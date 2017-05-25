#include "onesignal.h"

#if (defined (Q_OS_LINUX) || defined (Q_OS_UNIX) || defined (Q_OS_WIN) || defined (Q_OS_MACX)) && !defined (Q_OS_ANDROID)

#include <QWebEngineView>
#include <QtWebEngine>

KAJ_DECL_SINGLETON(OneSignal)

OneSignal::OneSignal(QObject *parent) : KajPluginBase(parent), m_applicationId(QString::null), isRegistered(false),
    m_userId(QString::null), m_registrationId(QString::null)
{
    setInstacne(this);
}

void OneSignal::init()
{
}

static QObject *createSingletonOneSignal(QQmlEngine *, QJSEngine *)
{
    return new OneSignal;
}

void OneSignal::init(const QQmlApplicationEngine *engine)
{
    Q_UNUSED(engine)
    qmlRegisterType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignal");
    qmlRegisterSingletonType<OneSignal>(KAJ_QML_URI, 1, 0, "OneSignalInstance", createSingletonOneSignal);
}

QString OneSignal::applicationId() const
{
    return m_applicationId;
}

QString OneSignal::userId()
{
    return m_userId;
}

QString OneSignal::registrationId()
{
    return m_registrationId;
}

QString OneSignal::additionalData()
{
    return m_additionalData;
}

void OneSignal::setApplicationId(QString applicationId)
{
    if (m_applicationId == applicationId)
        return;

    m_applicationId = applicationId;
    emit applicationIdChanged(m_applicationId);
    initOneSignal();
}

void OneSignal::setUserId(QString userId)
{
    qDebug() <<"User id changed from" << m_userId << "to" << userId;
    if (m_userId == userId)
        return;

    m_userId = userId;
    emit userIdChanged(m_userId);
}

void OneSignal::setRegistrationId(QString registrationId)
{
    if (m_registrationId == registrationId)
        return;

    m_registrationId = registrationId;
    emit registrationIdChanged(m_registrationId);
}

void OneSignal::setAdditionalData(QString additionalData)
{
    if (m_additionalData == additionalData)
        return;

    m_additionalData = additionalData;
    emit additionalDataChanged(m_additionalData);
}

void OneSignal::initOneSignal()
{
    if (isRegistered || m_applicationId.isNull())
        return;
}


#endif
