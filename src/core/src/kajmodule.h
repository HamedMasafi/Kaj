#ifndef KAJMODULE_H
#define KAJMODULE_H

#include <QtCore/qglobal.h>
#include <QQmlExtensionPlugin>

class QQmlEngine;
class KajModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};



#endif // KAJMODULE_H
