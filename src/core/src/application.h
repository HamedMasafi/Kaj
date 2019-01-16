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

#ifndef APPLICATION_H
#define APPLICATION_H

#include "kajglobal.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

KAJ_BEGIN_NAMESPACE

class Application : public QObject
{
    Q_OBJECT
public:
    explicit Application(QObject *parent = nullptr);

    enum ApplicationState {
        ApplicationSuspended    = 0x00000000,
        ApplicationHidden       = 0x00000001,
        ApplicationInactive     = 0x00000002,
        ApplicationActive       = 0x00000004
    };

    Q_DECLARE_FLAGS(ApplicationStates, ApplicationState)
    Q_ENUM(ApplicationState)

private slots:
    void qApp_applicationStateChanged(Qt::ApplicationState state);

signals:
    void applicationStateChanged(ApplicationState state);

};

KAJ_END_NAMESPACE

#endif // APPLICATION_H
