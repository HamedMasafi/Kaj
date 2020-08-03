#include "filedownload.h"

#include <QFile>
#include <QNetworkReply>
#include <QDebug>

KAJ_REST_BEGIN_NAMESPACE

FileDownload::FileDownload(QObject *parent) : AbstractResponse(parent)
      , m_progress(0)
{

}

void FileDownload::processReply(QNetworkReply *reply)
{
    auto _file = new QFile(m_localFilePath);
    if (!_file->open(QIODevice::WriteOnly))
        return;

    setStatus(Pending);

    connect(reply, &QNetworkReply::readyRead, [this, reply, _file]() {
        setStatus(Downloading);
        QByteArray data = reply->readAll();
        _file->write(data);
    });

    connect(reply, &QNetworkReply::finished, [this, _file]() {
        _file->close();
        _file->deleteLater();
        setStatus(Finished);
    });
    connect(reply,
            &QNetworkReply::downloadProgress,
            [this](qint64 bytesReceived, qint64 bytesTotal) {
                setProgress((qreal) bytesReceived / (qreal) bytesTotal * 100.);
    });
}

QString FileDownload::localFilePath() const
{
    return m_localFilePath;
}

qreal FileDownload::progress() const
{
    return m_progress;
}

FileDownload::Status FileDownload::status() const
{
    return m_status;
}

void FileDownload::setLocalFilePath(QString localFilePath)
{
    if (m_localFilePath == localFilePath)
        return;

    m_localFilePath = localFilePath;
    emit localFilePathChanged(m_localFilePath);
}

void FileDownload::setProgress(qreal progress)
{
    if (qFuzzyCompare(m_progress, progress))
        return;

    m_progress = progress;
    emit progressChanged(m_progress);
}

void FileDownload::setStatus(FileDownload::Status status)
{
    if (m_status == status)
        return;

    m_status = status;
    emit statusChanged(m_status);
}

bool FileDownload::storeCacheAsFile() const
{
    return true;
}

bool FileDownload::selfProcess()
{
    return true;
}

KAJ_REST_END_NAMESPACE
