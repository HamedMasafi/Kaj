#ifndef KAJAPPMODULE_H
#define KAJAPPMODULE_H

#include <QDebug>
#include "kajglobal.h"
#include <QQmlExtensionPlugin>


class KajAppModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri)
    {
        Q_ASSERT(QLatin1String(uri) == QLatin1String("Kaj.App"));

        qDebug() << "registerTypes" << KAJ_VERSION_STR;

    }

    void initializeEngine(QQmlEngine *engine, const char *uri)
    {
        Q_UNUSED(uri);
        Q_UNUSED(engine);
    }
};


#endif // KAJAPPMODULE_H
