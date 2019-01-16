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

#ifndef ZOOMAREA_P_H
#define ZOOMAREA_P_H

#include "zoomarea.h"

KAJ_BEGIN_NAMESPACE

class ZoomAreaPrivate
{
    ZoomArea *q_ptr;
    Q_DECLARE_PUBLIC(ZoomArea)
    Q_PROPERTY(QRectF childGeomery READ childGeomery WRITE setChildGeomery NOTIFY childGeomeryChanged)

public:
    ZoomAreaPrivate(ZoomArea *parent);

    QPoint _lastClickPoint;
    QPointF _lastChildPosition;
    QPointF _touchCenter;
    QTouchEvent::TouchPoint _touchPoint;
    QTouchEvent::TouchPoint _mouseQpaTouchPoint;

    QMap<int, QTouchEvent::TouchPoint*> _touchPoints;

    QMap<QQuickItem*, QRectF> _originalChildsRect;

    QRectF childLastRect;


    bool m_handleMouseEvents;
    qreal m_totalScaleFactor;
    bool m_isActiveTouch;
    qreal m_minScale;
    qreal m_maxScale;
    int m_lastClickMsec;

    void validateRect(QQuickItem *child, QRectF *rc, QRectF *output);
    void copyTouchPoint(QTouchEvent::TouchPoint *from, QTouchEvent::TouchPoint *to);
    void updateGesture();
    void returnToBounds();
    void wrapChild(QQuickItem *child);
    void scaleRect(QRectF *rect, qreal delta, QPointF center);
    void scaleChild(QQuickItem *child, qreal delta, QPointF center);
    void handleEvents(QEvent *event);
    void processTouchEvent();
    QPointF lineMiddle(QPointF pt1, QPointF pt2);
    QRectF childGeomery() const;

public slots:
    void setChildGeomery(QRectF childGeomery);

signals:
    void childGeomeryChanged(QRectF childGeomery);

private:
    QRectF m_childGeomery;
};

KAJ_END_NAMESPACE

#endif // ZOOMAREA_P_H

