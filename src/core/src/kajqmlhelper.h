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

#ifndef KAJQMLHELPER_H
#define KAJQMLHELPER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "kajpluginbase.h"
#include "kajglobal.h"

class QQmlApplicationEngine;

KAJ_BEGIN_NAMESPACE
class KAJ_EXPORT KajQmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit KajQmlHelper(QObject *parent = 0);

    static void registerQmlTypes(QQmlApplicationEngine *engine);
    static void registerPlugins();
};

KAJ_END_NAMESPACE

#endif // KAJQMLHELPER_H
