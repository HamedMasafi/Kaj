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

#ifndef WEBREQUESTMANAGER_H
#define WEBREQUESTMANAGER_H

#include "kajglobal.h"
#include <QMutex>
#include <QObject>

KAJ_BEGIN_NAMESPACE

class WebRequest;
class WebRequestManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged)
    Q_PROPERTY(QStringList loadingTesxs READ loadingTesxs NOTIFY loadingTesxsChanged)

    static WebRequestManager *_instance;
    QMutex mutex;

public:
    WebRequestManager();
    static WebRequestManager *instance();
    bool isBusy() const;

    friend class WebRequest;
    QStringList loadingTesxs() const;

private:
    int calls;
    QList<WebRequest*> requests;
    bool m_isBusy;

    void addCall(WebRequest *r);
    void removeCall(WebRequest *r);

public slots:
    void setIsBusy(bool isBusy);

signals:
    void isBusyChanged(bool isBusy);
    void loadingTesxsChanged(QStringList loadingTesxs);
};

KAJ_END_NAMESPACE

#endif // WEBREQUESTMANAGER_H
