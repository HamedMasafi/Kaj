#ifndef MOBILITY_H
#define MOBILITY_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Mobility : public QObject
{
    Q_OBJECT
public:
    enum Duration {
        SHORT = 0,
        LONG = 1
    };

    explicit Mobility(QObject *parent = nullptr);

signals:

public slots:
    void directCallNumber(QString number);
    void toast(QString text);
};

#endif // MOBILITY_H
