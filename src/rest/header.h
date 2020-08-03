#ifndef HEADER_H
#define HEADER_H

#include "abstracthelper.h"
#include "pair.h"

KAJ_REST_BEGIN_NAMESPACE

class Header : public AbstractHelper
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(HeaderType type READ type WRITE setType NOTIFY typeChanged)

public:
    enum HeaderType {
        Unset,
        AIM,
        Accept,
        AcceptCharset,
        AcceptDatetime,
        AcceptEncoding,
        AcceptLanguage,
        AccessControlRequestMethod,
        AccessControlRequestHeaders,
        Authorization,
        CacheControl,
        Connection,
        ContentEncoding,
        ContentLength,
        ContentMD5,
        ContentType,
        Cookie,
        Date,
        Expect,
        Forwarded,
        From,
        Host,
        HTTP2Settings,
        IfMatch,
        IfModifiedSince,
        IfNoneMatch,
        IfRange,
        IfUnmodifiedSince,
        MaxForwards,
        Origin,
        Pragma,
        ProxyAuthorization,
        Range,
        Referer,
        TE,
        Trailer,
        TransferEncoding,
        UserAgent,
        Upgrade,
        Via,
        Warning
    };
    Q_ENUMS(HeaderType)

    Header(QObject *parent = nullptr);
    QString name() const;
    QString value() const;
    HeaderType type() const;

public slots:
    void setName(QString name);
    void setValue(QString value);
    void setType(HeaderType type);

signals:
    void nameChanged(QString name);
    void valueChanged(QString value);
    void typeChanged(HeaderType type);

private:
    QString m_name;
    QString m_value;
    HeaderType m_type;
};

KAJ_REST_END_NAMESPACE

#endif // HEADER_H
