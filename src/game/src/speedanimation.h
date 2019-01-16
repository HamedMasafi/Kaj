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

#ifndef SPEEDANIMATION_H
#define SPEEDANIMATION_H

#include <QPropertyAnimation>
#include <QQmlListProperty>

class SpeedAnimationPrivate;
class SpeedAnimation : public QPropertyAnimation
{
    Q_OBJECT

    SpeedAnimationPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(SpeedAnimation)

    Q_PROPERTY(qreal speed READ speed WRITE setSpeed NOTIFY speedChanged)
    //    Q_PROPERTY(int duration READ duration WRITE setDuration NOTIFY durationChanged)
    Q_PROPERTY(QVariant from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QVariant to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(QEasingCurve easing READ easing WRITE setEasing NOTIFY easingChanged)
    Q_PROPERTY(QObject *target READ target WRITE setTargetObject NOTIFY targetChanged)
    Q_PROPERTY(QString property READ property WRITE setProperty NOTIFY propertyChanged)
    Q_PROPERTY(QString properties READ properties WRITE setProperties NOTIFY propertiesChanged)
    Q_PROPERTY(QQmlListProperty<QObject> targets READ targets)
    Q_PROPERTY(QQmlListProperty<QObject> exclude READ exclude)

public:
    SpeedAnimation(QObject *parent = 0);

    qreal speed() const;
    QVariant from() const;
    QVariant to() const;
    QEasingCurve easing() const;
    QObject *target() const;
    QString property() const;
    QString properties() const;
    QQmlListProperty<QObject> targets() const;
    QQmlListProperty<QObject> exclude() const;

public slots:
    void setSpeed(qreal speed);
    void setFrom(QVariant from);
    void setTo(QVariant to);
    void setEasing(QEasingCurve easing);
    void setTargetObject(QObject * target);
    void setProperty(QString property);
    void setProperties(QString properties);

signals:
    void speedChanged(qreal speed);
    void fromChanged(QVariant from);
    void toChanged(QVariant to);
    void easingChanged(QEasingCurve easing);
    void targetChanged(QObject * target);
    void propertyChanged(QString property);
    void propertiesChanged(QString properties);

protected:
    void updateCurrentTime(int currentTime);
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

#endif // SPEEDANIMATION_H
