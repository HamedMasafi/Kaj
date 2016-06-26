#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "../../core/src/toojpluginbase.h"

class Notification : public ToojPluginBase
{
    Q_OBJECT
public:
    explicit Notification(QObject *parent = 0);
    static void init();

public slots:
    void createNotification(QString text);
};

#endif // NOTIFICATION_H
