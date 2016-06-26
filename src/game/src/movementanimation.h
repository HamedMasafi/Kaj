#ifndef MOVEMENTANIMATION_H
#define MOVEMENTANIMATION_H

#include <QPointF>
#include <QAbstractAnimation>

#include "kajglobal.h"

QT_BEGIN_NAMESPACE

class QPointF;
class MovementAnimationPrivate;
class KAJ_EXPORT MovementAnimation : public QAbstractAnimation
{
    Q_OBJECT

    MovementAnimationPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(MovementAnimation)

    Q_PROPERTY(float speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(float speedUp READ speedUp WRITE setSpeedUp NOTIFY speedUpChanged)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(QPointF from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(QPointF to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    MovementAnimation(QObject *parent = 0);
    ~MovementAnimation();

    float speed() const;
    float speedUp() const;

    int duration() const;

    QObject *target();

    QPointF from() const;
    QPointF to() const;

    bool running() const;

public slots:
    void setSpeed(float s);
    void setSpeedUp(float s);
    void setTarget(QObject *target);
    void setFrom(QPointF from);
    void setTo(QPointF to);
    void setRunning(bool running);

signals:
    void speedChanged();
    void speedUpChanged();
    void targetChanged();
    void fromChanged();
    void toChanged();
    void runningChanged();
    void stopped();
    void started();

protected:
    void updateCurrentTime(int currentTime);
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

QT_END_NAMESPACE

#endif // MOVEMENTANIMATION_H
