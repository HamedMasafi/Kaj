#ifndef CAFEBAZAARPLUGIN_H
#define CAFEBAZAARPLUGIN_H

#include "kajpluginbase.h"


class CafeBazaarPlugin : public KajPluginBase
{
    Q_OBJECT
    KAJ_SINGLETON(CafeBazaarPlugin)

    Q_PROPERTY(QString publicKey READ publicKey WRITE setPublicKey NOTIFY publicKeyChanged)

    QString m_publicKey;

public:
    explicit CafeBazaarPlugin(QObject *parent = 0);

    QString publicKey() const;

public slots:
//    void checkForUpdate();
    void payment(QString name);
//    void openBazaar();

    static bool init();
    bool isSupported();

    void setPublicKey(QString publicKey);

signals:
    void result(bool isSuccessfull, QString name);
    void publicKeyChanged(QString publicKey);
};

KAJ_DECLARE_CPP_PLUGIN(CafeBazaarPlugin)

#endif // CAFEBAZAARPLUGIN_H
