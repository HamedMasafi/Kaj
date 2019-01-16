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

#ifndef PLATFORMS_H
#define PLATFORMS_H

#include "kajglobal.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT Platforms : public QObject
{
    Q_OBJECT
public:
    explicit Platforms(QObject *parent = 0);

public slots:
    bool isMobile();
    bool isDesktop();
    bool isAndroid();
    bool isIos();
    bool isLinux();
    bool isWindows();
    bool isMacOsX();
};

KAJ_END_NAMESPACE

#endif // PLATFORMS_H
