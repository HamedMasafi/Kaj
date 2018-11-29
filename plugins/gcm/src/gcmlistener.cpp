#include "gcmlistener.h"

#include "googlegcm.h"
#include <QDebug>

KAJ_BEGIN_NAMESPACE

GcmListener::GcmListener(GoogleGcm *gcm) : firebase::messaging::PollableListener(), _gcm(gcm)
{

}

void GcmListener::OnMessage(const firebase::messaging::Message &message)
{
//    GoogleGcm::instance()->
    qDebug() << "Message:" << QString::fromStdString(message.notification->title)
             << " - "
             << QString::fromStdString(message.notification->body);

    Message msg(message);
    emit _gcm->messageRecived(msg);
}

void GcmListener::OnTokenReceived(const char *token)
{
    qDebug() << "Token recived" << token;
    _gcm->setRegistrationToken(QString::fromStdString(token));
}

KAJ_END_NAMESPACE
