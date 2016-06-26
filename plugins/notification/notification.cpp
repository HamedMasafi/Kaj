#if QT_ANDROIDEXTRAS_LIB
#   include <QtAndroidExtras>
#endif

#include <QDebug>

#include "notification.h"

TOOJ_DECLARE_PLUGIN(Notification)

Notification::Notification(QObject *parent) : ToojPluginBase(parent)
{

}

void Notification::createNotification(QString text)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject javaNotification = QAndroidJniObject::fromString(text);
    QAndroidJniObject::callStaticMethod<void>("org/tooj/plugins/NotificationClient",
                                              "notify",
                                              "(Ljava/lang/String;)V",
                                              javaNotification.object<jstring>());
#else
    qWarning("Class 'Notification' run only on android");
#endif
}

void Notification::init()
{
    qDebug()<<"Notification::init";
}

