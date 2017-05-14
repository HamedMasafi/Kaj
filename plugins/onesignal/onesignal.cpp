#include "onesignal.h"
#ifdef Q_OS_ANDROID
#include <QtAndroidExtras>

KAJ_BEGIN_JNI_METHODS

KAJ_JAVA_NATIVE_METHOD(NotificationReceivedHandler, signalReceived)(JNIEnv *env, jobject obj, jstring title, jstring message)
{
    Q_UNUSED(obj)
    QString t(env->GetStringUTFChars(title, false));
    QString b(env->GetStringUTFChars(message, false));
    OneSignal::instance()->signalRecived(t, b);
}

KAJ_JAVA_NATIVE_METHOD(NotificationOpenedHandler, signalOpened)(JNIEnv *env, jobject obj, jstring title, jstring message)
{
    Q_UNUSED(obj)
    QString t(env->GetStringUTFChars(title, false));
    QString b(env->GetStringUTFChars(message, false));
    OneSignal::instance()->signalOpened(t, b);
}
#endif

KAJ_END_JNI_METHODS

KAJ_DECL_SINGLETON(OneSignal)

OneSignal::OneSignal(QObject *parent) : KajPluginBase(parent), m_applicationId(QString::null), isRegistered(false)
{
    setInstacne(this);
}

void OneSignal::init()
{
}

static QObject *createSingletonOneSignal(QQmlEngine *, QJSEngine *)
{
    return new OneSignal();
}

void OneSignal::init(const QQmlApplicationEngine *engine)
{
    Q_UNUSED(engine)
//    qmlRegisterType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignal");
    qmlRegisterSingletonType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignal", createSingletonOneSignal);
}

QString OneSignal::applicationId() const
{
    return m_applicationId;
}

void OneSignal::setApplicationId(QString applicationId)
{
    if (m_applicationId == applicationId)
        return;

    m_applicationId = applicationId;
    emit applicationIdChanged(m_applicationId);
    initOneSignal();
}

void OneSignal::initOneSignal()
{
    if (isRegistered || m_applicationId.isNull())
        return;

#ifdef Q_OS_ANDROID
    QAndroidJniObject applicationId = QAndroidJniObject::fromString(m_applicationId);
    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(OneSignal),
                                              "Init",
                                              "(Ljava/lang/String;)V",
                                              applicationId.object<jstring>());

    isRegistered = true;
#else
    qWarning("Class 'OneSignal' run only on android");
#endif
}

