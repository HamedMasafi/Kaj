/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

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
