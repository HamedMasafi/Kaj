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
    Q_PROPERTY(QString fileName READ fileName WRITE setFileName NOTIFY fileNameChanged)

    QString m_fileName;

public:
    explicit ImageRequest(QObject *parent = nullptr);
    QString fileName() const;

public slots:
    void setFileName(QString fileName);

signals:
    void finished(QImage data);
    void fileNameChanged(QString fileName);

protected:
    void processResponse(QByteArray buffer) Q_DECL_OVERRIDE;
    void storeInCache(QDateTime expire, QByteArray buffer) Q_DECL_OVERRIDE;
    bool retriveFromCache(const QString &key) Q_DECL_OVERRIDE;
};

KAJ_END_NAMESPACE

#endif // IMAGEREQUEST_H
