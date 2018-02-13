#ifdef QT_ANDROIDEXTRAS_LIB
#   include <QtAndroidExtras>
#endif

#include <QtQml>

#include "cafebazaarplugin.h"


KAJ_DECL_SINGLETON(CafeBazaarPlugin)

CafeBazaarPlugin::CafeBazaarPlugin(QObject *parent) : KajPluginBase(parent)
{
    setInstacne(this);
}

QString CafeBazaarPlugin::publicKey() const
{
    return m_publicKey;
}

void CafeBazaarPlugin::payment(QString name)
{
#ifdef QT_ANDROIDEXTRAS_LIB
    QAndroidJniObject jname = QAndroidJniObject::fromString(name);
    QAndroidJniObject jtoken = QAndroidJniObject::fromString(m_publicKey);

    QAndroidJniObject::callStaticMethod<void>(KAJ_JAVA_CLASS_NAME(cafebazaar, CafeBazaar),
                                              "Purchase",
                                              "(Ljava/lang/String;Ljava/lang/String;)V",
                                              jname.object<jstring>(),
                                              jtoken.object<jstring>());
#else
    Q_UNUSED(name)
#endif
}

bool CafeBazaarPlugin::init()
{
    qmlRegisterType<CafeBazaarPlugin>(KAJ_QML_URI, 1, 0, QT_STRINGIFY(CafeBazaarPlugin));
    return true;
}

bool CafeBazaarPlugin::isSupported()
{
#ifdef QT_ANDROIDEXTRAS_LIB
    return true;
#else
    return false;
#endif
}

void CafeBazaarPlugin::setPublicKey(QString publicKey)
{
    if (m_publicKey == publicKey)
        return;

    m_publicKey = publicKey;
    emit publicKeyChanged(publicKey);
}

#ifdef QT_ANDROIDEXTRAS_LIB
void KAJ_JAVA_NATIVE_METHOD(cafebazaar, CafeBazaar, result)(JNIEnv *env, jobject thiz, jboolean isSuccessfull, jstring name)
{
    Q_UNUSED(env);
    Q_UNUSED(thiz);

    qDebug()<< "cafebazaar::afeBazaar::result" << "Success=" << isSuccessfull;

    QAndroidJniObject d(name);
    CafeBazaarPlugin::instance()->result(isSuccessfull, d.toString());
}
#endif
