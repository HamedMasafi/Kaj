#ifndef GCMLISTENER_H
#define GCMLISTENER_H

#include <QtGlobal>
#include <firebase/app.h>
#include <firebase/messaging.h>

class GcmListener : public firebase::messaging::Listener
{
public:
    GcmListener();

    // Listener interface
public:
    void OnMessage(const firebase::messaging::Message &message) Q_DECL_OVERRIDE;
    void OnTokenReceived(const char *token) Q_DECL_OVERRIDE;
};

#endif // GCMLISTENER_H
