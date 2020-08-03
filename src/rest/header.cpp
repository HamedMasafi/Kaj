#include "header.h"

KAJ_REST_BEGIN_NAMESPACE

Header::Header(QObject *parent) : AbstractHelper(parent), m_type(Unset)
{

}

QString Header::name() const
{
    if (m_name.isEmpty()) {
        switch (m_type) {
        case AIM:
            return "AIM";
        case Accept:
            return "Accept";
        case AcceptCharset:
            return "Accept-Charset";
        case AcceptDatetime:
            return "Accept-Datetime";
        case AcceptEncoding:
            return "Accept-Encoding";
        case AcceptLanguage:
            return "Accept-Language";
        case AccessControlRequestMethod:
            return "Access-Control-Request-Method";
        case AccessControlRequestHeaders:
            return "Access-Control-Request-Headers";
        case Authorization:
            return "Authorization";
        case CacheControl:
            return "Cache-Control";
        case Connection:
            return "Connection";
        case ContentEncoding:
            return "Content-Encoding";
        case ContentLength:
            return "Content-Length";
        case ContentMD5:
            return "Content-MD5";
        case ContentType:
            return "Content-Type";
        case Cookie:
            return "Cookie";
        case Date:
            return "Date";
        case Expect:
            return "Expect";
        case Forwarded:
            return "Forwarded";
        case From:
            return "From";
        case Host:
            return "Host";
        case HTTP2Settings:
            return "HTTP2-Settings";
        case IfMatch:
            return "If-Match";
        case IfModifiedSince:
            return "If-Modified-Since";
        case IfNoneMatch:
            return "If-None-Match";
        case IfRange:
            return "If-Range";
        case IfUnmodifiedSince:
            return "If-Unmodified-Since";
        case MaxForwards:
            return "Max-Forwards";
        case Origin:
            return "Origin";
        case Pragma:
            return "Pragma";
        case ProxyAuthorization:
            return "Proxy-Authorization";
        case Range:
            return "Range";
        case Referer:
            return "Referer";
        case TE:
            return "TE";
        case Trailer:
            return "Trailer";
        case TransferEncoding:
            return "Transfer-Encoding";
        case UserAgent:
            return "User-Agent";
        case Upgrade:
            return "Upgrade";
        case Via:
            return "Via";
        case Warning:
            return "Warning";
        case Unset:
            return QString();
        }
    }
    return m_name;
}

QString Header::value() const
{
    return m_value;
}

Header::HeaderType Header::type() const
{
    return m_type;
}

void Header::setName(QString name)
{
    if (m_name == name)
        return;

    m_name = name;
    emit nameChanged(m_name);
}

void Header::setValue(QString value)
{
    if (m_value == value)
        return;

    m_value = value;
    emit valueChanged(m_value);
}

void Header::setType(Header::HeaderType type)
{
    if (m_type == type)
        return;

    m_type = type;
    emit typeChanged(m_type);
}

KAJ_REST_END_NAMESPACE
