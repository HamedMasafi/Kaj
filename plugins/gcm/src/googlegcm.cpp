#include "googlegcm.h"

#include <firebase/app.h>
#include <firebase/messaging.h>
#include "gcmlistener.h"

#include <jni.h>

#include <QtAndroid>
#include <QAndroidJniEnvironment>
#include <QtAndroidExtras>

KAJ_DECL_SINGLETON(GoogleGcm)

KAJ_BEGIN_NAMESPACE

GoogleGcm::GoogleGcm(QObject *parent) : KajPluginBase(parent)
{

}

bool GoogleGcm::init()
{
    GcmListener *listener = new GcmListener;

    QAndroidJniEnvironment jni;
    ::firebase::App *app = ::firebase::App::Create(::firebase::AppOptions(),
                                                   (JNIEnv*)(jni),
                                                   QtAndroid::androidActivity().object());
    ::firebase::messaging::Initialize(*app, listener);

    return true;
}

#if QT_QML_LIB
bool GoogleGcm::init(const QQmlApplicationEngine *engine)
{
    qmlRegisterType<GoogleGcm>(KAJ_PLUGIN_QML_URI(GoogleGcm), 1, 0, "GoogleGcm");
    return true;
}
#endif

KAJ_END_NAMESPACE
