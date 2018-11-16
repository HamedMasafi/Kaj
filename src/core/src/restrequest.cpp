#include "restrequest.h"
#include "restrequest_p.h"

#include <QtCore/QDir>
#include <QtCore/QEventLoop>
#include <QtCore/QJsonDocument>
#include <QtCore/QJsonObject>
#include <QtCore/QMetaMethod>
#include <QtCore/QRegularExpression>
#include <QtCore/QThread>
#include <QtNetwork/QHttpPart>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>

#ifdef QT_SQL_LIB
#   include <QtCore/QCoreApplication>
#   include <QtSql/QSqlQuery>
#   include <QtSql/QSqlError>
#   include <QtCore/QStandardPaths>
#endif

KAJ_BEGIN_NAMESPACE

// RestRequestCallsManager
WebRequestManager* WebRequestManager::_instance = nullptr;

void WebRequestManager::addCall()
{
    calls++;
    setIsBusy(true);
}

void WebRequestManager::removeCall()
{
    calls--;
    setIsBusy(calls);
}

WebRequestManager::WebRequestManager() : calls(0), m_isBusy(false)
{

}

WebRequestManager *WebRequestManager::instance()
{
    if (_instance == nullptr)
        _instance = new WebRequestManager;
    return _instance;
}

bool WebRequestManager::isBusy() const
{
    return m_isBusy;
}

void WebRequestManager::setIsBusy(bool isBusy)
{
    if (m_isBusy == isBusy)
        return;

    m_isBusy = isBusy;
    emit isBusyChanged(m_isBusy);
}

//RestRequestCacheManager
WebRequestCache* WebRequestCache::_instance = nullptr;

bool WebRequestCache::contains(const QString &key) const
{
    QSqlQuery q(db);
    q.prepare("SELECT COUNT(*) FROM data WHERE key=:key");
    q.bindValue(":key", key);
    q.exec();
    if (!q.first())
        return false;
    int c = q.value(0).toInt();
    return c > 0;
}

int WebRequestCache::findId(const QString &key) const
{
    QSqlQuery q(db);
    q.prepare("SELECT id FROM data WHERE key=:key");
    q.bindValue(":key", key);
    q.exec();
    if (!q.first())
        return 0;

    return q.value(0).toInt();
}

WebRequestCache *WebRequestCache::instance()
{
    if (_instance == nullptr)
        _instance = new WebRequestCache;
    return _instance;
}

WebRequestCache::WebRequestCache(const QString &name)
{
#ifdef QT_SQL_LIB
    db = QSqlDatabase::addDatabase("QSQLITE");
    path = QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    QDir d(path);
    if (!d.exists())
        d.mkdir(path);

    if (name == QString())
        db.setDatabaseName(path + "/cache.dat");
    else
        db.setDatabaseName(path + "/" + name + ".dat");

    db.open();

    db.exec("CREATE TABLE IF NOT EXISTS data("
            "id INTEGER PRIMARY KEY,"
            "key TEXT,"
            "value TEXT,"
            "expire DATETIME,"
            "type INTEGER"
            ")");

    printError();
#endif
}

QString WebRequestCache::value(const QString &key) const
{
#ifdef QT_SQL_LIB
    QSqlQuery q = db.exec(QString("SELECT id, value, expire FROM data WHERE key='%1'").arg(key));
    printError();
    if (!q.first())
        return QString();

    QDateTime expire =  QDateTime::fromString(q.value("expire").toString());

    if (expire < QDateTime::currentDateTime()) {
        QSqlQuery qdelete(db);
        qdelete.prepare("DELETE FROM data WHERE id=:id");
        qdelete.bindValue(":id", q.value("id"));
        qdelete.exec();
        return QString();
    }

    return q.value("value").toString();
#else
    if (cache.contains(key))
        return *cache.object(key);
    else
        return QString();
#endif
}

bool WebRequestCache::setValue(const QString &key, const QByteArray &value, const QDateTime &expire) const
{
    int id = findId(key);

    QSqlQuery q2(db);
    if (!id)
        q2.prepare("UPDATE data SET expire=:expire WHERE key=:key");
    else
        q2.prepare("INSERT INTO data (key, expire, type) "
                  "VALUES (:key, :expire, '2')");

    q2.bindValue(":key", key);
    q2.bindValue(":expire", expire.toString());
    q2.exec();

    if (!id)
        id = q2.lastInsertId().toInt();

    QFile f(path + "/file-" + QString::number(id));
    if (!f.open(QIODevice::WriteOnly))
        return false;

    f.write(value);
    f.close();
    return true;
}

bool WebRequestCache::setValue(QString key, QString value, QDateTime expire) const
{
#ifdef QT_SQL_LIB
    bool exists = contains(key);

    QSqlQuery q2(db);
    if (exists)
        q2.prepare("UPDATE data SET value=:value, expire=:expire WHERE key=:key");
    else
        q2.prepare("INSERT INTO data (key, value, expire, type) "
                  "VALUES (:key, :value, :expire, '1')");

    q2.bindValue(":key", key);
    q2.bindValue(":value", value);
    q2.bindValue(":expire", expire.toString());
    q2.exec();

    printError();
    return q2.numRowsAffected() > 0;;
#else
    cache.insert(key, &value);
    return true;
#endif
}

void WebRequestCache::printError() const
{
#ifdef QT_SQL_LIB
    if (db.lastError().type() != QSqlError::NoError)
        qWarning() << "Error database:" << db.lastError().text();
#endif
}

WebRequestPrivate::WebRequestPrivate(WebRequest *parent) : q_ptr(parent),
    calls(0), m_isBusy(false), m_cacheId(QString()),
    m_useCache(true), m_data(QVariantMap()), m_includeDataInCacheId(false),
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

void WebRequest::sendToServer(QVariantMap props)
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

//    QJsonDocument doc;
//    doc.setObject(QJsonObject::fromVariantMap(props));
//    postData = doc.toJson();

    if (d->m_useCache) {
        QString cacheId;
        if (d->m_cacheId != QString()) {
            cacheId = d->m_cacheId;
        } else {
            if (d->m_includeDataInCacheId)
                cacheId = d->m_url.toString() + "?" + postData;
            else
                cacheId = d->m_url.toString();
        }

        QString cache = cacheManager()->value(cacheId);
        if (cache != QString()) {
            processResponse(cache.toLocal8Bit());
            return;
        }
    }
    manager()->addCall();
    setIsBusy(true);

    QNetworkRequest request;
    beforeSend(request);
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "application/x-www-form-urlencoded");
    request.setUrl(d->m_url);
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
        QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
        foreach (auto key, props.keys()) {
            QHttpPart textPart;
            textPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + key + "\""));
            textPart.setBody(props.value(key).toByteArray());
            multiPart->append(textPart);
        }

        d->net->post(request, postData);
    } else {
        if (d->m_method == Get)
            d->net->get(request);
        else
            d->net->post(request, QByteArray());
    }
}

void WebRequest::send()
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
    sendToServer(map);
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

void WebRequest::on_net_finished(QNetworkReply *reply)
{
    Q_D(WebRequest);

    auto buffer = reply->readAll();
    manager()->removeCall();
    if (reply->error() != QNetworkReply::NoError) {
        qWarning() << "Error" << reply->error() << reply->errorString();
        qWarning() << buffer;
        emit replyError(reply->error(), reply->errorString());
        return;
    }

    if (d->m_useCache) {
        QString cacheControl = QString(reply->rawHeader("cache-control"));
        QRegularExpression r("max-age=(\\d+)");
        QRegularExpressionMatch m = r.match(cacheControl);
        QDateTime expire = QDateTime::currentDateTime();
        if (m.hasMatch()) {
            expire = expire.addSecs(m.captured(1).toInt());
        }
        storeInCache(expire, buffer);
    }
    processResponse(buffer);

    d->calls--;
    setIsBusy(d->calls);
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

    d->m_data = data;
    emit dataChanged(d->m_data);
}

void WebRequest::setIncludeDataInCacheId(bool includeDataInCacheId)
{
    Q_D(WebRequest);
    if (d->m_includeDataInCacheId == includeDataInCacheId)
        return;

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

JsonRequest::JsonRequest(QObject *parent) : WebRequest(parent)
{ }

void JsonRequest::processResponse(QByteArray buffer)
{
    QJsonObject obj = QJsonDocument::fromJson(buffer).object();
    if (obj.isEmpty())
        emit replyError(0, "");
    else
        emit finished(obj);
}

StringRequest::StringRequest(QObject *parent) : WebRequest(parent)
{ }

void StringRequest::processResponse(QByteArray buffer)
{
    emit finished(QString(buffer));
}

VariantRequest::VariantRequest(QObject *parent) : WebRequest(parent)
{

}

void VariantRequest::processResponse(QByteArray buffer)
{
    //TODO:
    Q_UNUSED(buffer);
    emit finished(QVariant());
}

ImageRequest::ImageRequest(QObject *parent) : WebRequest(parent)
{

}

void ImageRequest::processResponse(QByteArray buffer)
{
    Q_UNUSED(buffer);
}

void ImageRequest::storeInCache(QDateTime expire, QByteArray buffer)
{
    QString cid = cacheId();
    if (cid.isEmpty())
        cid = url().toString().replace("'", "");
    bool ok = cacheManager()->setValue(cid, buffer, expire);
    if (!ok)
        qWarning() << "Unable to store cache";}

KAJ_END_NAMESPACE
