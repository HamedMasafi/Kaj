#include "notification.h"

#include <QMessageBox>
#include <QApplication>
#ifdef Q_OS_ANDROID
#include <QtAndroid>
#endif
Notification::Notification(QObject *parent) : QObject(parent)
{

}

void Notification::message(QString text)
{
#ifdef Q_OS_ANDROID
    QtAndroid::runOnAndroidThread([text] {
        QAndroidJniObject javaString = QAndroidJniObject::fromString(text);
        QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                            QtAndroid::androidActivity().object(),
                                                                            javaString.object(),
                                                                            jint(LONG));
        toast.callMethod<void>("show");
    });
#else
    QMessageBox::information(0, qApp->applicationName(), text);
#endif
}
