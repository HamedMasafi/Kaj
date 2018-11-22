#ifndef WEBREQUESTMANAGER_H
#define WEBREQUESTMANAGER_H

#include "kajglobal.h"
#include <QObject>

KAJ_BEGIN_NAMESPACE

class WebRequestManager : public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isBusy READ isBusy WRITE setIsBusy NOTIFY isBusyChanged)

    static WebRequestManager *_instance;

public:
    WebRequestManager();
    static WebRequestManager *instance();
    bool isBusy() const;

    friend class WebRequest;

private:
    int calls;
    bool m_isBusy;

    void addCall();
    void removeCall();

public slots:
    void setIsBusy(bool isBusy);

signals:
    void isBusyChanged(bool isBusy);
};

KAJ_END_NAMESPACE

#endif // WEBREQUESTMANAGER_H
