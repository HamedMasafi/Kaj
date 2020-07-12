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
//#include "request/webrequest.h"
//#include "request/stringrequest.h"
//#include "request/imagerequest.h"
//#include "request/jsonrequest.h"
//#include "request/variantrequest.h"
//#include "request/webrequestcache.h"
//#include "request/webrequestmanager.h"
#include "shape.h"
#include "appcolors.h"
#include "contactsmodel.h"
#include "icons.h"
//#include "safezone.h"

#ifdef KAJ_GAME_LIB
#   include "kajgameplugin.h"
#endif

#ifdef KAJ_APP_LIB
#endif

#ifdef  KAJ_BOX2D_LIB
#  include "../../box2d/kajbox2dplugin.h"
#endif
#ifdef KAJ_NAMESPACE
    using namespace KAJ_NAMESPACE;
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
DECLARE_SINGELTON_METHOD(Icons)

//static QObject *createSingletonRestRequestCallsManager(QQmlEngine *, QJSEngine *)
//{
//    return WebRequestManager::instance();
//}

static QObject *createSingletonAppColors(QQmlEngine *, QJSEngine *)
{
    return AppColors::instance();
}

void KajModule::registerTypes(const char *uri)
{
    Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj"));

    qDebug() << "Registering core module" << KAJ_VERSION_STR;

    qmlRegisterType<SwipeGestureManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SwipeGestureManager");
    qmlRegisterType<ZoomArea>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ZoomArea");
    qmlRegisterType<Application>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Application");
    qmlRegisterType<ScaleContainer>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ScaleContainer");
    qmlRegisterType<Shape>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Shape");
    qmlRegisterType<ContactsModel>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ContactsModel");
//    qmlRegisterType<SafeZone>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "SafeZone");
    qmlRegisterSingletonType<Mobility>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Mobility", createSingletonMobility);
    qmlRegisterSingletonType<Units>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Units", createSingletonUnits);
    qmlRegisterSingletonType<Platforms>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Platforms", createSingletonPlatforms);
    qmlRegisterSingletonType<FileUtils>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "FileUtils", createSingletonFileUtils);
    qmlRegisterSingletonType<AppColors>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "AppColors", createSingletonAppColors);
    qmlRegisterSingletonType<Icons>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "Icons", createSingletonIcons);

    //Web request
//    qmlRegisterType<WebRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequest");
//    qmlRegisterType<StringRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "StringRequest");
//    qmlRegisterType<JsonObjectRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "JsonRequest");
//    qmlRegisterType<VariantRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "VariantRequest");
//    qmlRegisterType<ImageRequest>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "ImageRequest");
//    qmlRegisterType<WebRequestManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestManager");
//    qmlRegisterType<WebRequestCache>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestCache");
//    qmlRegisterSingletonType<WebRequestManager>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "WebRequestManagerInstance", createSingletonRestRequestCallsManager);

#ifdef KAJ_GAME_LIB
    KajGamePlugin gamePlugin;
    gamePlugin.registerTypes("Kaj.Game");
//    qmlRegisterType<MovementAnimation>("Kaj.Game", KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "MovementAnimation");
//    qmlRegisterType<RotateAnimation>("Kaj.Game", KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RotateAnimation");
//    qmlRegisterType<GridMap>("Kaj.Game", KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "GridMap");
#endif

#ifdef KAJ_APP_LIB
#endif

#ifdef KAJ_BOX2D_LIB
    KajBox2DPlugin plugin;
    plugin.registerTypes("Kaj.Game.Box2D");
#endif
}

void KajModule::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    Q_UNUSED(engine);
}
