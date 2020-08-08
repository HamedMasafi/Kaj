/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QDesktopServices>
#include <QDebug>
#include <QMessageBox>
#include <QApplication>
#include <QVariantList>

#ifdef Q_OS_ANDROID
#   include <QtAndroid>
#   include <QtAndroidExtras>
#   include <jni.h>
#endif

#include "mobility.h"

KAJ_BEGIN_NAMESPACE

Mobility::Mobility(QObject *parent) : QObject(parent)
{
}

void Mobility::toast(QString text, ToastDuration duration)
{
#ifdef Q_OS_ANDROID
    QtAndroid::runOnAndroidThread([text,duration] {
        QAndroidJniObject javaString = QAndroidJniObject::fromString(text);
        QAndroidJniObject toast = QAndroidJniObject::callStaticObjectMethod("android/widget/Toast", "makeText",
                                                                            "(Landroid/content/Context;Ljava/lang/CharSequence;I)Landroid/widget/Toast;",
                                                                            QtAndroid::androidActivity().object(),
                                                                            javaString.object(),
                                                                            jint(duration));
        toast.callMethod<void>("show");
    });
#else
    Q_UNUSED(duration);
    QMessageBox::information(0, qApp->applicationName(), text);
#endif
}

int Mobility::getStatusBarHeight()
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject window = QtAndroid::androidActivity().callObjectMethod("getWindow", "()Landroid/view/Window;");
    QAndroidJniObject view = window.callObjectMethod("getDecorView", "()Landroid/view/View;");
    QAndroidJniObject rect("android/graphics/Rect");
    view.callMethod<void>("getWindowVisibleDisplayFrame", "(Landroid/graphics/Rect;)V", rect.object());
    qDebug() << "rect="
             << rect.getField<jint>("top")
             << rect.getField<jint>("left")
             << rect.getField<jint>("right")
             << rect.getField<jint>("bottom");

#endif
    return 0;
}

void Mobility::setFullScreen(FullScreenMode mode)
{
    //FLAG_FULLSCREEN = 1024
#ifdef Q_OS_ANDROID
    QtAndroid::runOnAndroidThread([=] {
        QAndroidJniObject window = QtAndroid::androidActivity().callObjectMethod("getWindow", "()Landroid/view/Window;");
        const int FLAG_TRANSLUCENT_NAVIGATION = 0x08000000;
        const int FLAG_TRANSLUCENT_STATUS = 0x04000000;
        const int FLAG_FORCE_NOT_FULLSCREEN = 0x00000800;
        const int FLAG_FULLSCREEN = 0x00000400;
        const int FLAG_LAYOUT_INSET_DECOR = 0x00010000;

        const int SYSTEM_UI_FLAG_HIDE_NAVIGATION = 0x00000002;
        const int SYSTEM_UI_FLAG_FULLSCREEN = 0x00000004;
        const int SYSTEM_UI_FLAG_IMMERSIVE = 0x00000800;
        const int SYSTEM_UI_FLAG_IMMERSIVE_STICKY = 0x00001000;

        QAndroidJniObject view = window.callObjectMethod("getDecorView", "()Landroid/view/View;");
        switch (mode) {
        case LeanBack:
            view.callMethod<void>("setSystemUiVisibility", "(I)V", SYSTEM_UI_FLAG_FULLSCREEN | SYSTEM_UI_FLAG_HIDE_NAVIGATION);
            break;

        case Immersive:
            view.callMethod<void>("setSystemUiVisibility", "(I)V", SYSTEM_UI_FLAG_IMMERSIVE
                                  | SYSTEM_UI_FLAG_FULLSCREEN | SYSTEM_UI_FLAG_HIDE_NAVIGATION);
            break;

        case StickyImmersive:
            view.callMethod<void>("setSystemUiVisibility", "(I)V", SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                                  | SYSTEM_UI_FLAG_FULLSCREEN | SYSTEM_UI_FLAG_HIDE_NAVIGATION);
            break;
        }
/*
        window.callMethod<void>("setFlags", "(II)V", FLAG_TRANSLUCENT_NAVIGATION, FLAG_TRANSLUCENT_NAVIGATION);
        window.callMethod<void>("setFlags", "(II)V", FLAG_TRANSLUCENT_STATUS, FLAG_TRANSLUCENT_STATUS);
        window.callMethod<void>("setFlags", "(II)V", FLAG_FULLSCREEN, FLAG_FULLSCREEN);
        window.callMethod<void>("setFlags", "(II)V", FLAG_LAYOUT_INSET_DECOR, FLAG_LAYOUT_INSET_DECOR);
*/

    });
#else
    Q_UNUSED(mode);
#endif
}

Mobility::ConnectionType Mobility::networkConnectionType() const
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject cm = QtAndroid::androidActivity().callObjectMethod("getSystemService",
                                                                         "(Ljava/lang/String;)Ljava/lang/Object;",
                                                                         QAndroidJniObject::fromString("connectivity").object());
    QAndroidJniObject info = cm.callObjectMethod("getActiveNetworkInfo", "()Landroid/net/NetworkInfo;");
    jint type = info.callMethod<jint>("getType");
    return static_cast<ConnectionType>(type);
#endif
    return NONE;
}

void Mobility::directCallNumber(QString number)
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
    qDebug() << "directCallNumber is not working on desktop...";
#endif
}

KAJ_END_NAMESPACE
