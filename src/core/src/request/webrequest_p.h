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

#ifndef WEBREQUEST_P_H
#define WEBREQUEST_P_H

#include "webrequest.h"

class QNetworkAccessManager;

KAJ_BEGIN_NAMESPACE

class WebRequest;
class WebRequestPrivate {
    WebRequest *q_ptr;
    Q_DECLARE_PUBLIC(WebRequest)

public:
    WebRequestPrivate(WebRequest *parent);

//    QNetworkAccessManager *net;
    int calls;
    QUrl m_url;
    bool m_isBusy;
    QString m_cacheId;
    bool m_useCache;
    QVariantMap m_data;
    bool m_includeDataInCacheId;
    QString m_actualCacheId;
    bool m_cacheUsed;
    qint64 m_expirationSeconds;
    QString loadingText;
    WebRequest::Method m_method;
    WebRequestManager *m_manager;
    WebRequestCache *m_cacheManager;
    QMap<QString, QString> files;
    bool useUtf8;
};

KAJ_END_NAMESPACE

#endif // WEBREQUEST_P_H
