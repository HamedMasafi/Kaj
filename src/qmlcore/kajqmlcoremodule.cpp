#include "kajqmlcoremodule.h"

#include "kajglobal.h"
#include "swipegesturemanager.h"
#include "units.h"
#include "zoomarea.h"
#include "scalecontainer.h"
#include "shape.h"

#define DECLARE_SINGELTON_METHOD(type) \
static QObject *createSingleton##type(QQmlEngine *, QJSEngine *) \
{ \
    return new type(); \
}

DECLARE_SINGELTON_METHOD(Units)

void KajQmlCoreModule::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj"));

    qmlRegisterType<SwipeGestureManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SwipeGestureManager");
    qmlRegisterType<ZoomArea>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ZoomArea");
    qmlRegisterType<ScaleContainer>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ScaleContainer");
    qmlRegisterType<Shape>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Shape");
    qmlRegisterSingletonType<Units>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Units", createSingletonUnits);
}

void KajQmlCoreModule::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    Q_UNUSED(engine);
}
