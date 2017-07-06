#include <QDesktopServices>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>

#ifdef Q_OS_ANDROID
#   include <QtAndroid>
#   include <QtAndroidExtras>
#endif

#include "mobility.h"

Mobility::Mobility(QObject *parent) : QObject(parent)
{
}

void Mobility::toast(QString text)
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

void Mobility::callNumber(QString number)
{
#if defined(Q_OS_IOS)
        QDesktopServices::openUrl(QUrl(QString("tel://%1").arg(number)));
#elif defined(Q_OS_ANDROID)
    // get the Qt android activity
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod(
        "org/qtproject/qt5/android/QtNative", "activity",
        "()Landroid/app/Activity;");
    //
    if (activity.isValid()) {
        // real Java code to C++ code
        // Intent callIntent = new callIntent(Intent.ACTION_CALL);
        QAndroidJniObject callConstant
            = QAndroidJniObject::getStaticObjectField<jstring>(
                "android/content/Intent", "ACTION_CALL");
        QAndroidJniObject callIntent("android/content/Intent",
                                     "(Ljava/lang/String;)V",
                                     callConstant.object());
        // callIntent.setPackage("com.android.phone"); (<= 4.4w)
        // intent.setPackage("com.android.server.telecom");  (>= 5)
        QAndroidJniObject package;
        if (QtAndroid::androidSdkVersion() >= 21)
            package
                = QAndroidJniObject::fromString("com.android.server.telecom");
        else
            package = QAndroidJniObject::fromString("com.android.phone");
        callIntent.callObjectMethod(
            "setPackage", "(Ljava/lang/String;)Landroid/content/Intent;",
            package.object<jstring>());
        // callIntent.setData(Uri.parse("tel:" + number));
        QAndroidJniObject jNumber
            = QAndroidJniObject::fromString(QString("tel:%1").arg(number));
        QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod(
            "android/net/Uri", "parse", "(Ljava/lang/String;)Landroid/net/Uri;",
            jNumber.object());
        callIntent.callObjectMethod(
            "setData", "(Landroid/net/Uri;)Landroid/content/Intent;",
            uri.object<jobject>());
        // callIntent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        jint flag = QAndroidJniObject::getStaticField<jint>(
            "android/content/Intent", "FLAG_ACTIVITY_NEW_TASK");
        callIntent.callObjectMethod("setFlags", "(I)Landroid/content/Intent;",
                                    flag);
        // startActivity(callIntent);
        activity.callMethod<void>("startActivity",
                                  "(Landroid/content/Intent;)V",
                                  callIntent.object<jobject>());
    } else
        qDebug() << "Something wrong with Qt activity...";
#else
    Q_UNUSED(number);
    qDebug() << "Does nothing here...";
#endif
}
