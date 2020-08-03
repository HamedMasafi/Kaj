#include "webrequestqml.h"
#include "../abstracthelper.h"
#include "header.h"
#include "../data/querystring.h"
#include "response/abstractresponse.h"
#include "expiretime.h"

#include <QDebug>


KAJ_REST_BEGIN_NAMESPACE


static void addProduct(QQmlListProperty<QObject> *property, QObject *product)
{
    WebRequestQml *store = qobject_cast<WebRequestQml *>(property->object);
    Q_ASSERT(store != 0);
//    product->setStore(store);

    QList<QObject *> *products = reinterpret_cast<QList<QObject *> *>(property->data);
    Q_ASSERT(products != 0);

    products->append(product);
}

static int productCount(QQmlListProperty<QObject> *property)
{
    QList<QObject *> *products = reinterpret_cast<QList<QObject *> *>(property->data);
    Q_ASSERT(products != 0);

    return products->size();
}

static void clearProducts(QQmlListProperty<QObject> *property)
{
    QList<QObject *> *products = reinterpret_cast<QList<QObject *> *>(property->data);
    Q_ASSERT(products != 0);

    products->clear();
}

static QObject *productAt(QQmlListProperty<QObject> *property, int index)
{
    QList<QObject *> *m_products = reinterpret_cast<QList<QObject *> *>(property->data);
    Q_ASSERT(m_products != 0);

    return m_products->at(index);
}

WebRequestQml::WebRequestQml(QObject *parent) : WebRequest(parent)
{

}

QQmlListProperty<QObject> WebRequestQml::helpers()
{
    //    return QQmlListProperty<QObject>(this, &m_helpers);
    return QQmlListProperty<QObject>(this,
                                     &m_helpers,
                                     &addProduct,
                                     &productCount,
                                     &productAt,
                                     &clearProducts);
}


void WebRequestQml::checkHelpers()
{
    for (auto i = m_helpers.begin(); i != m_helpers.end(); ++i) {
        auto dataInstance = qobject_cast<AbstractData *>(*i);
        if (dataInstance) {
            if (data()) {
                qWarning() << "more than one data";
                return;
            }
            setData(dataInstance);
            continue;
        }

        auto responseInstance = qobject_cast<AbstractResponse *>(*i);
        if (responseInstance) {
            if (response()) {
                qWarning() << "more than one data";
                return;
            }
            setResponse(responseInstance);
            continue;
        }

        auto queryString = qobject_cast<QueryString *>(*i);
        if (queryString) {
            //TODO: set QueryString
            continue;
        }

        auto header = qobject_cast<Header *>(*i);
        if (header) {
            setHeader(header->name(), header->value());
            continue;
        }

        auto expireTime = qobject_cast<ExpireTime *>(*i);
        if (expireTime) {
            setExpireTime(expireTime);
            continue;
        }

        qWarning() << "Unknown data: " << (*i)->metaObject()->className();
    }
}

void WebRequestQml::send()
{
    checkHelpers();
    WebRequest::send();
}

KAJ_REST_END_NAMESPACE
