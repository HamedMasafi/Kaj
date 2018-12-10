#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include "kajglobal.h"

#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QMap>
#include <QtCore/QVariant>

class QNetworkRequest;
class QNetworkReply;

KAJ_BEGIN_NAMESPACE

class WebRequestPrivate;
class WebRequestManager;
class WebRequestCache;
class KAJ_EXPORT WebRequest : public QObject
{
    Q_OBJECT

    WebRequestPrivate *d_ptr;
    Q_DECLARE_PRIVATE(WebRequest)

    Q_PROPERTY(QUrl url READ url WRITE setUrl NOTIFY urlChanged STORED false)
    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged STORED false)
    Q_PROPERTY(QString cacheId READ cacheId WRITE setCacheId NOTIFY cacheIdChanged STORED false)
    Q_PROPERTY(bool useCache READ useCache WRITE setUseCache NOTIFY useCacheChanged STORED false)
    Q_PROPERTY(QVariantMap data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(bool includeDataInCacheId READ includeDataInCacheId WRITE setIncludeDataInCacheId NOTIFY includeDataInCacheIdChanged)
    Q_PROPERTY(Method method READ method WRITE setMethod NOTIFY methodChanged)
    Q_PROPERTY(WebRequestManager* manager READ manager WRITE setManager NOTIFY managerChanged)
    Q_PROPERTY(WebRequestCache* cacheManager READ cacheManager WRITE setCacheManager NOTIFY cacheManagerChanged)
    Q_PROPERTY(bool cacheUsed READ cacheUsed WRITE setCacheUsed NOTIFY cacheUsedChanged)
    Q_PROPERTY(qint64 expirationSeconds READ expirationSeconds WRITE setExpirationSeconds NOTIFY expirationSecondsChanged)

public:
    enum Method {
        Get,
        Post
    };
    Q_ENUMS(Method)

    explicit WebRequest(QObject *parent = nullptr);

    QUrl url() const;
    bool isBusy() const;
    QString cacheId() const;
    bool useCache() const;
    QVariantMap data() const;
    bool includeDataInCacheId() const;
    Method method() const;
    WebRequestManager *manager() const;
    WebRequestCache *cacheManager() const;
    bool cacheUsed() const;
    qint64 expirationSeconds() const;

protected:
    void sendToServer(QVariantMap props = QMap<QString, QVariant>(), bool cache = true);
    virtual void processResponse(QByteArray buffer);
    virtual void beforeSend(QVariantMap &map);
    virtual void beforeSend(QNetworkRequest &request);
    virtual void storeInCache(QDateTime expire, QByteArray buffer);
    virtual bool retriveFromCache(const QString &key);
    QString actualCacheId() const;
    QString generateCacheId(QVariantMap props);
    void setCacheUsed(bool cacheUsed);

signals:
    void replyError(const int &code, const QString &descript);
    void urlChanged(QUrl url);
    void isBusyChanged(bool isBusy);
    void rawDataRecived(QString data);
    void cacheIdChanged(QString cacheId);
    void useCacheChanged(bool useCache);
    void dataChanged(QVariantMap data);
    void includeDataInCacheIdChanged(bool includeDataInCacheId);
    void methodChanged(Method method);
    void managerChanged(WebRequestManager *manager);
    void cacheManagerChanged(WebRequestCache *cacheManager);
    void cacheUsedChanged(bool cacheUsed);
    void expirationSecondsChanged(qint64 expirationSeconds);

private slots:
    void on_net_finished(QNetworkReply *reply);

public slots:
    void send(bool cache = true);
    void setUrl(QUrl url);
    void setIsBusy(bool isBusy);
    void setCacheId(QString cacheId);
    void setUseCache(bool useCache);
    void setData(QVariantMap data);
    void setIncludeDataInCacheId(bool includeDataInCacheId);
    void setMethod(Method method);
    void setManager(WebRequestManager *manager);
    void setCacheManager(WebRequestCache *cacheManager);
    void setExpirationSeconds(qint64 expirationSeconds);
};

KAJ_END_NAMESPACE

#endif // WEBREQUEST_H
