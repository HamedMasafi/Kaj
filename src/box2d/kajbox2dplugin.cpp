#include "kajbox2dplugin.h"

#include "box2dworld.h"
#include "box2dbody.h"
#include "box2ddebugdraw.h"
#include "box2dfixture.h"
#include "box2djoint.h"
#include "box2ddistancejoint.h"
#include "box2dprismaticjoint.h"
#include "box2drevolutejoint.h"
#include "box2dmotorjoint.h"
#include "box2dweldjoint.h"
#include "box2dpulleyjoint.h"
#include "box2dfrictionjoint.h"
#include "box2dwheeljoint.h"
#include "box2dmousejoint.h"
#include "box2dgearjoint.h"
#include "box2dropejoint.h"
#include "box2dcontact.h"
#include "box2draycast.h"

#include "../core/src/kajglobal.h"

KajBox2DPlugin::KajBox2DPlugin(QObject *parent) :
    QQmlExtensionPlugin(parent)
{

}

void KajBox2DPlugin::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj.Game.Box2D"));

    qmlRegisterType<Box2DWorld>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "World");
    qmlRegisterUncreatableType<Box2DProfile>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Profile",
                                             QStringLiteral("Property group of World"));
    qmlRegisterType<Box2DBody>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Body");
    qmlRegisterUncreatableType<Box2DFixture>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Fixture",
                                             QStringLiteral("Base type for Box, Circle etc."));
    qmlRegisterType<Box2DBox>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Box");
    qmlRegisterType<Box2DCircle>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Circle");
    qmlRegisterType<Box2DPolygon>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Polygon");
    qmlRegisterType<Box2DChain>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Chain");
    qmlRegisterType<Box2DEdge>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Edge");
    qmlRegisterType<Box2DDebugDraw>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "DebugDraw");
    qmlRegisterUncreatableType<Box2DJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Joint",
                                           QStringLiteral("Base type for DistanceJoint, RevoluteJoint etc."));
    qmlRegisterType<Box2DDistanceJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "DistanceJoint");
    qmlRegisterType<Box2DPrismaticJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "PrismaticJoint");
    qmlRegisterType<Box2DRevoluteJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RevoluteJoint");
    qmlRegisterType<Box2DMotorJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "MotorJoint");
    qmlRegisterType<Box2DWeldJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WeldJoint");
    qmlRegisterType<Box2DPulleyJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "PulleyJoint");
    qmlRegisterType<Box2DFrictionJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FrictionJoint");
    qmlRegisterType<Box2DWheelJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WheelJoint");
    qmlRegisterType<Box2DMouseJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "MouseJoint");
    qmlRegisterType<Box2DGearJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "GearJoint");
    qmlRegisterType<Box2DRopeJoint>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RopeJoint");
    qmlRegisterType<Box2DRayCast>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RayCast");

    qmlRegisterUncreatableType<Box2DContact>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Contact", QStringLiteral("Contact class"));
}
