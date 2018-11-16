#ifndef RESTREQUEST_P_H
#define RESTREQUEST_P_H

#include "restrequest.h"

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
    WebRequest::Method m_method;
    WebRequestManager *m_manager;
    WebRequestCache *m_cacheManager;
};

KAJ_END_NAMESPACE

#endif // RESTREQUEST_P_H
