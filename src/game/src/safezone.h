#ifndef SAFEZONE_H
#define SAFEZONE_H

#include <QObject>
#include <QSize>

class SafeZone : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QSize contentSize READ contentSize WRITE setContentSize NOTIFY contentSizeChanged)
    Q_PROPERTY(QSize windowSize READ windowSize WRITE setWindowSize NOTIFY windowSizeChanged)

    Q_PROPERTY(qreal contentScale READ contentScale WRITE setContentScale NOTIFY contentScaleChanged)
    Q_PROPERTY(qreal backgroundScale READ backgroundScale WRITE setBackgroundScale NOTIFY backgroundScaleChanged)

    QSize m_contentSize;
    QSize m_windowSize;
    qreal m_contentScale;
    qreal m_backgroundScale;
    QSizeF scales;

public:
    explicit SafeZone(QObject *parent = nullptr);

    QSize contentSize() const;
    QSize windowSize() const;
    qreal contentScale() const;
    qreal backgroundScale() const;

public Q_SLOTS:
    void recalculate();

    void setContentSize(QSize contentSize);
    void setWindowSize(QSize windowSize);
    void setContentScale(qreal contentScale);
    void setBackgroundScale(qreal backgroundScale);

signals:
    void contentSizeChanged(QSize contentSize);
    void windowSizeChanged(QSize windowSize);
    void contentScaleChanged(qreal contentScale);
    void backgroundScaleChanged(qreal backgroundScale);
};

#endif // SAFEZONE_H
