#ifndef WEBREQUEST_H
#define WEBREQUEST_H

#include "kajglobal.h"
#include <QtCore/qglobal.h>
#include <QtCore/QJsonObject>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QUrl>
#include <QtCore/QVariant>
#include <QtNetwork/QNetworkRequest>

#ifdef QT_SQL_LIB
#   include <QtSql/QSqlDatabase>
#   include <QtGui/QImage>
#else
#   include <QtCore/QCache>
#endif

class QNetworkReply;
class QNetworkAccessManager;

KAJ_BEGIN_NAMESPACE

class WebRequestManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged)

    int calls;
    static WebRequestManager *_instance;
    bool m_isBusy;

    void addCall();
    void removeCall();

public:
    WebRequestManager();
    static WebRequestManager *instance();
    bool isBusy() const;

    friend class WebRequest;

public slots:
    void setIsBusy(bool isBusy);

signals:
    void isBusyChanged(bool isBusy);
};

class WebRequestCache : public QObject {
    Q_OBJECT

    static WebRequestCache *_instance;
#ifdef QT_SQL_LIB
    QSqlDatabase db;
#else
    QCache<QString, QString> cache;
#endif
    QString path;

    bool contains(const QString &key) const;
    int findId(const QString &key) const;

public:
    static WebRequestCache *instance();
    WebRequestCache(const QString &name = QString());

    QString value(const QString &key) const;
    bool setValue(const QString &key, const QByteArray &value, const QDateTime &expire) const;
    bool setValue(QString key, QString value, QDateTime expire) const;
    void printError() const;
};

class WebRequestPrivate;
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

protected:
    void sendToServer(QVariantMap props = QMap<QString, QVariant>());
    virtual void processResponse(QByteArray buffer);
    virtual void beforeSend(QVariantMap &map);
    virtual void beforeSend(QNetworkRequest &request);
    virtual void storeInCache(QDateTime expire, QByteArray buffer);

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

private slots:
    void on_net_finished(QNetworkReply *reply);

public slots:
    void send();
    void setUrl(QUrl url);
    void setIsBusy(bool isBusy);
    void setCacheId(QString cacheId);
    void setUseCache(bool useCache);
    void setData(QVariantMap data);
    void setIncludeDataInCacheId(bool includeDataInCacheId);
    void setMethod(Method method);
    void setManager(WebRequestManager *manager);
    void setCacheManager(WebRequestCache *cacheManager);
};

class KAJ_EXPORT StringRequest : public WebRequest
{
    Q_OBJECT
public:
    explicit StringRequest(QObject *parent = nullptr);

signals:
    void finished(QString data);

protected:
    void processResponse(QByteArray buffer) Q_DECL_OVERRIDE;
};

class KAJ_EXPORT VariantRequest : public WebRequest
{
    Q_OBJECT
public:
    explicit VariantRequest(QObject *parent = nullptr);

signals:
    void finished(QVariant data);

protected:
    void processResponse(QByteArray buffer) Q_DECL_OVERRIDE;
};

class KAJ_EXPORT JsonRequest : public WebRequest
{
    Q_OBJECT
public:
    explicit JsonRequest(QObject *parent = nullptr);

signals:
    void finished(QJsonObject data);

protected:
    void processResponse(QByteArray buffer) Q_DECL_OVERRIDE;
};

class KAJ_EXPORT ImageRequest : public WebRequest
{
    Q_OBJECT
public:
    explicit ImageRequest(QObject *parent = nullptr);

signals:
    void finished(QImage data);

protected:
    void processResponse(QByteArray buffer) Q_DECL_OVERRIDE;
    void storeInCache(QDateTime expire, QByteArray buffer) Q_DECL_OVERRIDE;
};

KAJ_END_NAMESPACE

#endif // WEBREQUEST_H
