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
    engine->addImportPath("qrc:/kaj/qml/");

#ifdef KAJ_CORE_LIB
    qmlRegisterType<SwipeGestureManager>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SwipeGestureManager");
    qmlRegisterType<ZoomArea>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ZoomArea");
    qmlRegisterUncreatableType<ScaleContainer>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ScaleContainer", "This is automaticly will be created");
    qmlRegisterSingletonType<Units>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Units", createSingletonUnits);
    qmlRegisterSingletonType<Platforms>(KAJ_QML_URL, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Platforms", createSingletonPlatforms);
#endif

#ifdef KAJ_GAME_LIB
    KajGamePlugin gamePlugin;
    gamePlugin.registerTypes(KAJ_QML_URL ".Game");
#endif
}

void KajQmlHelper::registerPlugins()
{
    KajPluginRegisterHelper::registerAll();
}

QT_END_NAMESPACE
