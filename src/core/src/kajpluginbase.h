#ifndef KAJPLUGINBASE_H
#define KAJPLUGINBASE_H

#include "kajglobal.h"

#include <QEvent>
#include <typeinfo>

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QList>
#include <QDebug>
#include <QHash>
#include <QMetaObject>


#define CLASS_NAME(x) #x
#define KAJ_QML_URI "Kaj.Plugins"

#define KAJ_JAVA_NATIVE_METHOD(name, class, method) \
    Java_org_tooj_framework_plugins_ ## name ## _ ## class ## _ ## method

#define KAJ_JAVA_CLASS_NAME(name, class) \
    "org/tooj/framework/plugins/" #name "/" #class

#define KAJ_DECLARE_PLUGIN(x) \
    static KajPluginBaseRegistrar<x> __temp ## x;

class KajPluginRegisterHelper : public QObject
{
    Q_OBJECT
    static QHash<QString, void (*)()> plugins;
    static int n;
public:
    static void insert(QString name, void (init)());

    static void registerAll();
};

template<typename T>
class KajPluginBaseRegistrar : public QObject{

public:
    KajPluginBaseRegistrar()
    {
        QString className = T::staticMetaObject.className();
        KajPluginRegisterHelper::insert(className, &T::init);
    }

    ~KajPluginBaseRegistrar(){

    }


};
class KajPluginBase : public QObject
{
    Q_OBJECT

public:
    explicit KajPluginBase(QObject *parent = 0);

protected:
    virtual bool isSupported();
};

#endif // KAJPLUGINBASE_H
