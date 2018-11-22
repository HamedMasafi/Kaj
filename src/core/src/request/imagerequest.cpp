#include "imagerequest.h"
#include "webrequestcache.h"

#include <QtCore/QDateTime>
#include <QtCore/QDebug>

KAJ_BEGIN_NAMESPACE

ImageRequest::ImageRequest(QObject *parent) : WebRequest(parent)
{

}

QString ImageRequest::fileName() const
{
    return m_fileName;
}

void ImageRequest::setFileName(QString fileName)
{
    if (m_fileName == fileName)
        return;

    m_fileName = fileName;
    emit fileNameChanged(m_fileName);
}

void ImageRequest::processResponse(QByteArray buffer)
{
    Q_UNUSED(buffer);
    QString fn = fileName();
    if (fn.isEmpty())
        emit replyError(-1, "Image is null");
    else
        emit finished(QImage(fn));
}

void ImageRequest::storeInCache(QDateTime expire, QByteArray buffer)
{
    QString cid = actualCacheId();
    if (cid.isEmpty())
        cid = url().toString().replace("'", "");
    setFileName(cacheManager()->setValue(cid, buffer, expire));
}

bool ImageRequest::retriveFromCache(const QString &key)
{
    QString fn = cacheManager()->fileName(key);
    if (fn != QString()) {
        setFileName(fn);
        processResponse(QByteArray());
        return true;
    }
    return false;
}

KAJ_END_NAMESPACE
