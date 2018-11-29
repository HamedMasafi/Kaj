#ifndef GOOGLEGCM_H
#define GOOGLEGCM_H

#include <kajpluginbase.h>

namespace firebase {
    namespace messaging {
        class Message;
    }
}

KAJ_BEGIN_NAMESPACE

class GcmListener;

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
    Q_PROPERTY(QString body READ body WRITE setBody NOTIFY bodyChanged)
    Q_PROPERTY(QMap<QString, QString> data READ data WRITE setData NOTIFY dataChanged)
    Q_PROPERTY(QString link READ link WRITE setLink NOTIFY linkChanged)

public:
    Message (const firebase::messaging::Message &message);

    QString title() const;
    QString body() const;
    QMap<QString, QString> data() const;
    QString link() const;

public slots:
    void setTitle(QString title);
    void setBody(QString body);
    void setData(QMap<QString, QString> data);
    void setLink(QString link);

signals:
    void titleChanged(QString title);
    void bodyChanged(QString body);
    void dataChanged(QMap<QString, QString> data);
    void linkChanged(QString link);

private:
    QString m_title;
    QString m_body;
    QMap<QString, QString> m_data;
    QString m_link;
};


class GoogleGcm : public KajPluginBase
{
    Q_OBJECT

    KAJ_SINGLETON(GoogleGcm)

    Q_PROPERTY(QString registrationToken READ registrationToken WRITE setRegistrationToken NOTIFY registrationTokenChanged)

    QString m_registrationToken;
#ifdef Q_OS_ANDROID
    GcmListener *listener;
#endif

    friend class GcmListener;

public:
    GoogleGcm(QObject *parent = nullptr);
    QString registrationToken() const;

public slots:
    static bool init();
#if QT_QML_LIB
    static bool init(const QQmlApplicationEngine *engine);
#endif

    Message *polLastMessage();
    void setRegistrationToken(QString registrationToken);

signals:
    void registrationTokenChanged(QString registrationToken);
    void messageRecived(const Message &message);
    void tokenReceived(const QString &token);

};

KAJ_END_NAMESPACE

KAJ_DECLARE_CPP_PLUGIN(GoogleGcm)
KAJ_DECLARE_QML_PLUGIN(GoogleGcm)

#endif // GOOGLEGCM_H
