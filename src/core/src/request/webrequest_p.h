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

    QNetworkAccessManager *net;
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
    WebRequest::Method m_method;
    WebRequestManager *m_manager;
    WebRequestCache *m_cacheManager;
};

KAJ_END_NAMESPACE

#endif // WEBREQUEST_P_H
