#ifndef SHARE_H
#define SHARE_H

#include "kajpluginbase.h"

KAJ_BEGIN_NAMESPACE

class Share : public KajPluginBase
{
    Q_OBJECT

public:
    explicit Share(QObject *parent = 0);

    Q_INVOKABLE void shareApp();
    static void registerQmlType();
signals:

public slots:
    void share(QString &subject, QString &url);
};

KAJ_END_NAMESPACE

#endif // SHARE_H
