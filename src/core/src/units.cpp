#include <QApplication>
#include <QScreen>
#include <QtMath>
#include <QDebug>

#include "units.h"

QT_BEGIN_NAMESPACE

Units::Units(QObject *parent) : QObject(parent), m_fontScale(1)
{
    m_virtualDpi = qApp->primaryScreen()->physicalDotsPerInch();
//    qDebug() << "m_virtualDpi" << m_virtualDpi
//             << qApp->primaryScreen()->physicalDotsPerInch();
}

QString Units::screenName() const
{

    return QString("");
}

qreal Units::dp(int number)
{
    return number * (m_virtualDpi / 160.);
}

int Units::sp(int number)
{
    return qRound(dp(number) * m_fontScale);
}

int Units::pt(int number)
{
    return ((number / m_virtualDpi) * 72);
}

qreal Units::mm(int number)
{
    return in(number) * 25.4;
}

qreal Units::in(int number)
{
    return (qreal)number / m_virtualDpi;
}

qreal Units::cm(int number)
{
    return mm(number) / 100.;
}

qreal Units::fromDp(int number)
{
    return (number / m_virtualDpi) * 160.;
}

int Units::virtualDpi() const
{
    return m_virtualDpi;
}

qreal Units::fontScale() const
{
    return m_fontScale;
}

void Units::setVirtualDpi(qreal virtualDpi)
{
    if (qFuzzyCompare(m_virtualDpi, virtualDpi))
        return;

    m_virtualDpi = virtualDpi;
    emit virtualDpiChanged(virtualDpi);
}

void Units::setFontScale(qreal fontScale)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_fontScale, fontScale))
        return;

    m_fontScale = fontScale;
    emit fontScaleChanged(m_fontScale);
}

QT_END_NAMESPACE
