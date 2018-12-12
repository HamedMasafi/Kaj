#ifndef KAJGLOBAL_H
#define KAJGLOBAL_H

#include <QtGlobal>

// class Kaj_EXPORT KajGlobal
// This is added for header file exporter

//#define KAJ_NAMESPACE Kaj
#define KAJ_QML_URL         "Kaj"
#define KAJ_VERSION_MAJOR   1
#define KAJ_VERSION_MINOR   0
#define KAJ_VERSION_PATCH   0
#define KAJ_VERSION_STR     "1.0.0"

#define KAJ_VERSION         QT_VERSION_CHECK(KAJ_VERSION_MAJOR, KAJ_VERSION_MINOR, KAJ_VERSION_PATCH)

#ifdef KAJ_NAMESPACE
#   define KAJ_BEGIN_NAMESPACE     namespace KAJ_NAMESPACE{
#   define KAJ_END_NAMESPACE       }
#   define KAJ_WRAP_NAMESPACE(x)   KAJ_NAMESPACE::x
#else
#   define KAJ_BEGIN_NAMESPACE
#   define KAJ_END_NAMESPACE
#   define KAJ_WRAP_NAMESPACE(x)   x
#endif


#define KAJ_DECL_SINGLETON(type)                        \
    type *type::_instance = Q_NULLPTR;

#define KAJ_SINGLETON(type)                             \
    static type *_instance;                             \
    public: static type *instance() {                   \
    if(!_instance)                                      \
        _instance = new type;                           \
    return _instance;                                   \
    }                                                   \
    static void setInstacne(type *ins){                 \
        _instance = ins;                                \
    } private:

#define KAJ_SINGLETON_UNIT(type)                        \
    static type *_instance;                             \
    public: static type *instance() {                   \
        if (_instance == nullptr)                       \
            _instance = new type;                       \
        return _instance;                               \
    }                                                   \
    static void setInstacne(type *ins){                 \
        if (_instance != Q_NULLPTR)                     \
            qDebug()                                    \
                << "Instance is not null"               \
                << _instance->objectName();             \
        _instance = ins;                                \
    } private:


#ifdef KAJ_COMPILE_STATIC
#    define KAJ_EXPORT
#else
#    if defined(BUILD_KAJ_CORE)
#        define KAJ_EXPORT Q_DECL_EXPORT
#    else
#        define KAJ_EXPORT Q_DECL_IMPORT
#    endif
#endif // BUILD_CORE

#endif // KAJGLOBAL_H

