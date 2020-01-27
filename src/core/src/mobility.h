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

#ifndef MOBILITY_H
#define MOBILITY_H

#include "kajglobal.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QVariant>

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT Mobility : public QObject
{
    Q_OBJECT
public:
    enum ToastDuration {
        Short = 0,
        Long = 1
    };
    Q_ENUM(ToastDuration)

    enum FullScreenMode {
        LeanBack,
        Immersive,
        StickyImmersive
    };
    Q_ENUM(FullScreenMode)

    enum ConnectionType {
        NONE        = -1,
        MOBILE      = 0,
        WIFI        = 1,
        MOBILE_MMS  = 2,
        MOBILE_SUPL = 3,
        MOBILE_DUN  = 4,
        MOBILE_HIPRI = 5,
        WIMAX       = 6,
        BLUETOOTH   = 7,
        DUMMY       = 8,
        ETHERNET    = 9,
        MOBILE_FOTA = 10,
        MOBILE_IMS  = 11,
        MOBILE_CBS  = 12,
        WIFI_P2P    = 13
    };
    Q_ENUM(ConnectionType)

    explicit Mobility(QObject *parent = nullptr);

signals:

public slots:
    void directCallNumber(QString number);
    void toast(QString text, ToastDuration duration = Short);
    int getStatusBarHeight();
    void setFullScreen(FullScreenMode mode = StickyImmersive);
    ConnectionType networkConnectionType() const;
    QVariant contacts();
};

KAJ_END_NAMESPACE

#endif // MOBILITY_H
