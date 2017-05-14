#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Notification : public QObject
{
    Q_OBJECT

public:
    enum Duration {
        SHORT = 0,
        LONG = 1
    };
    explicit Notification(QObject *parent = nullptr);

signals:

public slots:
    void message(QString text);

};

#endif // NOTIFICATION_H
