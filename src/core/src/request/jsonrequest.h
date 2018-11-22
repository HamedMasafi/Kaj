#ifndef JSONREQUEST_H
#define JSONREQUEST_H

#include "kajglobal.h"
#include "request/webrequest.h"
#include <QtCore/QObject>
#include <QtCore/QJsonObject>

KAJ_BEGIN_NAMESPACE

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

KAJ_END_NAMESPACE

#endif // JSONREQUEST_H
