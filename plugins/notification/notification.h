#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "kajpluginbase.h"

class Notification : public KajPluginBase
{
    Q_OBJECT
public:
    explicit Notification(QObject *parent = 0);
    static void init();

public slots:
    void createNotification(QString text);
};

KAJ_DECLARE_CPP_PLUGIN(Notification)

#endif // NOTIFICATION_H
