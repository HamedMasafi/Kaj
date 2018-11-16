#include "speedanimation_p.h"
#include "speedanimation.h"

#include <QColor>
#include <QLine>
#include <QLineF>
#include <QSize>
#include <QSizeF>
#include <QPoint>
#include <QPointF>
#include <QVariant>
#include <QtMath>

#define LENGTH_POINT(a, b) sqrt(            \
    pow(a.x() - b.x(), 2)                   \
    + pow(a.y() - b.y(), 2));

#define LENGTH_SIZE(a, b) sqrt(             \
    pow(a.width() - b.width(), 2)           \
    + pow(a.height() - b.height(), 2));

#define LENGTH_LINE(a, b) sqrt(             \
    pow(a.dx() - b.dx(), 2)                 \
    + pow(a.dy() - b.dy(), 2))

SpeedAnimationPrivate::SpeedAnimationPrivate(SpeedAnimation *parent) :
        q_ptr(parent),
        target(0)
{

}

qlonglong SpeedAnimationPrivate::lenght(QVariant &v1, QVariant &v2)
{
    QVariant::Type t1 = v1.type();
    QVariant::Type t2 = v2.type();

    if(t1 != t2){
        qWarning("Types are not equal");
        return 0;
    }

    switch (t1) {
    case QMetaType::Int:
        return v2.toInt() - v1.toInt();

    case QVariant::UInt:
        return v2.toUInt() - v1.toUInt();

    case QVariant::Double:
        return v2.toDouble() - v1.toDouble();

    case QVariant::Line:
        return LENGTH_LINE(v2.toLine(), v1.toLine());

    case QVariant::LineF:
        return LENGTH_LINE(v2.toLineF(), v1.toLineF());

    case QVariant::Point:
        return LENGTH_POINT(v2.toPoint(), v1.toPoint());

    case QVariant::PointF:
        return LENGTH_POINT(v2.toPointF(), v1.toPointF());

    case QVariant::Size:
        return LENGTH_SIZE(v2.toSize(), v1.toSize());

    case QVariant::SizeF:
        return LENGTH_SIZE(v2.toSizeF(), v1.toSizeF());

    case QVariant::Color:
        return v2.value<QColor>().rgb() - v1.value<QColor>().rgb();

    default:
        qWarning("Types is not supported");
        return 0;
    }
}

SpeedAnimation::SpeedAnimation(QObject *parent) : QPropertyAnimation(parent),
    d_ptr(new SpeedAnimationPrivate(this))
{

}

void SpeedAnimation::setSpeed(qreal speed)
{
    Q_D(SpeedAnimation);

    if (d->speed == speed)
        return;

    d->speed = speed;
    emit speedChanged(speed);
}

void SpeedAnimation::setFrom(QVariant from)
{
    Q_D(SpeedAnimation);

    if (d->from == from)
        return;

    d->from = from;
    emit fromChanged(from);
}

void SpeedAnimation::setTo(QVariant to)
{
    Q_D(SpeedAnimation);

    if (d->to == to)
        return;

    d->to = to;
    emit toChanged(to);
}

void SpeedAnimation::setEasing(QEasingCurve easing)
{
    Q_D(SpeedAnimation);

    if (d->easing == easing)
        return;

    d->easing = easing;
    emit easingChanged(easing);
}

void SpeedAnimation::setTargetObject(QObject *target)
{
    Q_D(SpeedAnimation);

    if (d->target == target)
        return;

    d->target = target;
    emit targetChanged(target);
}

void SpeedAnimation::setProperty(QString property)
{
    Q_D(SpeedAnimation);

    if (d->property == property)
        return;

    d->property = property;
    emit propertyChanged(property);
}

void SpeedAnimation::setProperties(QString properties)
{
    Q_D(SpeedAnimation);

    if (d->properties == properties)
        return;

    d->properties = properties;
    emit propertiesChanged(properties);
}

qreal SpeedAnimation::speed() const
{
    Q_D(const SpeedAnimation);
    return d->speed;
}

QVariant SpeedAnimation::from() const
{
    Q_D(const SpeedAnimation);
    return d->from;
}

QVariant SpeedAnimation::to() const
{
    Q_D(const SpeedAnimation);
    return d->to;
}

QEasingCurve SpeedAnimation::easing() const
{
    Q_D(const SpeedAnimation);
    return d->easing;
}

QObject *SpeedAnimation::target() const
{
    Q_D(const SpeedAnimation);
    return d->target;
}

QString SpeedAnimation::property() const
{
    Q_D(const SpeedAnimation);
    return d->property;
}

QString SpeedAnimation::properties() const
{
    Q_D(const SpeedAnimation);
    return d->properties;
}

QQmlListProperty<QObject> SpeedAnimation::targets() const
{
    Q_D(const SpeedAnimation);
    return d->targets;
}

QQmlListProperty<QObject> SpeedAnimation::exclude() const
{
    Q_D(const SpeedAnimation);
    return d->exclude;
}

void SpeedAnimation::updateCurrentTime(int currentTime)
{
    Q_UNUSED(currentTime);
}

void SpeedAnimation::updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState)
{
    if(oldState == Stopped && newState == Running){
//        d->duration = (d->lenght(startValue(), endValue()) / d->speed);
    }

    QPropertyAnimation::updateState(oldState, newState);
}


