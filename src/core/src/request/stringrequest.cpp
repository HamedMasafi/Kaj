#include "stringrequest.h"

KAJ_BEGIN_NAMESPACE

StringRequest::StringRequest(QObject *parent) : WebRequest(parent)
{ }

void StringRequest::processResponse(QByteArray buffer)
{
    emit finished(QString(buffer));
}

KAJ_END_NAMESPACE
