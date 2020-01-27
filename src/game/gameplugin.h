#ifndef PLUGIN_H
#define PLUGIN_H

#include <QQmlExtensionPlugin>

class KajBox2DPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
#if !defined(STATIC_PLUGIN_BOX2D)
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")
#endif

public:
    KajBox2DPlugin(QObject *parent = nullptr);

    void registerTypes(const char *uri);
};

#endif // PLUGIN_H
