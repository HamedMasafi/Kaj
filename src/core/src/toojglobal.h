#ifndef KAJGLOBAL_H
#define KAJGLOBAL_H

#include <QtGlobal>

// class KAJ_EXPORT KAJGlobal
// This is added for header file exporter

#define KAJ_VERSION 0x000100
#define KAJ_VERSION_STR "0.1.0"
#define KAJ_QML_URL "Kaj"
#define KAJ_VERSION_MAJOR 1
#define KAJ_VERSION_MINOR 0


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

