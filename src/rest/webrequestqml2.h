/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kaj is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef WEBREQUESTQML2_H
#define WEBREQUESTQML2_H

#include "webrequest.h"

KAJ_REST_BEGIN_NAMESPACE

class Pair;
class ExpireTime;
class WebRequestQml2 : public WebRequest
{
    Q_OBJECT
    Q_PROPERTY(QList<Pair*> headers READ headers WRITE setHeaders NOTIFY headersChanged)
    Q_PROPERTY(ExpireTime* expireTime READ expireTime WRITE setExpireTime NOTIFY expireTimeChanged)

    QList<Pair*> m_headers;
    ExpireTime* m_expireTime;

public:
    WebRequestQml2();

    QList<Pair*> headers() const;
    ExpireTime* expireTime() const;

public slots:
    void send();
    void setHeaders(QList<Pair*> headers);
    void setExpireTime(ExpireTime* expireTime);

signals:
    void headersChanged(QList<Pair*> headers);
    void expireTimeChanged(ExpireTime* expireTime);
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUESTQML_H
