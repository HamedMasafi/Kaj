#include <QCoreApplication>
#include "kajpluginbase.h"

KajPluginBase::KajPluginBase(QObject *parent) : QObject(parent)
{
}

bool KajPluginBase::isSupported()
{
    return true;
}

KAJ_DECL_SINGLETON(KajPluginRegisterHelper)

//QHash<QString, void (*)()> KajPluginRegisterHelper::plugins;




void registerAll(){
//     KajPluginRegisterHelper::registerAll();
}

Q_COREAPP_STARTUP_FUNCTION(registerAll)
