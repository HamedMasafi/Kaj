#ifndef KAJQMLCOREMODULE_H
#define KAJQMLCOREMODULE_H

#include <QQmlExtensionPlugin>

class KajQmlCoreModule : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID QQmlExtensionInterface_iid)

public:
    KajQmlCoreModule();

public:
    void registerTypes(const char *uri);

    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // KAJQMLCOREMODULE_H
