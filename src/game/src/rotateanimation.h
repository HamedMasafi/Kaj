#ifndef ROTATEANIMATION_H
#define ROTATEANIMATION_H

#include <QAbstractAnimation>

#include "kajglobal.h"

KAJ_BEGIN_NAMESPACE

class RotateAnimationPrivate;
class KAJ_EXPORT RotateAnimation : public QAbstractAnimation
{
    Q_OBJECT

    RotateAnimationPrivate *const d_ptr;
    Q_DECLARE_PRIVATE(RotateAnimation)

    Q_PROPERTY(float speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(float speedUp READ speedUp WRITE setSpeedUp NOTIFY speedUpChanged)
    Q_PROPERTY(QObject* target READ target WRITE setTarget NOTIFY targetChanged)
    Q_PROPERTY(qreal from READ from WRITE setFrom NOTIFY fromChanged)
    Q_PROPERTY(qreal to READ to WRITE setTo NOTIFY toChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)
    Q_PROPERTY(QString property READ property WRITE setProperty NOTIFY propertyChanged)

public:
    RotateAnimation(QObject *parent = 0);
    ~RotateAnimation();

    float speed() const;
    float speedUp() const;

    int duration() const;

    QObject *target();

    qreal from() const;
    qreal to() const;

    bool running() const;

    QString property() const;

public slots:
    void setSpeed(float s);
    void setSpeedUp(float s);

    void setTarget(QObject *target);

    void setFrom(qreal from);

    void setTo(qreal to);

    void setRunning(bool running);

    void setProperty(const QString &property);

signals:
    void speedChanged();
    void speedUpChanged();
    void targetChanged();
    void fromChanged();
    void toChanged();
    void runningChanged();
    void stopped();
    void started();
    void propertyChanged();

protected:
    void updateCurrentTime(int currentTime);
    void updateState(QAbstractAnimation::State newState, QAbstractAnimation::State oldState);
};

KAJ_END_NAMESPACE

#endif // ROTATEANIMATION_H
