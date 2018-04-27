#include "kajmodule.h"

#include "kajglobal.h"
#include "kajqmlhelper.h"
#include "swipegesturemanager.h"
#include "units.h"
#include "zoomarea.h"
#include "scalecontainer.h"
#include "platforms.h"
#include "application.h"
#include "mobility.h"
#include "fileutils.h"

#ifdef KAJ_GAME_LIB
#   include "movementanimation.h"
#   include "rotateanimation.h"
#   include "gridmap.h"
#endif

#ifdef KAJ_APP_LIB
#endif

#define DECLARE_SINGELTON_METHOD(type) \
static QObject *createSingleton##type(QQmlEngine *, QJSEngine *) \
{ \
    return new type(); \
}

DECLARE_SINGELTON_METHOD(Units)
DECLARE_SINGELTON_METHOD(Platforms)
DECLARE_SINGELTON_METHOD(Mobility)
DECLARE_SINGELTON_METHOD(FileUtils)

void KajModule::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj"));

    qDebug() << "registerTypes" << KAJ_VERSION_STR;

    qmlRegisterType<SwipeGestureManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SwipeGestureManager");
    qmlRegisterType<ZoomArea>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ZoomArea");
    qmlRegisterType<Application>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Application");
    qmlRegisterSingletonType<Mobility>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Mobility", createSingletonMobility);
    qmlRegisterSingletonType<Units>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Units", createSingletonUnits);
    qmlRegisterSingletonType<Platforms>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Platforms", createSingletonPlatforms);
    qmlRegisterSingletonType<FileUtils>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FileUtils", createSingletonFileUtils);
    qmlRegisterUncreatableType<ScaleContainer>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ScaleContainer", "This is automaticly will be created");

#ifdef KAJ_GAME_LIB
    qmlRegisterType<MovementAnimation>("Kaj.Game", KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "MovementAnimation");
    qmlRegisterType<RotateAnimation>("Kaj.Game", KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RotateAnimation");
    qmlRegisterType<GridMap>("Kaj.Game", KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "GridMap");
#endif

#ifdef KAJ_APP_LIB
#endif
}

void KajModule::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    Q_UNUSED(engine);
}
