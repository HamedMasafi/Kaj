#include "platforms.h"

KAJ_BEGIN_NAMESPACE

Platforms::Platforms(QObject *parent) : QObject(parent)
{

}

bool Platforms::isMobile()
{
#if defined (Q_OS_ANDROID) || defined (Q_OS_IOS)
    return true;
#else
    return false;
#endif
}

bool Platforms::isDesktop()
{
#if (defined (Q_OS_LINUX) || defined (Q_OS_UNIX) || defined (Q_OS_WIN) || defined (Q_OS_MACX)) && !defined (Q_OS_ANDROID)
    return true;
#else
    return false;
#endif
}

bool Platforms::isAndroid()
{
#ifdef Q_OS_ANDROID
    return true;
#else
    return false;
#endif
}

bool Platforms::isIos()
{
#ifdef Q_OS_IOS
    return true;
#else
    return false;
#endif
}

bool Platforms::isLinux()
{
#ifdef Q_OS_LINUX
    return true;
#else
    return false;
#endif
}

bool Platforms::isWindows()
{
#ifdef Q_OS_WIN
    return true;
#else
    return false;
#endif
}

bool Platforms::isMacOsX()
{
#ifdef Q_OS_MACX
    return true;
#else
    return false;
#endif

}

KAJ_END_NAMESPACE
