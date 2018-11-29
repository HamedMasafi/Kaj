#include "share.h"

#if QT_ANDROIDEXTRAS_LIB
#include <QAndroidIntent>
#   include <QAndroidJniObject>
#   include <QtAndroid>
#endif

#include <QtQml>

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
    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(Share),
                                              "ShareApp",
                                              "()V");
#endif
}

bool Share::init(const QQmlApplicationEngine *engine)
{
#if QT_QML_LIB
    qmlRegisterSingletonType<Share>("Kaj.Share", 1, 0, "Share", createSingletonShare);
#endif
}

void Share::shareLink(const QString &subject, const QString &url)
{
//    QAndroidJniObject jsText = QAndroidJniObject::fromString(text);
//    QAndroidJniObject jsUrl = QAndroidJniObject::fromString(url.toString());
//    QAndroidJniObject::callStaticMethod<void>("com/musescore/QShareUtils",
//                                       "share",
//                                       "(Ljava/lang/String;Ljava/lang/String;)V",
//                                       jsText.object<jstring>(), jsUrl.object<jstring>());
#ifdef Q_OS_ANDROID
    QAndroidIntent it("ACTION_SEND");
    it.putExtra("EXTRA_SUBJECT", subject.toLocal8Bit());
    it.putExtra("EXTRA_TEXT", url.toLocal8Bit());
    QtAndroid::startActivity(it.handle(), 1);

//    QAndroidJniObject ACTION_SET_TIMER = QAndroidJniObject::getStaticField<jint>("android/content/Intent",
//                                                                                 "ACTION_SEND");
//    QAndroidJniObject intent("android/content/Intent",
//                             "(Ljava/lang/String;)V",
//                             ACTION_SET_TIMER.object());

//    QAndroidJniObject subjectObject = QAndroidJniObject::fromString(subject);
//    QAndroidJniObject urlObject = QAndroidJniObject::fromString(url);
//    QAndroidJniObject EXTRA_SUBJECT = QAndroidJniObject::getStaticField<jint>("android/content/Intent",
//                                                                              "EXTRA_SUBJECT");
//    QAndroidJniObject EXTRA_TEXT = QAndroidJniObject::getStaticObjectField<jint>("android/content/Intent",
//                                                                              "EXTRA_TEXT");
//    intent.callObjectMethod("putExtra",
//                            "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
//                            EXTRA_SUBJECT.object(),
//                            subjectObject.object());

//    intent.callObjectMethod("putExtra",
//                            "(Ljava/lang/String;Ljava/lang/String;)Landroid/content/Intent;",
//                            EXTRA_TEXT.object(),
//                            urlObject.object());

//    QtAndroid::startActivity(intent, 1);
#endif
}

KAJ_END_NAMESPACE
