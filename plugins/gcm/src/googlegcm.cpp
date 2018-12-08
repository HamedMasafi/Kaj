#include "googlegcm.h"

#ifdef KAJ_PLUGIN_GCM
#   include <firebase/app.h>
#   include <firebase/messaging.h>
#   include "firebase/future.h"
#   include "firebase/util.h"

#   include "gcmlistener.h"

#   include <android/native_activity.h>

#   include <jni.h>

#   include <QtAndroid>
#   include <QAndroidJniEnvironment>
#   include <QtAndroidExtras>
#endif

KAJ_DECL_SINGLETON(GoogleGcm)

KAJ_BEGIN_NAMESPACE

Message::Message(const firebase::messaging::Message &message)
{
#ifdef KAJ_PLUGIN_GCM
    if (message.notification) {
        setBody(QString::fromStdString(message.notification->body));
        setTitle(QString::fromStdString(message.notification->title));
        setLink(QString::fromStdString(message.link));
        for (auto const &i : message.data) {
            m_data.insert(QString::fromStdString(i.first),
                          QString::fromStdString(i.second));
        }
    }
#else
    Q_UNUSED(message);
#endif
}

QString Message::title() const
{
    return m_title;
}

QString Message::body() const
{
    return m_body;
}

QMap<QString, QString> Message::data() const
{
    return m_data;
}

QString Message::link() const
{
    return m_link;
}

void Message::setTitle(QString title)
{
    if (m_title == title)
        return;

    m_title = title;
    emit titleChanged(m_title);
}

void Message::setBody(QString body)
{
    if (m_body == body)
        return;

    m_body = body;
    emit bodyChanged(m_body);
}

void Message::setData(QMap<QString, QString> data)
{
    if (m_data == data)
        return;

    m_data = data;
    emit dataChanged(m_data);
}

void Message::setLink(QString link)
{
    if (m_link == link)
        return;

    m_link = link;
    emit linkChanged(m_link);
}

static QObject *createSingletonGoogleGcm(QQmlEngine *, QJSEngine *)
{
    return GoogleGcm::instance();
}

GoogleGcm::GoogleGcm(QObject *parent) : KajPluginBase(parent)
{

}

QString GoogleGcm::registrationToken() const
{
    return m_registrationToken;
}

Message *GoogleGcm::polLastMessage()
{
#ifdef KAJ_PLUGIN_GCM
    ::firebase::messaging::Message msg;
    listener->PollMessage(&msg);

    Message *m2 = new Message(msg);
    return m2;
#else
    return nullptr;
#endif
}

bool GoogleGcm::init()
{
#ifdef KAJ_PLUGIN_GCM
    GcmListener *listener = new GcmListener(instance());
    instance()->listener = listener;
//    ::firebase::messaging::PollableListener *listener = new ::firebase::messaging::PollableListener;


    QAndroidJniEnvironment jni;

    qDebug() << "api key" << ::firebase::AppOptions().api_key();
    ::firebase::App *app = ::firebase::App::Create(::firebase::AppOptions(),
                                                   (JNIEnv*)(jni),
                                                   QtAndroid::androidActivity().object());
    ::firebase::ModuleInitializer initializer;
    initializer.Initialize(
                app, listener, [](::firebase::App* app, void* userdata) {
        ::firebase::messaging::PollableListener* listener =
                static_cast<::firebase::messaging::PollableListener*>(userdata);
        firebase::messaging::MessagingOptions options;
        // Prevent the app from requesting permission to show notifications
        // immediately upon starting up. Since it the prompt is being
        // suppressed, we must manually display it with a call to
        // RequestPermission() elsewhere.
        options.suppress_notification_permission_prompt = true;
        qDebug() << "RequestPermission() elsewhere.";
        return ::firebase::messaging::Initialize(*app, listener, options);
    });

    if (initializer.InitializeLastResult().error() != 0) {
        qDebug() << "Failed to initialize Firebase Messaging: " <<
                    initializer.InitializeLastResult().error_message();
        QThread::msleep(2000);
        return false;
    }

    ::firebase::Future<void> result = ::firebase::messaging::RequestPermission();
    while (result.status() == ::firebase::kFutureStatusPending) {
        QThread::msleep(100);
    }

    if (result.error() ==
            ::firebase::messaging::kErrorFailedToRegisterForRemoteNotifications) {
        qDebug() << "Error registering for remote notifications.";
    } else {
        qDebug() << "Finished checking for permission.";
    }

    std::string token;
    if (listener->PollRegistrationToken(&token)) {
        qDebug() << "Received Registration Token: " << token.c_str();
        instance()->setRegistrationToken(QString::fromStdString(token));
    } else {
        qDebug() << "Unable to get Registration Token";
    }

    //    ::firebase::InitResult r = ::firebase::messaging::Initialize(*app, listener);

    //    if (r != ::firebase::kInitResultSuccess) {
    //        qWarning() << "Error initing google gcm";
    //        return false;
    //    }

#endif
    return true;
}

#if QT_QML_LIB
bool GoogleGcm::init(const QQmlApplicationEngine *)
{
    qmlRegisterUncreatableType<Message>("Kaj.GoogleGcm", 1, 0, "Message", "For using in gcm methods");
    qmlRegisterSingletonType<GoogleGcm>("Kaj.GoogleGcm", 1, 0, "GoogleGcm", createSingletonGoogleGcm);
    return true;
}
#endif

void GoogleGcm::setRegistrationToken(QString registrationToken)
{
    if (m_registrationToken == registrationToken)
        return;

    m_registrationToken = registrationToken;
    emit registrationTokenChanged(m_registrationToken);
}

KAJ_END_NAMESPACE
