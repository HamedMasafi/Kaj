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

#ifndef MOBILITY_H
#define MOBILITY_H

#include "kajglobal.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT Mobility : public QObject
{
    Q_OBJECT
public:
    enum ToastDuration {
        Short = 0,
        Long = 1
    };
    Q_ENUM(ToastDuration)

    enum FullScreenMode {
        LeanBack,
        Immersive,
        StickyImmersive
    };
    Q_ENUM(FullScreenMode)

    explicit Mobility(QObject *parent = nullptr);

signals:

public slots:
    void directCallNumber(QString number);
    void toast(QString text, ToastDuration duration = Short);
    int getStatusBarHeight();
    void setFullScreen(FullScreenMode mode = StickyImmersive);
};

KAJ_END_NAMESPACE

#endif // MOBILITY_H
