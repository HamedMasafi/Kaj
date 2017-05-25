#include "swipegesturemanager_p.h"
#include "swipegesturemanager.h"

#include <QMouseEvent>
#include <QPoint>
#include <QDebug>

KAJ_BEGIN_NAMESPACE

SwipeGestureManagerPrivate::SwipeGestureManagerPrivate(SwipeGestureManager *parent) : q_ptr(parent)
{

}

SwipeGestureManager::SwipeGestureManager(QQuickItem *parent) :
    QQuickItem(parent), d_ptr(new SwipeGestureManagerPrivate(this))
{
    Q_D(SwipeGestureManager);
    d->state = Unknown;
    d->minimum = 10;
    d->orientation = Qt::Horizontal;
    setFiltersChildMouseEvents(true);
}

void SwipeGestureManager::setMinimum(int min)
{
    Q_D(SwipeGestureManager);
    if(d->minimum == min)
        return;

    d->minimum = min;
    emit minimumChanged();
}

int SwipeGestureManager::minimum() const
{
    Q_D(const SwipeGestureManager);
    return d->minimum;
}

void SwipeGestureManager::setOrientation(int ori)
{
    Q_D(SwipeGestureManager);
    if(d->orientation == ori)
        return;

    d->orientation = ori;
    emit orientationChanged();
}

int SwipeGestureManager::orientation() const
{
    Q_D(const SwipeGestureManager);
    return d->orientation;
}

int SwipeGestureManager::mouseX() const
{
    Q_D(const SwipeGestureManager);
    return d->position.x();
}

int SwipeGestureManager::mouseY() const
{
    Q_D(const SwipeGestureManager);
    return d->position.y();
}

bool SwipeGestureManager::childMouseEventFilter(QQuickItem *item, QEvent *e)
{
    Q_D(SwipeGestureManager);
    QMouseEvent *mevent = static_cast<QMouseEvent*>(e);
    if(e->type() == QEvent::MouseMove)
    {
        if(d->state == NotGrabbed)
            return QQuickItem::childMouseEventFilter(item, e);
        else
            if(d->state == Grabbed)
            {
                d->position = mapFromItem(item, mevent->pos()).toPoint();
                emit mouseXChanged();
                emit mouseYChanged();
                emit positionChanged();
                return true;
            }
    }
    else
        if(d->state != Unknown && e->type() != QEvent::MouseButtonRelease)
            return QQuickItem::childMouseEventFilter(item, e);

    switch(static_cast<int>(mevent->type()))
    {
    case QEvent::MouseButtonPress:
        d->pin = mevent->pos();
        break;

    case QEvent::MouseButtonRelease:
        if(d->state == Grabbed)
            emit released();

        d->position = QPoint(0,0);
        d->state = Unknown;
        break;

    case QEvent::MouseMove:
    {
        const int dx = qAbs(mevent->pos().x() - d->pin.x());
        const int dy = qAbs(mevent->pos().y() - d->pin.y());
        if(dx > d->minimum)
        {
            d->state = d->orientation == Qt::Horizontal ? Grabbed : NotGrabbed;
            if(d->state == Grabbed)
            {
                d->position = mapFromItem(item, mevent->pos()).toPoint();
                emit pressed();
                emit mouseXChanged();
                emit mouseYChanged();
                emit positionChanged();
            }
            return true;
        }
        else
            if(dy > d->minimum)
            {
                d->state = d->orientation==Qt::Horizontal? NotGrabbed : Grabbed;
                if(d->state == Grabbed)
                {
                    d->position = mapFromItem(item, mevent->pos()).toPoint();
                    emit pressed();
                    emit mouseXChanged();
                    emit mouseYChanged();
                    emit positionChanged();
                }
                return true;
            }
    }
        break;
    }

    return QQuickItem::childMouseEventFilter(item, e);
}

SwipeGestureManager::~SwipeGestureManager()
{
    delete d_ptr;
}

KAJ_END_NAMESPACE
