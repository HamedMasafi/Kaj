#ifndef ZOOMAREA_H
#define ZOOMAREA_H

#include <QtCore/qglobal.h>
#include <QQuickItem>

#include "kajglobal.h"

QT_BEGIN_NAMESPACE

class ZoomAreaPrivate;
class KAJ_EXPORT ZoomArea : public QQuickItem
{
    Q_OBJECT

    ZoomAreaPrivate *d_ptr;
    Q_DECLARE_PRIVATE(ZoomArea)

    Q_PROPERTY(bool handleMouseEvents READ handleMouseEvents WRITE setHandleMouseEvents NOTIFY handleMouseEventsChanged)
    Q_PROPERTY(qreal minScale READ minScale WRITE setMinScale NOTIFY minScaleChanged)
    Q_PROPERTY(qreal maxScale READ maxScale WRITE setMaxScale NOTIFY maxScaleChanged)

public:
    ZoomArea(QQuickItem *parent = 0);

    bool handleMouseEvents() const;

    qreal minScale() const;

    qreal maxScale() const;

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

public slots:
    void setHandleMouseEvents(bool handleMouseEvents);
    void setMinScale(qreal minScale);
    void setMaxScale(qreal maxScale);
};

QML_DECLARE_TYPE(ZoomArea)

QT_END_NAMESPACE

#endif // ZOOMAREA_H
