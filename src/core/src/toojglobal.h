#ifndef TOOJGLOBAL_H
#define TOOJGLOBAL_H

#include <QtGlobal>

// class TOOJ_EXPORT ToojGlobal
// This is added for header file exporter

#define KAJ_VERSION 0x000100
#define KAJ_VERSION_STR "0.1.0"
#define KAJ_QML_URL "Kaj"
#define KAJ_VERSION_MAJOR 1
#define KAJ_VERSION_MINOR 0


#ifdef TOOJ_COMPILE_STATIC
#    define TOOJ_EXPORT
#else
#    if defined(BUILD_TOOJ_CORE)
#        define TOOJ_EXPORT Q_DECL_EXPORT
#    else
#        define TOOJ_EXPORT Q_DECL_IMPORT
#    endif
#endif // BUILD_CORE

#endif // TOOJGLOBAL_H

