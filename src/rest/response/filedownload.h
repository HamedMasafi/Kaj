#ifndef FILEDOWNLOAD_H
#define FILEDOWNLOAD_H

#include "abstractresponse.h"

class QFile;

KAJ_REST_BEGIN_NAMESPACE

class FileDownload : public AbstractResponse
{
    Q_OBJECT
    Q_PROPERTY(QString localFilePath READ localFilePath WRITE setLocalFilePath NOTIFY localFilePathChanged)
    Q_PROPERTY(qreal progress READ progress WRITE setProgress NOTIFY progressChanged)
    Q_PROPERTY(Status status READ status WRITE setStatus NOTIFY statusChanged)

public:
    enum Status { Pending, Downloading, Finished };
    Q_ENUMS(Status)

    FileDownload(QObject *parent = nullptr);
    void processReply(QNetworkReply *reply);

    QString localFilePath() const;

    qreal progress() const;

    Status status() const;

public slots:
    void setLocalFilePath(QString localFilePath);

    void setProgress(qreal progress);

    void setStatus(Status status);

signals:
    void finished();
    void localFilePathChanged(QString localFilePath);

    // AbstractResponse interface
    void progressChanged(qreal progress);

    void statusChanged(Status status);

protected:
    bool storeCacheAsFile() const;
    bool selfProcess();

private:
    QString m_localFilePath;
    qreal m_progress;
    Status m_status;
};

KAJ_REST_END_NAMESPACE

#endif // FILEDOWNLOAD_H
