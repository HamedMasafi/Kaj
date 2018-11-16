#include <QVariant>
#include <QPointF>
#include <QDebug>
#include <QtMath>

#include "movementanimation.h"

KAJ_BEGIN_NAMESPACE

class MovementAnimationPrivate{
private:
    MovementAnimation *q_ptr;
    Q_DECLARE_PUBLIC(MovementAnimation)

public:
    MovementAnimationPrivate(MovementAnimation *parent = 0):q_ptr(parent),
        speed(10),
        speedUp(0),
        duration(2000),
        target(0),
        from(QPointF()),
        to(QPointF())
    {
    }

    float lenght() const {
        return sqrt(
                    pow(from.x() - to.x(), 2)
                    + pow(from.y() - to.y(), 2));
    }

    float stepX;
    float stepY;

    float speed;
    float speedUp;
    int duration;

    QObject *target;
    QPointF from;
    QPointF to;
};

/*!
 * \brief MovementAnimation::MovementAnimation
 * \param parent The parent object of animation
 */
MovementAnimation::MovementAnimation(QObject *parent) : QAbstractAnimation(parent),
    d_ptr(new MovementAnimationPrivate(this))
{

}

MovementAnimation::~MovementAnimation()
{

}

float MovementAnimation::speed() const
{
    Q_D(const MovementAnimation);
    return d->speed;
}

float MovementAnimation::speedUp() const
{
    Q_D(const MovementAnimation);
    return d->speedUp;
}

int MovementAnimation::duration() const
{
    Q_D(const MovementAnimation);
    return d->duration;
}

QObject *MovementAnimation::target()
{
    Q_D(MovementAnimation);
    return d->target;
}

QPointF MovementAnimation::from() const
{
    Q_D(const MovementAnimation);
    return d->from;
}

QPointF MovementAnimation::to() const
{
    Q_D(const MovementAnimation);
    return d->to;
}

bool MovementAnimation::running() const
{
    return state() == Running;
}

void MovementAnimation::setSpeed(float s)
{
    Q_D(MovementAnimation);
    d->speed = s;
}

void MovementAnimation::setSpeedUp(float s)
{
    Q_D(MovementAnimation);
    d->speedUp = s;
}

void MovementAnimation::setTarget(QObject *target)
{
    Q_D(MovementAnimation);
    if (d->target == target)
        return;

    d->target = target;
    emit targetChanged();
}

void MovementAnimation::setFrom(QPointF startPosition)
{
    Q_D(MovementAnimation);
    if (d->from == startPosition)
        return;

    d->from = startPosition;
    emit fromChanged();
}

void MovementAnimation::setTo(QPointF endPosition)
{
    Q_D(MovementAnimation);
    if (d->to == endPosition)
        return;

    d->to = endPosition;
    emit toChanged();
}

void MovementAnimation::setRunning(bool running)
{
    if(running){
        if (state() == Paused)
            resume();
        else
            start();
    }else{
        stop();
    }

    emit runningChanged();
}

/*!
 * \reimp
 */
void MovementAnimation::updateCurrentTime(int currentTime)
{
    Q_D(MovementAnimation);

    float x = d->target->property("x").toFloat();
    float y = d->target->property("y").toFloat();

    if((qAbs(x - d->to.x()) < d->stepX && qAbs(y - d->to.y()) < d->stepY) || currentTime >= d->duration){
        stop();
        d->target->setProperty("x", d->to.x());
        d->target->setProperty("y", d->to.y());
        return;
    }

    d->target->setProperty("x", d->from.x() + (d->stepX * currentTime));
    d->target->setProperty("y", d->from.y() + (d->stepY * currentTime));
}

/*!
 * \reimp
 */
void MovementAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    Q_D(MovementAnimation);
    if(oldState == Stopped && newState == Running){
        if(d->from == QPointF())
        {
            float x = d->target->property("x").toFloat();
            float y = d->target->property("y").toFloat();
            d->from == QPointF(x, y);
        } else {
            d->target->setProperty("x", d->from.x());
            d->target->setProperty("y", d->from.y());
        }

        /*
         * x = v.t
         * : x = d->lenght
         * : v = d->speed
         * : t = d->duration
         * t = x / v
        */
        d->duration = (d->lenght() / d->speed);
        d->stepX = (d->to.x() - d->from.x()) / d->duration;
        d->stepY = (d->to.y() - d->from.y()) / d->duration;

        emit started();
    }

    if(newState == Stopped){
//        d->from = d->to;
        emit stopped();
    }
}

KAJ_END_NAMESPACE
