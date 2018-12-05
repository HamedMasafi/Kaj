#ifndef IMAGEREQUEST_H
#define IMAGEREQUEST_H

#include "kajglobal.h"
#include "request/webrequest.h"

#include <QtCore/QObject>
#include <QtGui/QImage>


KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT ImageRequest : public WebRequest
{
    Q_OBJECT
    Q_PROPERTY(QUrl fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

    QUrl m_fileName;

public:
    explicit ImageRequest(QObject *parent = nullptr);
    QUrl fileName() const;

public slots:
    void setFileName(QUrl fileName);

signals:
    void finished(QImage data);
    void fileNameChanged(QUrl fileName);

protected:
    void processResponse(QByteArray buffer) Q_DECL_OVERRIDE;
    void storeInCache(QDateTime expire, QByteArray buffer) Q_DECL_OVERRIDE;
    bool retriveFromCache(const QString &key) Q_DECL_OVERRIDE;
    void beforeSend(QNetworkRequest &request);
};

KAJ_END_NAMESPACE

#endif // IMAGEREQUEST_H
