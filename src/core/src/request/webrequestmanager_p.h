#ifndef WEBREQUESTMANAGER_P_H
#define WEBREQUESTMANAGER_P_H

#include "webrequestmanager.h"

#include <QNetworkRequest>
#include <QQueue>

class QNetworkAccessManager;
KAJ_BEGIN_NAMESPACE

class WebRequestManagerPrivate
{
    WebRequestManager *q_ptr;
    Q_DECLARE_PUBLIC(WebRequestManager)

public:

    WebRequestManagerPrivate(WebRequestManager *parent);

    QNetworkAccessManager *networdAccessManager;
};

KAJ_END_NAMESPACE

#endif // WEBREQUESTMANAGER_P_H
