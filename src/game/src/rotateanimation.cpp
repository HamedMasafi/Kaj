#include <QVariant>
#include <QDebug>
#include <QtMath>

#include "rotateanimation.h"

QT_BEGIN_NAMESPACE

class RotateAnimationPrivate{
private:
    RotateAnimation *q_ptr;
    Q_DECLARE_PUBLIC(RotateAnimation)

public:
    RotateAnimationPrivate(RotateAnimation *parent = 0):q_ptr(parent),
        speed(10),
        speedUp(0),
        duration(2000),
        target(0),
        from(-1),
        to(-1),
        property("rotation")
    {
    }

    float step;

    float speed;
    float speedUp;
    int duration;
    QString property;

    QObject *target;
    qreal from;
    qreal to;
};

/*!
 * \brief RotateAnimation::RotateAnimation
 * \param parent The parent object of animation
 */
RotateAnimation::RotateAnimation(QObject *parent) : QAbstractAnimation(parent),
    d_ptr(new RotateAnimationPrivate(this))
{

}

RotateAnimation::~RotateAnimation()
{

}

float RotateAnimation::speed() const
{
    Q_D(const RotateAnimation);
    return d->speed;
}

float RotateAnimation::speedUp() const
{
    Q_D(const RotateAnimation);
    return d->speedUp;
}

int RotateAnimation::duration() const
{
    Q_D(const RotateAnimation);
    return d->duration;
}

QObject *RotateAnimation::target()
{
    Q_D(RotateAnimation);
    return d->target;
}

qreal RotateAnimation::from() const
{
    Q_D(const RotateAnimation);
    return d->from;
}

qreal RotateAnimation::to() const
{
    Q_D(const RotateAnimation);
    return d->to;
}

bool RotateAnimation::running() const
{
    return state() == Running;
}

QString RotateAnimation::property() const
{
    Q_D(const RotateAnimation);
    return QString(d->property);
}

void RotateAnimation::setSpeed(float s)
{
    Q_D(RotateAnimation);
    d->speed = s;
}

void RotateAnimation::setSpeedUp(float s)
{
    Q_D(RotateAnimation);
    d->speedUp = s;
}

void RotateAnimation::setTarget(QObject *target)
{
    Q_D(RotateAnimation);
    if (d->target == target)
        return;

    d->target = target;
    emit targetChanged();
}

void RotateAnimation::setFrom(qreal startPosition)
{
    Q_D(RotateAnimation);
    if (d->from == startPosition)
        return;

    d->from = startPosition;
    emit fromChanged();
}

void RotateAnimation::setTo(qreal endPosition)
{
    Q_D(RotateAnimation);
    if (d->to == endPosition)
        return;

    d->to = endPosition;
    emit toChanged();
}

void RotateAnimation::setRunning(bool running)
{
    if (state() == Running)
        return;

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

void RotateAnimation::setProperty(const QString &property)
{
    Q_D(RotateAnimation);
    if (d->property == property)
        return;

    d->property =  property;
    emit propertyChanged();
}

/*!
 * \reimp
 */
void RotateAnimation::updateCurrentTime(int currentTime)
{
    Q_D(RotateAnimation);

    const char* ch = d->property.toLatin1().data();
    qreal rotation = d->target->property(ch).toFloat();

    if(rotation == d->to || currentTime >= d->duration){
        stop();
        return;
    }

    d->target->setProperty(ch, d->from + (d->step * (float)currentTime));
}

/*!
 * \reimp
 */
void RotateAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    Q_D(RotateAnimation);
    if(oldState == Stopped && newState == Running){
        qreal objectRotate = d->target->property(d->property.toLatin1().data()).toReal();
        if(d->from == -1)
            d->from = objectRotate;

        if(d->from < 0 || d->from > 360)
            d->from = (int)d->from % 360;

        qreal rangeMax = d->from + 180;
        qreal rangeMin = d->from - 180;

        while(d->to > rangeMax || d->to < rangeMin){
            if(d->to > rangeMax)
                d->to -= 360;

            if(d->to < rangeMin)
                d->to += 360;
        }

        d->duration = (qAbs(d->to - d->from) / d->speed);
        d->step = (d->to - d->from) / d->duration;

        emit started();
    }

    if(newState == Stopped){
        d->from = d->to;
        emit stopped();
    }
}

QT_END_NAMESPACE
