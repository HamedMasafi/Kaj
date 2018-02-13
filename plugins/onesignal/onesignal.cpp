#include "onesignal.h"

#ifdef Q_OS_ANDROID

#include <QtAndroidExtras>

KAJ_DECL_SINGLETON(OneSignal)

KAJ_BEGIN_JNI_METHODS

KAJ_JAVA_NATIVE_METHOD(OneSignal, signalReceived)(JNIEnv *env, jobject obj, jlong nativePointer, jstring title, jstring message, jstring extraData)
{
    Q_UNUSED(obj)
//    if (nativePointer) {
//        OneSignal *ins = reinterpret_cast<OneSignal *>(nativePointer);

        QString t(env->GetStringUTFChars(title, false));
        QString b(env->GetStringUTFChars(message, false));
        QString ed(env->GetStringUTFChars(extraData, false));
        emit OneSignal::instance()->signalRecived(t, b, ed);
        //    ins->setAdditionalData(ed);
        OneSignal::instance()->metaObject()->invokeMethod(OneSignal::instance(), "setAdditionalData", Q_ARG(QString, ed));
//    }
}

KAJ_JAVA_NATIVE_METHOD(OneSignal, signalOpened)(JNIEnv *env, jobject obj, jlong nativePointer, jstring title, jstring message, jstring extraData)
{
    Q_UNUSED(obj)

//    if (nativePointer) {
//        OneSignal *ins = reinterpret_cast<OneSignal *>(nativePointer);

        QString t(env->GetStringUTFChars(title, false));
        QString b(env->GetStringUTFChars(message, false));
        QString ed(env->GetStringUTFChars(extraData, false));
        //    emit ins->signalOpened(t, b);
        OneSignal::instance()->metaObject()->invokeMethod(OneSignal::instance(), "signalOpened", Q_ARG(QString, t), Q_ARG(QString, b), Q_ARG(QString, ed));
//    }
}


KAJ_JAVA_NATIVE_METHOD(OneSignal, idsAvailable)(JNIEnv *env, jobject obj, jlong nativePointer, jstring userId, jstring registrationId)
{
    Q_UNUSED(obj)
//    if (nativePointer) {
//        OneSignal *ins = reinterpret_cast<OneSignal *>(nativePointer);

        QString u(env->GetStringUTFChars(userId, false));
        QString r(env->GetStringUTFChars(registrationId, false));
        //    ins->setUserId(u);
        //    ins->setRegistrationId(r);
        OneSignal::instance()->metaObject()->invokeMethod(OneSignal::instance(), "setUserId", Q_ARG(QString, u));
        OneSignal::instance()->metaObject()->invokeMethod(OneSignal::instance(), "setRegistrationId", Q_ARG(QString, r));
//    }
}

KAJ_END_JNI_METHODS

OneSignal::OneSignal(QObject *parent) : KajPluginBase(parent), m_applicationId(QString::null), isRegistered(false),
    m_userId(QString::null), m_registrationId(QString::null)
{
    qDebug() << "OneSignal ctor";
    if (instance() != Q_NULLPTR)
        qDebug() << "Instance is inited!!!!!!!!!!!!!!!!!!";
    setInstacne(this);

    connect(this, &QObject::objectNameChanged, [=](const QString &objectName){
       qDebug() <<  "QObject::objectNameChanged; " << objectName;
    });
}

static QObject *createSingletonOneSignal(QQmlEngine *, QJSEngine *)
{
    return OneSignal::instance();
}

bool OneSignal::init(const QQmlApplicationEngine *engine)
{
    Q_UNUSED(engine)
    qmlRegisterType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignal");
//    qmlRegisterSingletonType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignalInstance", createSingletonOneSignal);
    return true;
}

QString OneSignal::applicationId() const
{
    return m_applicationId;
}

QString OneSignal::userId()
{
    if (m_userId.isNull()) {
        QAndroidJniObject userId = QAndroidJniObject::callStaticObjectMethod<jstring>(KAJ_JAVA_CLASS_NAME(OneSignal), "getUserId");

        m_userId = userId.toString();
    }

    return m_userId;
}

QString OneSignal::registrationId()
{
    if (m_registrationId.isNull()) {
        QAndroidJniObject registrationId = QAndroidJniObject::callStaticObjectMethod<jstring>(KAJ_JAVA_CLASS_NAME(OneSignal), "getRegistrationId");

        m_registrationId = registrationId.toString();
    }

    return m_registrationId;
}

QString OneSignal::additionalData()
{
    if (m_additionalData.isNull()) {
        QAndroidJniObject registrationId = QAndroidJniObject::callStaticObjectMethod<jstring>(KAJ_JAVA_CLASS_NAME(OneSignal), "getAdditionalData");

        m_additionalData = registrationId.toString();
    }

    return m_additionalData;
}

void OneSignal::setApplicationId(QString applicationId)
{
    if (m_applicationId == applicationId)
        return;

    qDebug() << "OneSignal::setApplicationId" << applicationId;
    m_applicationId = applicationId;
    emit applicationIdChanged(m_applicationId);
//    initOneSignal();
}

void OneSignal::setUserId(QString userId)
{
    if (m_userId == userId)
        return;

    qDebug() <<"User id changed from" << m_userId << "to" << userId << "; " << objectName();
    m_userId = userId;
    emit userIdChanged(m_userId);
    qDebug() << "After emit";
}

void OneSignal::setRegistrationId(QString registrationId)
{
    if (m_registrationId == registrationId)
        return;

    m_registrationId = registrationId;
    emit registrationIdChanged(m_registrationId);
}

void OneSignal::setAdditionalData(QString additionalData)
{
    if (m_additionalData == additionalData)
        return;

    m_additionalData = additionalData;
    emit additionalDataChanged(m_additionalData);
}

void OneSignal::initOneSignal()
{
    if (isRegistered || m_applicationId.isNull())
        return;

    qDebug() << "Initing onegignal" << objectName();
    QAndroidJniObject applicationId = QAndroidJniObject::fromString(m_applicationId);
    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(OneSignal),
                                              "Init",
                                              "(Ljava/lang/String;J)V",
                                              applicationId.object<jstring>(),
                                              reinterpret_cast<jlong>(this));

    isRegistered = true;
}

#endif
