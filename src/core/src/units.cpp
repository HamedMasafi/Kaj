#include <QApplication>
#include <QScreen>
#include <QtMath>

#include "units.h"

QT_BEGIN_NAMESPACE

Units::Units(QObject *parent) : QObject(parent)
{
    m_virtualDpi = qApp->primaryScreen()->logicalDotsPerInch();
}

QString Units::screenName() const
{

}

qreal Units::dp(int number)
{
    return number * ((qreal)m_virtualDpi / 160.);
}

int Units::sp(int number)
{
    return qRound(dp(number));
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
    return (qreal)number / (qreal)m_virtualDpi;
}

qreal Units::cm(int number)
{
    return mm(number) / 100.;
}

int Units::virtualDpi() const
{
    return m_virtualDpi;
}

void Units::setVirtualDpi(int arg)
{
    if (m_virtualDpi == arg)
        return;

    m_virtualDpi = arg;
    emit virtualDpiChanged(arg);
}


QT_END_NAMESPACE
