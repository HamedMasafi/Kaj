#ifndef KAJGAMEPLUGIN_H
#define KAJGAMEPLUGIN_H

#include "kajglobal.h"
#include <QQmlExtensionPlugin>

class KAJ_EXPORT KajGamePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
#if !defined(KAJ_COMPILE_STATIC)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
#endif

public:
    KajGamePlugin(QObject *parent = 0);
    void registerTypes(const char *uri);
};

#endif // KAJGAMEPLUGIN_H
