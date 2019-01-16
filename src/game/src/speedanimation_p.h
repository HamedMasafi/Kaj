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

#ifndef SPEEDANIMATION_P
#define SPEEDANIMATION_P

#include <QVariant>

#include "speedanimation.h"

class SpeedAnimationPrivate
{
    SpeedAnimation *q_ptr;
    Q_DECLARE_PUBLIC(SpeedAnimation)

public:
    SpeedAnimationPrivate(SpeedAnimation *parent);

    qlonglong lenght(QVariant &v1, QVariant &v2);

    qreal speed;
    QVariant from;
    QVariant to;
    QEasingCurve easing;
    QObject *target;
    QString property;
    QString properties;
    QQmlListProperty<QObject> targets;
    QQmlListProperty<QObject> exclude;
};

#endif // SPEEDANIMATION_P

