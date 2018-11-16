#ifndef MOBILITY_H
#define MOBILITY_H

#include "kajglobal.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT Mobility : public QObject
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

KAJ_END_NAMESPACE

#endif // MOBILITY_H
