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
#if QT_QML_LIB
    static bool init(const QQmlApplicationEngine *engine);
#endif
signals:

public slots:
    void shareLink(const QString &subject, const QString &url);
};

KAJ_END_NAMESPACE

KAJ_DECLARE_QML_PLUGIN(Share)

#endif // SHARE_H
