#ifndef VARIANTREQUEST_H
#define VARIANTREQUEST_H

#include "kajglobal.h"
#include "request/webrequest.h"
#include <QObject>

KAJ_BEGIN_NAMESPACE

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

KAJ_END_NAMESPACE

#endif // VARIANTREQUEST_H
