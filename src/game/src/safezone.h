#ifndef SAFEZONE_H
#define SAFEZONE_H

#include <QObject>

class SafeZone : public QObject
{
    Q_OBJECT
public:
    explicit SafeZone(QObject *parent = nullptr);

signals:

};

#endif // SAFEZONE_H
