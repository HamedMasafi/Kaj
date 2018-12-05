#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include "kajpluginbase.h"

class Notification : public KajPluginBase
{
    Q_OBJECT
public:
    explicit Notification(QObject *parent = 0);
#if QT_QML_LIB
    static bool init(const QQmlApplicationEngine *engine);
#endif

public slots:
    void createNotification(QString text);
};

KAJ_DECLARE_QML_PLUGIN(Notification)

#endif // NOTIFICATION_H
