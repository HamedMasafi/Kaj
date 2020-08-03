#ifndef WEBREQUESTQML_H
#define WEBREQUESTQML_H

#include "../webrequest.h"

#include <QQmlListProperty>

KAJ_REST_BEGIN_NAMESPACE

class AbstractHelper;
class WebRequestQml : public WebRequest
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<QObject> helpers READ helpers DESIGNABLE false)
    Q_CLASSINFO("DefaultProperty", "helpers")

    QList<QObject *> m_helpers;

public:
    WebRequestQml(QObject *parent = nullptr);

    QQmlListProperty<QObject> helpers();

private:
    void checkHelpers();

    // WebRequest interface
public slots:
    void send();
};

KAJ_REST_END_NAMESPACE

#endif // WEBREQUESTQML_H
