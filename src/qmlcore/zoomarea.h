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

#ifndef ZOOMAREA_H
#define ZOOMAREA_H

#include <QtCore/qglobal.h>
#include <QQuickItem>

#include "kajglobal.h"

KAJ_BEGIN_NAMESPACE

class ZoomAreaPrivate;
class KAJ_EXPORT ZoomArea : public QQuickItem
{
    Q_OBJECT

    ZoomAreaPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ZoomArea)

    Q_PROPERTY(bool handleMouseEvents READ handleMouseEvents WRITE setHandleMouseEvents NOTIFY handleMouseEventsChanged)
    Q_PROPERTY(qreal minScale READ minScale WRITE setMinScale NOTIFY minScaleChanged)
    Q_PROPERTY(qreal maxScale READ maxScale WRITE setMaxScale NOTIFY maxScaleChanged)
    Q_PROPERTY(qreal childZoom READ childZoom WRITE setChildZoom NOTIFY childZoomChanged)

    qreal m_childZoom;

public:
    ZoomArea(QQuickItem *parent = 0);

    bool handleMouseEvents() const;

    qreal minScale() const;

    qreal maxScale() const;

    qreal childZoom() const;

protected:
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);

    void wheelEvent(QWheelEvent *event);
    bool childMouseEventFilter(QQuickItem *item, QEvent *event);
    void itemChange(ItemChange change, const ItemChangeData & value);
    void touchEvent(QTouchEvent *event);

    void mousePressEvent(QMouseEvent *event);
signals:

    void handleMouseEventsChanged(bool handleMouseEvents);

    void minScaleChanged(qreal minScale);

    void maxScaleChanged(qreal maxScale);

    void childZoomChanged(qreal childZoom);

public slots:
    void setHandleMouseEvents(bool handleMouseEvents);
    void setMinScale(qreal minScale);
    void setMaxScale(qreal maxScale);
    void setChildZoom(qreal childZoom);
};

KAJ_END_NAMESPACE

QML_DECLARE_TYPE(KAJ_WRAP_NAMESPACE(ZoomArea))

#endif // ZOOMAREA_H
