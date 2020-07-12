#if QT_ANDROIDEXTRAS_LIB
#   include <QtAndroidExtras>
#endif

#include <QDebug>

#include "notification.h"

Notification::Notification(QObject *parent) : KajPluginBase(parent)
{

}

#if QT_QML_LIB
bool Notification::init(const QQmlApplicationEngine *engine)
{
    Q_UNUSED(engine)
    qmlRegisterType<Notification>("Kaj.Notification", 1, 0, "Notification");
    return true;
}
#endif

void Notification::createNotification(QString text)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject manager = QtAndroid::androidActivity().callObjectMethod("getSystemService",
                                              "(Ljava/lang/String;)Ljava/lang/Object;",
                                              QAndroidJniObject::fromString("notification").object());
//    QAndroidJniObject manager("android/support/v4/app/NotificationCompatManager");

    QAndroidJniObject builder("android/support/v4/app/NotificationCompat$Builder",
                              "(Landroid/content/Context;)V",
                              QtAndroid::androidActivity().object());

    builder.callObjectMethod("setContentText", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;",
                             QAndroidJniObject::fromString(text).object());

    builder.callObjectMethod("setContentTitle", "(Ljava/lang/CharSequence;)Landroid/support/v4/app/NotificationCompat$Builder;",
                             QAndroidJniObject::fromString("Hi").object());

    auto msg = builder.callObjectMethod("build", "()Landroid/app/Notification;");
    manager.callMethod<void>("notify", "(ILandroid/app/Notification;)V",
                             1, msg.object());

//    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(text);
//    QAndroidJniObject::callStaticMethod<void>("org/kaj/plugins/NotificationClient",
//                                              "notify",
//                                              "(Ljava/lang/String;)V",
//                                              javaNotification.object<jstring>());
#else
    Q_UNUSED(text)
    qWarning("Class 'Notification' run only on android");
#endif
}

