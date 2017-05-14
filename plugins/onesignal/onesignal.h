#ifndef ONESIGNAL_H
#define ONESIGNAL_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <kajpluginbase.h>

class QQmlApplicationEngine;
class OneSignal : public KajPluginBase
{
    Q_OBJECT
    KAJ_SINGLETON(OneSignal)

    Q_PROPERTY(QString applicationId READ applicationId WRITE setApplicationId NOTIFY applicationIdChanged)

    QString m_applicationId;
    bool isRegistered;

public:
    explicit OneSignal(QObject *parent = nullptr);
    static void init();
    static void init(const QQmlApplicationEngine *engine);

    QString applicationId() const;

signals:
    void signalRecived(QString title, QString body);
    void signalOpened(QString title, QString body);

    void applicationIdChanged(QString applicationId);

public slots:
    void setApplicationId(QString applicationId);

private:
    void initOneSignal();
};

KAJ_DECLARE_CPP_PLUGIN(OneSignal)
KAJ_DECLARE_QML_PLUGIN(OneSignal)

#endif // ONESIGNAL_H
