#ifndef MOBILITY_H
#define MOBILITY_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Mobility : public QObject
{
    Q_OBJECT
public:
    explicit Mobility(QObject *parent = nullptr);

signals:

public slots:
    void callNumber(QString number);
    void toast(QString text);
};

#endif // MOBILITY_H
