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

#include <QtQml>

#include "movementanimation.h"
#include "rotateanimation.h"
#include "gridmap.h"
#include "kajgameplugin.h"

#ifdef KAJ_NAMESPACE
    using namespace KAJ_NAMESPACE;
#endif

KajGamePlugin::KajGamePlugin(QObject *parent) : QQmlExtensionPlugin(parent)
{

}

void KajGamePlugin::registerTypes(const char *uri)
{
    qmlRegisterType<MovementAnimation>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "MovementAnimation");
    qmlRegisterType<RotateAnimation>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "RotateAnimation");
    qmlRegisterType<GridMap>(uri, KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, "GridMap");
}
