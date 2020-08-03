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

#include "webrequestqml2.h"
#include "pair.h"
#include "expiretime.h"

KAJ_REST_BEGIN_NAMESPACE

WebRequestQml2::WebRequestQml2()
{

}

QList<Pair *> WebRequestQml2::headers() const
{
    return m_headers;
}

ExpireTime *WebRequestQml2::expireTime() const
{
    return m_expireTime;
}

void WebRequestQml2::setHeaders(QList<Pair *> headers)
{
    if (m_headers == headers)
        return;

    m_headers = headers;
    emit headersChanged(m_headers);
}

void WebRequestQml2::send()
{
    foreach (auto h, m_headers)
        setHeader(h->name(), h->value());
    setExpirationSeconds(m_expireTime->totalSecs());
}

void WebRequestQml2::setExpireTime(ExpireTime *expireTime)
{
    if (m_expireTime == expireTime)
        return;

    m_expireTime = expireTime;
    emit expireTimeChanged(m_expireTime);
}

KAJ_REST_END_NAMESPACE
