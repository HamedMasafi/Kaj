#ifndef GCMLISTENER_H
#define GCMLISTENER_H

#include "kajglobal.h"
#include <QtGlobal>
#include <firebase/app.h>
#include <firebase/messaging.h>

KAJ_BEGIN_NAMESPACE

class GoogleGcm;
class GcmListener : public firebase::messaging::PollableListener
{
    GoogleGcm *_gcm;
public:
    GcmListener(GoogleGcm *gcm = nullptr);

    // Listener interface
public:
    void OnMessage(const firebase::messaging::Message &message) Q_DECL_OVERRIDE;
    void OnTokenReceived(const char *token) Q_DECL_OVERRIDE;
};

KAJ_END_NAMESPACE

#endif // GCMLISTENER_H
