#include "androidintent.h"
#include "androidjniarraylist.h"
#include "share.h"

#if QT_ANDROIDEXTRAS_LIB
#include <QAndroidIntent>
#include <QAndroidJniEnvironment>
#   include <QAndroidJniObject>
#include <QAndroidParcel>
#   include <QtAndroid>
#endif

#include <QtQml>

#define GET_INTENT_FIELD(x) QAndroidJniObject::getStaticObjectField(            \
    "android/content/Intent", #x, "Ljava/lang/String;");

#define CREATE_INTENT(action)  QAndroidJniObject intent(                        \
    "android/content/Intent", "(Ljava/lang/String;)V",                          \
    QAndroidJniObject::fromString("android.intent.action." #action).object());

#define PUT_EXTRA(intent, name, value) intent.callObjectMethod("putExtra",      \
    "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",           \
    EXTRA_SUBJECT.object(), subjectObject.object());

static QObject *createSingletonShare(QQmlEngine *, QJSEngine *)
{
    return new Share();
}

KAJ_BEGIN_NAMESPACE

Share::Share(QObject *parent) : KajPluginBase(parent)
{

}

void Share::shareApp()
{

#if QT_ANDROIDEXTRAS_LIB
    QAndroidJniExceptionCleaner cleaner;
    AndroidIntent intent(ACTION_SEND_MULTIPLE);
    intent.setType("application/vnd.android.package-archive");
    QAndroidJniObject applicationInfo = QtAndroid::androidActivity()
            .callObjectMethod("getApplicationInfo", "()Landroid/content/pm/ApplicationInfo;");
    QAndroidJniObject publicSourceDir = applicationInfo.getObjectField<jstring>("publicSourceDir");

    QAndroidJniObject file("java/io/File", "(Ljava/lang/String;)V", publicSourceDir.object());

    QAndroidJniObject uri = QAndroidJniObject::callStaticObjectMethod("android/net/Uri",
                                        "fromFile",
                                        "(Ljava/io/File;)Landroid/net/Uri;",
                                        file.object());

    AndroidJniArrayList array(1);
    array.add(uri.object());

    intent.handle().callObjectMethod("putParcelableArrayListExtra",
                                     "(Ljava/lang/String;Ljava/util/ArrayList;)Landroid/content/Intent;",
                                     QAndroidJniObject::fromString(EXTRA_STREAM).object(),
                                     array.handle());

    AndroidIntent chooserIntent = AndroidIntent::createChooser(intent, "");
    QtAndroid::startActivity(chooserIntent.handle(), 2);
#endif
}

bool Share::init(const QQmlApplicationEngine *engine)
{
#if QT_QML_LIB
    qmlRegisterSingletonType<Share>("Kaj.Share", 1, 0, "Share", createSingletonShare);
#endif
    return true;
}

void Share::shareLink(const QString &subject, const QString &url)
{
#ifdef Q_OS_ANDROID

    AndroidIntent intent(ACTION_SEND);
    intent.setType("text/plain");
    intent.putExtra(EXTRA_SUBJECT, subject);
    intent.putExtra(EXTRA_TEXT, url);
    AndroidIntent chooserIntent = AndroidIntent::createChooser(intent, "به اشتراک گذاری!");
    QtAndroid::startActivity(chooserIntent.handle(), 1);

//    QAndroidJniObject intent("android/content/Intent",
//                             "(Ljava/lang/String;)V",
//                             QAndroidJniObject::fromString("android.intent.action.SEND").object());

//    intent.callObjectMethod("setType", "(Ljava/lang/String;)Landroid/content/Intent;",
//                            QAndroidJniObject::fromString("text/plain").object());

//    //intent.callObjectMethod("", "", "0x04000000");

//    QAndroidJniObject subjectObject = QAndroidJniObject::fromString(subject);
//    QAndroidJniObject urlObject = QAndroidJniObject::fromString(url);
//    QAndroidJniObject EXTRA_SUBJECT = GET_INTENT_FIELD("EXTRA_SUBJECT");

//            /*QAndroidJniObject::getStaticObjectField("android/content/Intent",
//                                                                              "EXTRA_SUBJECT",
//                                                                              "Ljava/lang/String;");*/
//    //android.intent.extra.SUBJECT
//    QAndroidJniObject EXTRA_TEXT = GET_INTENT_FIELD("EXTRA_TEXT");
//            /*QAndroidJniObject::getStaticObjectField("android/content/Intent",
//                                                                              "EXTRA_TEXT", "Ljava/lang/String;");*/
//    //android.intent.extra.TEXT
//    intent.callObjectMethod("putExtra",
//                            "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
//                            EXTRA_SUBJECT.object(),
//                            subjectObject.object());

//    intent.callObjectMethod("putExtra",
//                            "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
//                            EXTRA_TEXT.object(),
//                            urlObject.object());

//    QAndroidJniObject shareIntent = QAndroidJniObject::callStaticObjectMethod(
//                "android/content/Intent",
//                "createChooser",
//                "(Landroid/content/Intent;Ljava/lang/CharSequence;)Landroid/content/Intent;",
//                intent.object(),
//                QAndroidJniObject::fromString("Share!").object());

//    QtAndroid::startActivity(shareIntent, 1);

#endif
}

KAJ_END_NAMESPACE
