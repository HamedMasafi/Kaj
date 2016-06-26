#ifndef SPEEDANIMATION_P
#define SPEEDANIMATION_P

#include <QVariant>

#include "speedanimation.h"

class SpeedAnimationPrivate
{
    SpeedAnimation *q_ptr;
    Q_DECLARE_PUBLIC(SpeedAnimation)

public:
    SpeedAnimationPrivate(SpeedAnimation *parent);

    qlonglong lenght(QVariant &v1, QVariant &v2);

    qreal speed;
    QVariant from;
    QVariant to;
    QEasingCurve easing;
    QObject *target;
    QString property;
    QString properties;
    QQmlListProperty<QObject> targets;
    QQmlListProperty<QObject> exclude;
};

#endif // SPEEDANIMATION_P

