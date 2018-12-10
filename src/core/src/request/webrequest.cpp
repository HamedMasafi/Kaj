#include "request/webrequest.h"
#include "webrequest_p.h"
#include "webrequestcache.h"
#include "webrequestmanager.h"

#include <QtCore/QMetaMethod>
#include <QtCore/QRegularExpression>
#include <QtNetwork/QHttpPart>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

KAJ_BEGIN_NAMESPACE

WebRequestPrivate::WebRequestPrivate(WebRequest *parent) : q_ptr(parent),
    calls(0), m_isBusy(false), m_cacheId(QString()),
    m_useCache(true), m_data(QVariantMap()), m_includeDataInCacheId(false),
    m_actualCacheId(QString()), m_expirationSeconds(0),
    m_method(WebRequest::Post)
{
    net = new QNetworkAccessManager(parent);
    net->setObjectName("net");
}

WebRequest::WebRequest(QObject *parent)
    : QObject(parent), d_ptr(new WebRequestPrivate(this))
{
    Q_D(WebRequest);
    connect(d->net, &QNetworkAccessManager::finished, this, &WebRequest::on_net_finished);

    setManager(WebRequestManager::instance());
    setCacheManager(WebRequestCache::instance());
}

void WebRequest::sendToServer(QVariantMap props, bool cache)
{
    Q_D(WebRequest);
    d->calls++;
    QByteArray postData = "";
    beforeSend(props);
    if (props.count()) {
        foreach (auto key, props.keys()) {
            if (postData != "")
                postData.append("&");

            postData.append(key + "=" + props.value(key).toString());
        }
    }

    if (d->m_useCache && cache) {
        QString id = generateCacheId(props);
        if (retriveFromCache(id)) {
            setCacheUsed(true);
            return;
        }
    }
    setCacheUsed(false);

    manager()->addCall();
    setIsBusy(true);

    QNetworkRequest request;
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setUrl(d->m_url);
    beforeSend(request);
/*
    QByteArray postData = "";
    foreach (auto key, props.keys()) {
        if (postData != "")
            postData.append("&");

        postData.append(key + "=" + props.value(key).toString());
    }

    calls.insert(requestId, callBack);
    net->post(request, postData);
*/

    if (props.count()) {
        if (d->m_method == Get) {
            QUrl url = request.url();
            url.setQuery(postData);
            request.setUrl(url);
            d->net->get(request);
        } else {
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            foreach (auto key, props.keys()) {
                QHttpPart textPart;
                textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
                textPart.setBody(props.value(key).toByteArray());
                multiPart->append(textPart);
            }

            d->net->post(request, postData);
        }
    } else {
        if (d->m_method == Get)
            d->net->get(request);
        else
            d->net->post(request, QByteArray());
    }
}

void WebRequest::send(bool cache)
{
    Q_D(WebRequest);
    if (d->m_data != QVariantMap()) {
        sendToServer(d->m_data);
        return;
    }
    QVariantMap map;
    for(int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); i++)  {
        QMetaProperty prop = metaObject()->property(i);
        if (!prop.isStored())
            map.insert(prop.name(), prop.read(this));
    }
    sendToServer(map, cache);
}

QUrl WebRequest::url() const
{
    Q_D(const WebRequest);
    return d->m_url;
}

bool WebRequest::isBusy() const
{
    Q_D(const WebRequest);
    return d->m_isBusy;
}

QString WebRequest::cacheId() const
{
    Q_D(const WebRequest);
    return d->m_cacheId;
}

bool WebRequest::useCache() const
{
    Q_D(const WebRequest);
    return d->m_useCache;
}

QVariantMap WebRequest::data() const
{
    Q_D(const WebRequest);
    return d->m_data;
}

bool WebRequest::includeDataInCacheId() const
{
    Q_D(const WebRequest);
    return d->m_includeDataInCacheId;
}

WebRequest::Method WebRequest::method() const
{
    Q_D(const WebRequest);
    return d->m_method;
}

WebRequestManager *WebRequest::manager() const
{
    Q_D(const WebRequest);
    return d->m_manager;
}

WebRequestCache *WebRequest::cacheManager() const
{
    Q_D(const WebRequest);
    return d->m_cacheManager;
}

bool WebRequest::cacheUsed() const
{
    Q_D(const WebRequest);
    return d->m_cacheUsed;
}

qint64 WebRequest::expirationSeconds() const
{
    Q_D(const WebRequest);
    return d->m_expirationSeconds;
}

void WebRequest::beforeSend(QVariantMap &map)
{
    Q_UNUSED(map);
}

void WebRequest::beforeSend(QNetworkRequest &request)
{
    Q_UNUSED(request);
}

void WebRequest::processResponse(QByteArray buffer)
{
    rawDataRecived(buffer);
}

void WebRequest::storeInCache(QDateTime expire, QByteArray buffer)
{
    QString cid = cacheId();
    if (cid.isEmpty())
        cid = url().toString().replace("'", "");
    bool ok = cacheManager()->setValue(cid, QString(buffer), expire);
    if (!ok)
        qWarning() << "Unable to store cache";
}

bool WebRequest::retriveFromCache(const QString &key)
{
    QString cache = cacheManager()->value(key);
    if (cache != QString()) {
        processResponse(cache.toLocal8Bit());
        return true;
    }
    return false;
}

QString WebRequest::actualCacheId() const
{
    Q_D(const WebRequest);
    return d->m_actualCacheId;
}

QString WebRequest::generateCacheId(QVariantMap props)
{
    Q_D(WebRequest);

    QString postData = "";
    if (props.count()) {
        foreach (auto key, props.keys()) {
            if (postData != "")
                postData.append("&");

            postData.append(key + "=" + props.value(key).toString());
        }
    }
    if (d->m_actualCacheId == "") {
        if (d->m_cacheId != QString()) {
            d->m_actualCacheId = d->m_cacheId;
        } else {
            if (d->m_includeDataInCacheId)
                d->m_actualCacheId = d->m_url.toString() + "?" + postData;
            else
                d->m_actualCacheId = d->m_url.toString();
        }
    }

    return d->m_actualCacheId;
}

void WebRequest::on_net_finished(QNetworkReply *reply)
{
    Q_D(WebRequest);

    auto buffer = reply->readAll();
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Error" << reply->error() << reply->errorString();
        qWarning() << buffer;
        emit replyError(reply->error(), reply->errorString());
        manager()->removeCall();
        return;
    }

    if (d->m_useCache) {
        QDateTime expire = QDateTime::currentDateTime();

        if (d->m_expirationSeconds) {
            expire = expire.addSecs(d->m_expirationSeconds);
        } else {
            QString cacheControl = QString(reply->rawHeader("cache-control"));
            QRegularExpression r("max-age=(\\d+)");
            QRegularExpressionMatch m = r.match(cacheControl);
            if (m.hasMatch()) {
                expire = expire.addSecs(m.captured(1).toInt());
            }
        }
        storeInCache(expire, buffer);
    }
    processResponse(buffer);

    d->calls--;
    setIsBusy(d->calls);
    manager()->removeCall();
}

void WebRequest::setUrl(QUrl url)
{
    Q_D(WebRequest);
    if (d->m_url == url)
        return;

    d->m_url = url;
    emit urlChanged(d->m_url);
}

void WebRequest::setIsBusy(bool isBusy)
{
    Q_D(WebRequest);
    if (d->m_isBusy == isBusy)
        return;

    d->m_isBusy = isBusy;
    emit isBusyChanged(d->m_isBusy);
}

void WebRequest::setCacheId(QString cacheId)
{
    Q_D(WebRequest);
    if (d->m_cacheId == cacheId)
        return;

    d->m_actualCacheId = "";
    d->m_cacheId = cacheId;
    emit cacheIdChanged(d->m_cacheId);
}

void WebRequest::setUseCache(bool useCache)
{
    Q_D(WebRequest);
    if (d->m_useCache == useCache)
        return;

    d->m_useCache = useCache;
    emit useCacheChanged(d->m_useCache);
}

void WebRequest::setData(QVariantMap data)
{
    Q_D(WebRequest);
    if (d->m_data == data)
        return;

    d->m_actualCacheId = "";
    d->m_data = data;
    emit dataChanged(d->m_data);
}

void WebRequest::setIncludeDataInCacheId(bool includeDataInCacheId)
{
    Q_D(WebRequest);
    if (d->m_includeDataInCacheId == includeDataInCacheId)
        return;

    d->m_actualCacheId = "";
    d->m_includeDataInCacheId = includeDataInCacheId;
    emit includeDataInCacheIdChanged(d->m_includeDataInCacheId);
}

void WebRequest::setMethod(WebRequest::Method method)
{
    Q_D(WebRequest);
    if (d->m_method == method)
        return;

    d->m_method = method;
    emit methodChanged(d->m_method);
}

void WebRequest::setManager(WebRequestManager *manager)
{
    Q_D(WebRequest);
    if (d->m_manager == manager)
        return;

    d->m_manager = manager;
    emit managerChanged(manager);
}

void WebRequest::setCacheManager(WebRequestCache *cacheManager)
{
    Q_D(WebRequest);
    if (d->m_cacheManager == cacheManager)
        return;

    d->m_cacheManager = cacheManager;
    emit cacheManagerChanged(cacheManager);
}

void WebRequest::setExpirationSeconds(qint64 expirationSeconds)
{
    Q_D(WebRequest);
    if (d->m_expirationSeconds == expirationSeconds)
        return;

    d->m_expirationSeconds = expirationSeconds;
    emit expirationSecondsChanged(expirationSeconds);
}

void WebRequest::setCacheUsed(bool cacheUsed)
{
    Q_D(WebRequest);
    if (d->m_cacheUsed == cacheUsed)
        return;

    d->m_cacheUsed = cacheUsed;
    emit cacheUsedChanged(cacheUsed);
}

KAJ_END_NAMESPACE
