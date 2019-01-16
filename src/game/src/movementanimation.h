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

#ifndef MOVEMENTANIMATION_H
#define MOVEMENTANIMATION_H

#include <QPointF>
#include <QAbstractAnimation>

#include "kajglobal.h"

class QPointF;

KAJ_BEGIN_NAMESPACE

class MovementAnimationPrivate;
class KAJ_EXPORT MovementAnimation : public QAbstractAnimation
{
    Q_OBJECT

    MovementAnimationPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(MovementAnimation)

    Q_PROPERTY(float speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(float speedUp READ speedUp WRITE setSpeedUp NOTIFY speedUpChanged)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QPointF from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QPointF to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    MovementAnimation(QObject *parent = 0);
    ~MovementAnimation();

    float speed() const;
    float speedUp() const;

    int duration() const;

    QObject *target();

    QPointF from() const;
    QPointF to() const;

    bool running() const;

public slots:
    void setSpeed(float s);
    void setSpeedUp(float s);
    void setTarget(QObject *target);
    void setFrom(QPointF from);
    void setTo(QPointF to);
    void setRunning(bool running);

signals:
    void speedChanged();
    void speedUpChanged();
    void targetChanged();
    void fromChanged();
    void toChanged();
    void runningChanged();
    void stopped();
    void started();

protected:
    void updateCurrentTime(int currentTime);
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

KAJ_END_NAMESPACE

#endif // MOVEMENTANIMATION_H
