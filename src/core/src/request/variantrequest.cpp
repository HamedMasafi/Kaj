#include "variantrequest.h"

KAJ_BEGIN_NAMESPACE

VariantRequest::VariantRequest(QObject *parent) : WebRequest(parent)
{

}

void VariantRequest::processResponse(QByteArray buffer)
{
    //TODO:
    Q_UNUSED(buffer);
    emit finished(QVariant());
}

KAJ_END_NAMESPACE
