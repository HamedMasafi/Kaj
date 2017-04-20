#include <QCoreApplication>
#include "kajpluginbase.h"

KajPluginBase::KajPluginBase(QObject *parent) : QObject(parent)
{
}

bool KajPluginBase::isSupported()
{
    return true;
}

QHash<QString, void (*)()> KajPluginRegisterHelper::plugins;
void KajPluginRegisterHelper::insert(QString name, void (init)())
{
    if(!plugins.keys().contains(name))
        plugins.insert(name, init);

}

void KajPluginRegisterHelper::registerAll(){
    foreach (QString className, plugins.keys()) {
        qDebug() << "Registering" << className << "...";
        plugins[className]();
    }
}

void registerAll(){
     KajPluginRegisterHelper::registerAll();
}

Q_COREAPP_STARTUP_FUNCTION(registerAll)
