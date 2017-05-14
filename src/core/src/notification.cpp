#include "notification.h"
#include <QtAndroid>
Notification::Notification(QObject *parent) : QObject(parent)
{

}

void Notification::message(QString text)
{
    QtAndroid::runOnAndroidThread([text] {
        QAndroidJniObject javaString = QAndroidJniObject::fromString(text);
        QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                            QtAndroid::androidActivity().object(),
                                                                            javaString.object(),
                                                                            jint(LONG));
        toast.callMethod<void>("show");
    });
}
