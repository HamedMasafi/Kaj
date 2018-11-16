#ifndef KAJPLUGINBASE_H
#define KAJPLUGINBASE_H

#include "kajglobal.h"

#include <typeinfo>

#include <QEvent>
#include <QQmlApplicationEngine>
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QList>
#include <QDebug>
#include <QHash>
#include <QMetaObject>

#define CLASS_NAME(x) #x
#define KAJ_QML_URI "Kaj.Plugins"

#define KAJ_PLUGIN_QML_URI(x) "Kaj." #x

#define KAJ_JAVA_NATIVE_METHOD(class, method) \
    JNIEXPORT void JNICALL Java_org_kaj_plugins_ ## class ## _ ## method

#define KAJ_JAVA_CLASS_NAME(class) \
    "org/kaj/plugins/" #class

#define KAJ_DECLARE_PLUGIN(x, type) \
    namespace { \
    static const struct x ## _registrator_class_ ## type { \
        inline x ## _registrator_class_ ## type() { \
            QString className(x::staticMetaObject.className()); \
            KajPluginRegisterHelper::instance()->insert ## type(className, &x::init); \
    } \
    } x ## _registrator_class_instance_ ## type; \
}

#ifdef __cplusplus
#define KAJ_BEGIN_JNI_METHODS extern "C" {
#define KAJ_END_JNI_METHODS             }
#else
#define KAJ_BEGIN_JNI_METHODS
#define KAJ_END_JNI_METHODS
#endif

#define KAJ_DECLARE_CPP_PLUGIN(x) \
    KAJ_DECLARE_PLUGIN(x, Cpp)

#define KAJ_DECLARE_QML_PLUGIN(x) \
    KAJ_DECLARE_PLUGIN(x, Qml)


class KajPluginRegisterHelper : public QObject
{
    Q_OBJECT
    QHash<QString, bool (*)()> plugins;
    QHash<QString, bool (*)(const QQmlApplicationEngine *engine)> qmlPlugins;
    int n;

    KAJ_SINGLETON(KajPluginRegisterHelper)

public:

    void insertCpp(QString name, bool (init)())
    {
        if(!plugins.keys().contains(name))
            plugins.insert(name, init);
    }

    void insertQml(QString name, bool (init)(const QQmlApplicationEngine *engine))
    {
        if(!qmlPlugins.keys().contains(name))
            qmlPlugins.insert(name, init);
    }

    void registerPlugins(){
        foreach (QString className, plugins.keys()) {
            bool ok = plugins[className]();
            qInfo("Registering cpp plugin %s... %s",
                  qPrintable(className),
                  ok ? "OK" : "Error");
        }
    }

    void registerPlugins(QQmlApplicationEngine *engine){
        foreach (QString className, qmlPlugins.keys()) {
            bool ok = qmlPlugins[className](engine);
            qInfo("Registering qml plugin %s... %s",
                  qPrintable(className),
                  ok ? "OK" : "Error");
        }
    }

    void registerAll(QQmlApplicationEngine *engine){
        registerPlugins();
        registerPlugins(engine);
    }
};

//Depreacted!
template<typename T>
class KajPluginBaseRegistrar : public QObject{

public:
    enum PluginType{
        Cpp,
        Qml
    };

    KajPluginBaseRegistrar()
    {

    }

    KajPluginBaseRegistrar(PluginType type)
    {
        QString className(T::staticMetaObject.className());

        if(type == Cpp)
            KajPluginRegisterHelper::insertCpp(className, &T::init);

        if(type == Qml)
            KajPluginRegisterHelper::insertQml(className, &T::init);
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
