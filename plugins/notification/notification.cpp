#if QT_ANDROIDEXTRAS_LIB
#   include <QtAndroidExtras>
#endif

#include <QDebug>

#include "notification.h"

Notification::Notification(QObject *parent) : KajPluginBase(parent)
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
    Q_UNUSED(text)
    qWarning("Class 'Notification' run only on android");
#endif
}

void Notification::init()
{
    qDebug()<<"Notification::init";
}

