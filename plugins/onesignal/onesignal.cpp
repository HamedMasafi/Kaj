//#include "onesignal.h"
//#ifdef Q_OS_ANDROID
//#include <QtAndroidExtras>

//KAJ_BEGIN_JNI_METHODS

//KAJ_JAVA_NATIVE_METHOD(OneSignal, signalReceived)(JNIEnv *env, jobject obj, jlong nativePointer, jstring title, jstring message, jstring extraData)
//{
//    Q_UNUSED(obj)
//    OneSignal *ins = reinterpret_cast<OneSignal *>(nativePointer);

//    QString t(env->GetStringUTFChars(title, false));
//    QString b(env->GetStringUTFChars(message, false));
//    QString ed(env->GetStringUTFChars(extraData, false));
//    ins->signalRecived(t, b, ed);
//    ins->setAdditionalData(ed);
//}

//KAJ_JAVA_NATIVE_METHOD(OneSignal, signalOpened)(JNIEnv *env, jobject obj, jlong nativePointer, jstring title, jstring message)
//{
//    Q_UNUSED(obj)
//    OneSignal *ins = reinterpret_cast<OneSignal *>(nativePointer);

//    QString t(env->GetStringUTFChars(title, false));
//    QString b(env->GetStringUTFChars(message, false));
//    ins->signalOpened(t, b);
//}


//KAJ_JAVA_NATIVE_METHOD(OneSignal, idsAvailable)(JNIEnv *env, jobject obj, jlong nativePointer, jstring userId, jstring registrationId)
//{
//    Q_UNUSED(obj)
//    OneSignal *ins = reinterpret_cast<OneSignal *>(nativePointer);

//    QString u(env->GetStringUTFChars(userId, false));
//    QString r(env->GetStringUTFChars(registrationId, false));
//    ins->setUserId(u);
//    ins->setRegistrationId(r);
//}

//KAJ_END_JNI_METHODS

//#endif

//KAJ_DECL_SINGLETON(OneSignal)

//OneSignal::OneSignal(QObject *parent) : KajPluginBase(parent), m_applicationId(QString::null), isRegistered(false),
//    m_userId(QString::null), m_registrationId(QString::null)
//{
//    qDebug() << "OneSignal ctor";
//    setInstacne(this);
//}

//void OneSignal::init()
//{
//}

//static QObject *createSingletonOneSignal(QQmlEngine *, QJSEngine *)
//{
//    return new OneSignal;
//}

//void OneSignal::init(const QQmlApplicationEngine *engine)
//{
//    Q_UNUSED(engine)
//    qmlRegisterType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignal");
//    qmlRegisterSingletonType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignalInstance", createSingletonOneSignal);
//}

//QString OneSignal::applicationId() const
//{
//    return m_applicationId;
//}

//QString OneSignal::userId()
//{
//    if (m_userId.isNull()) {
//#ifdef Q_OS_ANDROID
//    QAndroidJniObject userId = QAndroidJniObject::callStaticObjectMethod<jstring>(KAJ_JAVA_CLASS_NAME(OneSignal), "getUserId");

//    m_userId = userId.toString();
//#endif
//    }

//    return m_userId;
//}

//QString OneSignal::registrationId()
//{
//    if (m_registrationId.isNull()) {
//#ifdef Q_OS_ANDROID
//    QAndroidJniObject registrationId = QAndroidJniObject::callStaticObjectMethod<jstring>(KAJ_JAVA_CLASS_NAME(OneSignal), "getRegistrationId");

//    m_registrationId = registrationId.toString();
//#endif
//    }

//    return m_registrationId;
//}

//QString OneSignal::additionalData()
//{
//    if (m_additionalData.isNull()) {
//#ifdef Q_OS_ANDROID
//    QAndroidJniObject registrationId = QAndroidJniObject::callStaticObjectMethod<jstring>(KAJ_JAVA_CLASS_NAME(OneSignal), "getAdditionalData");

//    m_additionalData = registrationId.toString();
//#endif
//    }

//    return m_additionalData;
//}

//void OneSignal::setApplicationId(QString applicationId)
//{
//    if (m_applicationId == applicationId)
//        return;

//    m_applicationId = applicationId;
//    emit applicationIdChanged(m_applicationId);
//    initOneSignal();
//}

//void OneSignal::setUserId(QString userId)
//{
//    qDebug() <<"User id changed from" << m_userId << "to" << userId;
//    if (m_userId == userId)
//        return;

//    m_userId = userId;
//    emit userIdChanged(m_userId);
//}

//void OneSignal::setRegistrationId(QString registrationId)
//{
//    if (m_registrationId == registrationId)
//        return;

//    m_registrationId = registrationId;
//    emit registrationIdChanged(m_registrationId);
//}

//void OneSignal::setAdditionalData(QString additionalData)
//{
//    if (m_additionalData == additionalData)
//        return;

//    m_additionalData = additionalData;
//    emit additionalDataChanged(m_additionalData);
//}

//void OneSignal::initOneSignal()
//{
//    if (isRegistered || m_applicationId.isNull())
//        return;

//#ifdef Q_OS_ANDROID
//    QAndroidJniObject applicationId = QAndroidJniObject::fromString(m_applicationId);
//    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(OneSignal),
//                                              "Init",
//                                              "(Ljava/lang/String;J)V",
//                                              applicationId.object<jstring>(),
//                                              reinterpret_cast<jlong>(this));

//    isRegistered = true;
//#else
//    qWarning("Class 'OneSignal' run only on android");
//#endif
//}

