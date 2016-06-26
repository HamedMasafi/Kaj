#include <QtQml>

#include "movementanimation.h"
#include "rotateanimation.h"
#include "gridmap.h"
#include "kajgameplugin.h"

KajGamePlugin::KajGamePlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{

}

void KajGamePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<MovementAnimation>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "MovementAnimation");
    qmlRegisterType<RotateAnimation>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RotateAnimation");
    qmlRegisterType<GridMap>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "GridMap");
}
