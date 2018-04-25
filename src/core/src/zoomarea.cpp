#include "zoomarea_p.h"
#include "zoomarea.h"
#include "scalecontainer.h"

#include <QDebug>
#include <QLineF>
#include <QTransform>
#include <QAnimationGroup>
#include <QPropertyAnimation>
#include <QTime>
#include <QParallelAnimationGroup>

#include "kajglobal.h"

QT_BEGIN_NAMESPACE

ZoomAreaPrivate::ZoomAreaPrivate(ZoomArea *parent)
    : q_ptr(parent), m_handleMouseEvents(true), m_totalScaleFactor(1),
      m_isActiveTouch(false), m_minScale(.25), m_maxScale(4), m_lastClickMsec(0)
{
    _mouseQpaTouchPoint.setId(-1);
}

void ZoomAreaPrivate::validateRect(QQuickItem *child, QRectF *rc,
                                   QRectF *output)
{
    Q_Q(ZoomArea);

    output->setTopLeft(rc->topLeft());
    output->setSize(rc->size());

    if ((output->width() / _originalChildsRect[child].width()) > m_maxScale
        || (output->height() / _originalChildsRect[child].height())
           > m_maxScale) {
        output->setWidth(_originalChildsRect[child].width() * m_maxScale);
        output->setHeight(_originalChildsRect[child].height() * m_maxScale);

        *output = QRectF();
        return;
    }

    if ((output->width() / _originalChildsRect[child].width()) < m_minScale
        || (output->height() / _originalChildsRect[child].height())
           < m_minScale) {
        output->setWidth(_originalChildsRect[child].width() * m_minScale);
        output->setHeight(_originalChildsRect[child].height() * m_minScale);

        *output = QRectF();
        return;
    }

    if (output->width() < q->width())
        output->moveLeft((q->width() - output->width()) / 2);
    else if (output->x() > 0)
        output->moveLeft(0);
    else if (output->x() + output->width() < q->width())
        output->moveLeft(q->width() - output->width());

    if (output->height() < q->height())
        output->moveTop((q->height() - output->height()) / 2);
    else if (output->y() > 0)
        output->moveTop(0);
    else if (output->y() + output->height() < q->height())
        output->moveTop(q->height() - output->height());
}

void ZoomAreaPrivate::copyTouchPoint(QTouchEvent::TouchPoint *from,
                                     QTouchEvent::TouchPoint *to)
{
    to->setState(from->state());

    to->setPos(from->pos());
    to->setScenePos(from->scenePos());
    to->setScreenPos(from->screenPos());

    to->setLastPos(from->lastPos());
    to->setLastScenePos(from->lastScenePos());
    to->setLastScreenPos(from->lastScreenPos());
}

void ZoomAreaPrivate::returnToBounds()
{
    Q_Q(ZoomArea);

    Q_ASSERT(q->childItems().count() == 1);

    QQuickItem *child = q->childItems().at(0);

    QRectF rc = child->boundingRect();
    rc.moveTo(child->position());
    QRectF output;

    validateRect(child, &rc, &output);

    if (output == QRectF())
        return;

    child->setPosition(output.topLeft());
    child->setSize(output.size());
}

void ZoomAreaPrivate::wrapChild(QQuickItem *child)
{
    Q_Q(ZoomArea);

    ScaleContainer *scaleContainer = new ScaleContainer(q);

    child->setParentItem(scaleContainer);
    scaleContainer->setChild(child);
    returnToBounds();

    _originalChildsRect[scaleContainer] = child->boundingRect();
}

void ZoomAreaPrivate::scaleRect(QRectF *rect, qreal delta, QPointF center)
{
    rect->setWidth(rect->width() * delta);
    rect->setHeight(rect->height() * delta);

    rect->moveTo(center.x() - (center.x() - rect->x()) * delta,
                 center.y() - (center.y() - rect->y()) * delta);
}

void ZoomAreaPrivate::scaleChild(QQuickItem *child, qreal delta, QPointF center)
{
    QRectF rc = child->boundingRect();
    rc.moveTo(child->position());

    rc.setWidth(rc.width() * delta);
    rc.setHeight(rc.height() * delta);

    rc.moveTo(center.x() - (center.x() - rc.x()) * delta,
              center.y() - (center.y() - rc.y()) * delta);

    childLastRect.moveTopLeft(rc.topLeft() - child->position());

    child->setPosition(rc.topLeft());
    child->setSize(rc.size());
}

void ZoomAreaPrivate::handleEvents(QEvent *event)
{
    QList<QTouchEvent::TouchPoint> touchPoints;

    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd: {
        QTouchEvent *touchEvent = static_cast<QTouchEvent *>(event);
        touchPoints = touchEvent->touchPoints();
        break;
    }
    case QEvent::MouseButtonPress:
    case QEvent::MouseMove:
    case QEvent::MouseButtonRelease: {
        QMouseEvent *me = static_cast<QMouseEvent *>(event);

        if (event->type() == QEvent::MouseMove) {
            _mouseQpaTouchPoint.setState(Qt::TouchPointMoved);

            _mouseQpaTouchPoint.setLastPos(_mouseQpaTouchPoint.pos());
            _mouseQpaTouchPoint.setLastScenePos(_mouseQpaTouchPoint.scenePos());
            _mouseQpaTouchPoint.setLastScreenPos(
                _mouseQpaTouchPoint.screenPos());
        } else if (event->type() == QEvent::MouseButtonRelease) {
            _mouseQpaTouchPoint.setState(Qt::TouchPointReleased);
            _touchPoints.remove(-1);
        } else { // QEvent::MouseButtonPress
            _mouseQpaTouchPoint.setState(Qt::TouchPointPressed);

            _mouseQpaTouchPoint.setLastPos(me->localPos());
            _mouseQpaTouchPoint.setLastScenePos(me->windowPos());
            _mouseQpaTouchPoint.setLastScreenPos(me->screenPos());

            _mouseQpaTouchPoint.setStartPos(me->pos());
            _mouseQpaTouchPoint.setStartScenePos(me->windowPos());
            _mouseQpaTouchPoint.setStartScreenPos(me->screenPos());

            //            _lastClickPoint = me->globalPos();

            //            childLastRect = child->boundingRect();
            //            childLastRect.moveTo(child->position());
            //            // _pressedTouchPoints.append(_mouseTouchPoint);
            _touchPoints.insert(-1, &_mouseQpaTouchPoint);
        }
        _mouseQpaTouchPoint.setPos(me->pos());
        _mouseQpaTouchPoint.setScenePos(me->windowPos());
        _mouseQpaTouchPoint.setScreenPos(me->screenPos());

        //        isMouseEvent = true;
        break;
    }
    default:
        qWarning("updateTouchData: unhandled event type %d", event->type());
        break;
    }

    foreach (QTouchEvent::TouchPoint point, touchPoints) {
        QTouchEvent::TouchPoint *to;

        if (_touchPoints.contains(point.id())) {
            to = _touchPoints.value(point.id());
        } else {
            to = new QTouchEvent::TouchPoint(point.id());

            to->setStartPos(point.startPos());
            to->setStartScenePos(point.startScenePos());
            to->setStartScreenPos(point.startScreenPos());

            _touchPoints.insert(point.id(), to);
            //            _touchPoints.insert(point.id(), to);
            //            childLastRect = child->boundingRect();
        }

        if (point.state() == Qt::TouchPointReleased) {
            int id = to->id();

            if (id != -1)
                delete to;

            _touchPoints.remove(id);
        } else {
            copyTouchPoint(&point, to);
        }
    }

    //    foreach (QTouchEvent::TouchPoint *point, _touchPoints) {
    //        if(point->state() == Qt::TouchPointReleased){
    //            int id = point->id();

    //            if(id != -1)
    //                delete point;

    //            _touchPoints.remove(id);

    //            returnToBounds();
    //        }
    //    }

    processTouchEvent();
}

void ZoomAreaPrivate::processTouchEvent()
{
    Q_Q(ZoomArea);

    QQuickItem *child = q->childItems().at(0);

    qDebug() << "_touchPoints.count()=" << _touchPoints.count();
    if (_touchPoints.count() == 0) {
        returnToBounds();
        childLastRect = child->boundingRect();
        childLastRect.moveTo(child->position());
    }

    if (_touchPoints.count() == 1 /* && !isActiveTouch*/) {
        const QTouchEvent::TouchPoint *touchPoint0 = _touchPoints.first();

        if (touchPoint0->state() == Qt::TouchPointReleased) {
            returnToBounds();

            if (m_lastClickMsec
                && (QTime::currentTime().msec() - m_lastClickMsec) < 600) {
                QPointF border
                    = (touchPoint0->scenePos() - touchPoint0->lastScenePos());
                QLineF borderLine = QLineF(touchPoint0->scenePos(),
                                           touchPoint0->lastScenePos());
                qDebug() << border.manhattanLength();
                if (borderLine.length() > 10) {
                    //                    QRectF rc = child->boundingRect();
                    //                    rc.moveTo(child->x() + border.x(),
                    //                    child->y() + border.y());
                    //                    QRectF output;
                    //                    validateRect(child, &rc, &output);
                    //                    QParallelAnimationGroup *animGroup =
                    //                    new QParallelAnimationGroup(q);

                    //                    QPropertyAnimation *propAnimX = new
                    //                    QPropertyAnimation(m_childGeomery,
                    //                    "x");
                    //                    propAnimX->setDuration(500);
                    //                    propAnimX->setStartValue(m_childGeomery.x());
                    //                    propAnimX->setEndValue(m_childGeomery.x()
                    //                    + (borderLine.dx() * 20));
                    //                    propAnimX->setEasingCurve(QEasingCurve::OutQuad);

                    //                    QPropertyAnimation *propAnimY = new
                    //                    QPropertyAnimation(m_childGeomery,
                    //                    "y");
                    //                    propAnimY->setDuration(500);
                    //                    propAnimY->setStartValue(m_childGeomery.y());
                    //                    propAnimY->setEndValue(m_childGeomery.y()
                    //                    + (borderLine.dy() * 20));
                    //                    propAnimY->setEasingCurve(QEasingCurve::OutQuad);

                    //                    animGroup->addAnimation(propAnimX);
                    //                    animGroup->addAnimation(propAnimY);
                    //                    animGroup->start();
                }
            }

            m_lastClickMsec = 0;
            //            _touchPoints.remove(touchPoint0->id());
        }
        if (touchPoint0->state() == Qt::TouchPointMoved) {
            m_lastClickMsec = QTime::currentTime().msec();
            child->setPosition(
                child->position()
                + (touchPoint0->scenePos() - touchPoint0->lastScenePos()));
        }

        //        if(touchPoint0->state() == Qt::TouchPointPressed)
        //            _lastChildPosition = child->position();
    }

    if (_touchPoints.count() == 2) {
        const QTouchEvent::TouchPoint *touchPoint0 = _touchPoints.first();
        const QTouchEvent::TouchPoint *touchPoint1 = _touchPoints.last();
        qDebug() << touchPoint0->lastPos();
        qDebug() << touchPoint1->lastPos();
        if (touchPoint0->state() == Qt::TouchPointPressed
            || touchPoint1->state() == Qt::TouchPointPressed) {
            //            _touchCenter = QLineF(touchPoint0->scenePos(),
            //            touchPoint1->scenePos()).pointAt(.5);
            //            _lastChildPosition = child->position();
        }

        if (touchPoint0->state() == Qt::TouchPointReleased
            || touchPoint1->state() == Qt::TouchPointReleased) {
            returnToBounds();
        } else {
            QPointF touchMiddle
                = lineMiddle(touchPoint0->scenePos(), touchPoint1->scenePos());

            QLineF lineGlobalPos(touchPoint0->scenePos(),
                                 touchPoint1->scenePos());
            QLineF lineLastGlobalPos(touchPoint0->lastScreenPos(),
                                     touchPoint1->lastScreenPos());
            QLineF lineStartGlobalPos(touchPoint0->startScreenPos(),
                                      touchPoint1->startScreenPos());
            qDebug() << "touchMiddle=" << touchMiddle;
            if (lineLastGlobalPos.length()) {
                //                child->setPosition(childLastRect.topLeft() +
                //                (lineGlobalPos.pointAt(.5) -
                //                lineStartGlobalPos.pointAt(.5)));
                scaleChild(child,
                           lineGlobalPos.length() / lineLastGlobalPos.length(),
                           touchMiddle);
                //                child->setPosition(child->position() +
                //                (touchPoint0->scenePos() -
                //                touchPoint0->lastScenePos()));

                child->setPosition(child->position()
                                   + (lineGlobalPos.pointAt(.5)
                                      - lineLastGlobalPos.pointAt(.5)));
            }
        }
    }
}

QPointF ZoomAreaPrivate::lineMiddle(QPointF pt1, QPointF pt2)
{
    return QPointF((pt1.x() + pt2.x()) / 2, (pt1.y() + pt2.y()) / 2);
}

QRectF ZoomAreaPrivate::childGeomery() const
{
    return m_childGeomery;
}

void ZoomAreaPrivate::setChildGeomery(QRectF childGeomery)
{
    if (m_childGeomery == childGeomery)
        return;

    m_childGeomery = childGeomery;
    //    emit childGeomeryChanged(childGeomery);
}

ZoomArea::ZoomArea(QQuickItem *parent)
    : QQuickItem(parent), d_ptr(new ZoomAreaPrivate(this))
{
    setAcceptedMouseButtons(Qt::LeftButton);
    setFiltersChildMouseEvents(true);
}

bool ZoomArea::handleMouseEvents() const
{
    Q_D(const ZoomArea);
    return d->m_handleMouseEvents;
}

qreal ZoomArea::minScale() const
{
    Q_D(const ZoomArea);
    return d->m_minScale;
}

qreal ZoomArea::maxScale() const
{
    Q_D(const ZoomArea);
    return d->m_maxScale;
}

qreal ZoomArea::childZoom() const
{
    return m_childZoom;
}

void ZoomArea::geometryChanged(const QRectF &newGeometry,
                               const QRectF &oldGeometry)
{
    Q_D(ZoomArea);
    Q_UNUSED(newGeometry);
    Q_UNUSED(oldGeometry);
    d->returnToBounds();
}

void ZoomArea::wheelEvent(QWheelEvent *event)
{
    Q_D(ZoomArea);

    if (!d->m_handleMouseEvents)
        return;

    //    childItems().at(0)->setTransformOriginPoint(event->pos());
    qreal delta = event->delta() / 100.;
    if (delta < 0)
        delta = 1 / -delta;

    foreach (QQuickItem *child, childItems()) {
        QRectF rc = child->boundingRect();
        QRectF output;
        rc.moveTo(child->position());
        d->scaleRect(&rc, delta, event->pos());
        d->validateRect(child, &rc, &output);
        //        d->scaleRect(&d->childLastRect, delta, QPointF(event->pos()));

        if (output != QRectF()
            && output.size() != child->boundingRect().size()) {
            child->setPosition(output.topLeft());
            child->setSize(output.size());
            d->returnToBounds();
        }
    }
}

bool ZoomArea::childMouseEventFilter(QQuickItem *item, QEvent *event)
{
    Q_D(ZoomArea);
    if (!isVisible() || !isEnabled())
        return QQuickItem::childMouseEventFilter(item, event);

    QVariant preventStealing = item->property("preventStealing");
    if (preventStealing.type() == QVariant::Bool && preventStealing.toBool()) {
qDebug() << "BACK";
        return QQuickItem::childMouseEventFilter(item, event);
    }

    switch (event->type()) {
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    case QEvent::MouseMove:
        if (d->m_handleMouseEvents)
            d->handleEvents(event);
        break;
    default:
        break;
    }

    return QQuickItem::childMouseEventFilter(item, event);
}

void ZoomArea::itemChange(QQuickItem::ItemChange change,
                          const QQuickItem::ItemChangeData &value)
{
    Q_D(ZoomArea);

    static bool isBusy = false;
    if (isBusy)
        return;
    if (change == QQuickItem::ItemChildAddedChange) {
        isBusy = true;
        if (/*!qobject_cast<ScaleContainer*>(value.item) && */ value.item
                ->parentItem() == this)
            d->wrapChild(value.item);
    }
    isBusy = false;
}

void ZoomArea::touchEvent(QTouchEvent *event)
{
    Q_D(ZoomArea);
    if (d->m_handleMouseEvents)
        d->handleEvents(event);
}

void ZoomArea::mousePressEvent(QMouseEvent *event)
{
    qDebug() << Q_FUNC_INFO;
    QQuickItem::mousePressEvent(event);
}

void ZoomArea::setHandleMouseEvents(bool handleMouseEvents)
{
    Q_D(ZoomArea);

    if (d->m_handleMouseEvents == handleMouseEvents)
        return;

    d->m_handleMouseEvents = handleMouseEvents;
    emit handleMouseEventsChanged(handleMouseEvents);
}

void ZoomArea::setMinScale(qreal minScale)
{
    Q_D(ZoomArea);
    if (d->m_minScale == minScale)
        return;

    d->m_minScale = minScale;
    emit minScaleChanged(minScale);
}

void ZoomArea::setMaxScale(qreal maxScale)
{
    Q_D(ZoomArea);
    if (d->m_maxScale == maxScale)
        return;

    d->m_maxScale = maxScale;
    emit maxScaleChanged(maxScale);
}

void ZoomArea::setChildZoom(qreal childZoom)
{
    Q_D(ZoomArea);

    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_childZoom, childZoom))
        return;

    foreach (QQuickItem *child, childItems()) {
        QRectF rc = child->boundingRect();
        QRectF output;
        rc.moveTo(child->position());
        d->scaleRect(&rc, childZoom, rc.center());
        d->validateRect(child, &rc, &output);
        //        d->scaleRect(&d->childLastRect, delta, QPointF(event->pos()));

        if (output != QRectF()
            && output.size() != child->boundingRect().size()) {
            child->setPosition(output.topLeft());
            child->setSize(output.size());
            d->returnToBounds();
        }
    }
    m_childZoom = childZoom;
    emit childZoomChanged(m_childZoom);
}

QT_END_NAMESPACE
