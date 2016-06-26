#ifndef SHARE_H
#define SHARE_H

#include "kajpluginbase.h"

class Share : public KajPluginBase
{
    Q_OBJECT

public:
    explicit Share(QObject *parent = 0);

    Q_INVOKABLE void shareApp();
    static void registerQmlType();
signals:

public slots:
};

#endif // SHARE_H
