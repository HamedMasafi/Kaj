#include "gcmlistener.h"

#include "googlegcm.h"
#include <QDebug>

GcmListener::GcmListener() : firebase::messaging::Listener()
{

}

void GcmListener::OnMessage(const firebase::messaging::Message &message)
{
//    GoogleGcm::instance()->
    qDebug() << QString(message.raw_data.c_str());
}

void GcmListener::OnTokenReceived(const char *token)
{

}
