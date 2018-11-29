#ifndef WEBREQUESTCACHE_H
#define WEBREQUESTCACHE_H

#include "kajglobal.h"
#include <QObject>

#ifdef QT_SQL_LIB
#   include <QtSql/QSqlDatabase>
#   include <QtGui/QImage>
#else
#   include <QtCore/QCache>
#endif

KAJ_BEGIN_NAMESPACE

class WebRequestCache : public QObject {
    Q_OBJECT

    static WebRequestCache *_instance;
#ifdef QT_SQL_LIB
    QSqlDatabase db;
#else
    QCache<QString, const QString> cache;
#endif
    QString path;

    bool contains(const QString &key) const;
    int findId(const QString &key) const;

    QString generateFileName(const int &id) const;

    void scheduleCleaninng();

public:
    static WebRequestCache *instance();
    WebRequestCache(const QString &name = QString());

    QString value(const QString &key) const;
    QString fileName(const QString &key) const;
    QString setValue(const QString &key, const QByteArray &value, const QDateTime &expire);
    bool setValue(const QString &key, const QString &value, const QDateTime &expire);
    bool removeValue(const QString &key);
    void printError() const;
    int clean();
    void clear();

protected:
    void timerEvent(QTimerEvent *);
};

KAJ_END_NAMESPACE

#endif // WEBREQUESTCACHE_H
