#ifndef STRINGREQUEST_H
#define STRINGREQUEST_H

#include "kajglobal.h"
#include "request/webrequest.h"
#include <QObject>

KAJ_BEGIN_NAMESPACE

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

KAJ_END_NAMESPACE

#endif // STRINGREQUEST_H
