#include <QQmlApplicationEngine>
#include <QFontDatabase>
#include <QQmlContext>
#include <QGuiApplication>
#include <QScreen>
#include <QtQml>
#include <QDebug>

#include <QDesktopWidget>

#include <functional>

#ifdef KAJ_GAME_LIB
#   include "kajgameplugin.h"
#endif

#ifdef KAJ_CORE_LIB
#   include "kajglobal.h"
#   include "kajqmlhelper.h"
#   include "swipegesturemanager.h"
#   include "units.h"
#   include "zoomarea.h"
#   include "scalecontainer.h"
#   include "platforms.h"
#endif

QT_BEGIN_NAMESPACE


static QObject *createSingletonUnits(QQmlEngine *, QJSEngine *)
{
    return new Units();
}

static QObject *createSingletonPlatforms(QQmlEngine *, QJSEngine *)
{
    return new Platforms();
}


class KajModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj"));

        qDebug() << "registerTypes" << KAJ_VERSION_STR;

        qmlRegisterType<SwipeGestureManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SwipeGestureManager");
        qmlRegisterType<ZoomArea>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ZoomArea");
        qmlRegisterUncreatableType<ScaleContainer>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ScaleContainer", "This is automaticly will be created");
        qmlRegisterSingletonType<Units>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Units", createSingletonUnits);
        qmlRegisterSingletonType<Platforms>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Platforms", createSingletonPlatforms);
    }

    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        Q_UNUSED(uri);
        Q_UNUSED(engine);
    }
};


/*!
 * 
 * This is qdoc
 * 
 */ 
KajQmlHelper::KajQmlHelper(QObject *parent) : QObject(parent)
{

}

void KajQmlHelper::registerQmlTypes(QQmlApplicationEngine *engine)
{
    qDebug() << "Registering Kaj ver" << KAJ_VERSION_STR;

    engine->addImportPath("qrc:/kaj/qml/");

#ifdef KAJ_CORE_LIB
//    qmlRegisterType<SwipeGestureManager>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SwipeGestureManager");
//    qmlRegisterType<ZoomArea>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ZoomArea");
//    qmlRegisterUncreatableType<ScaleContainer>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ScaleContainer", "This is automaticly will be created");
//    qmlRegisterSingletonType<Units>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Units", createSingletonUnits);
//    qmlRegisterSingletonType<Platforms>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Platforms", createSingletonPlatforms);
#else
#   error Core module does not registered
#endif

#ifdef KAJ_GAME_LIB
    KajGamePlugin gamePlugin;
    gamePlugin.registerTypes(KAJ_QML_URL ".Game");
#endif

#ifdef KAJ_APP_LIB

#endif

}

void KajQmlHelper::registerPlugins()
{
    KajPluginRegisterHelper::registerAll();
}

QT_END_NAMESPACE
