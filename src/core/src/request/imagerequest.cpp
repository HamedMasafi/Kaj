#include "imagerequest.h"
#include "webrequestcache.h"

#include <QtCore/QDateTime>
#include <QtCore/QDebug>

#include <QNetworkRequest>

KAJ_BEGIN_NAMESPACE

ImageRequest::ImageRequest(QObject *parent) : WebRequest(parent)
{
    setMethod(Get);
}

QUrl ImageRequest::fileName() const
{
    return m_fileName;
}

void ImageRequest::setFileName(QUrl fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

void ImageRequest::processResponse(QByteArray buffer)
{
    Q_UNUSED(buffer);
    QUrl fn = fileName();
    if (fn.isValid())
        emit finished(QImage(fn.toLocalFile()));
    else
        emit replyError(-1, "Image is null");
}

void ImageRequest::storeInCache(QDateTime expire, QByteArray buffer)
{
    QString cid = actualCacheId();
    if (cid.isEmpty())
        cid = url().toString().replace("'", "");
    QString fn = cacheManager()->setValue(cid, buffer, expire);
    setFileName(QUrl::fromLocalFile(fn));
}

bool ImageRequest::retriveFromCache(const QString &key)
{
    QString fn = cacheManager()->fileName(key);
    if (fn != QString()) {
        setFileName(QUrl::fromLocalFile(fn));
        processResponse(QByteArray());
        return true;
    }
    return false;
}

void ImageRequest::beforeSend(QNetworkRequest &request)
{
    request.setHeader(QNetworkRequest::ContentTypeHeader,
                      "");
}

KAJ_END_NAMESPACE
