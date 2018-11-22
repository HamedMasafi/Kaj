#include "webrequestmanager.h"

KAJ_BEGIN_NAMESPACE

// RestRequestCallsManager
WebRequestManager* WebRequestManager::_instance = nullptr;

WebRequestManager::WebRequestManager() : calls(0), m_isBusy(false)
{ }

void WebRequestManager::addCall()
{
    calls++;
    setIsBusy(true);
}

void WebRequestManager::removeCall()
{
    calls--;
    setIsBusy(calls);
}

WebRequestManager *WebRequestManager::instance()
{
    if (_instance == nullptr)
        _instance = new WebRequestManager;
    return _instance;
}

bool WebRequestManager::isBusy() const
{
    return m_isBusy;
}

void WebRequestManager::setIsBusy(bool isBusy)
{
    if (m_isBusy == isBusy)
        return;

    m_isBusy = isBusy;
    emit isBusyChanged(m_isBusy);
}

KAJ_END_NAMESPACE
