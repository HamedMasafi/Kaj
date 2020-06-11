#include "safezone.h"

SafeZone::SafeZone(QObject *parent) : QObject(parent)
{

}

QSize SafeZone::contentSize() const
{
    return m_contentSize;
}

QSize SafeZone::windowSize() const
{
    return m_windowSize;
}

qreal SafeZone::contentScale() const
{
    return m_contentScale;
}

qreal SafeZone::backgroundScale() const
{
    return m_backgroundScale;
}

void SafeZone::recalculate()
{
    scales.setWidth(static_cast<qreal>(m_windowSize.width()) / static_cast<qreal>(m_contentSize.width()));
    scales.setHeight(static_cast<qreal>(m_windowSize.height()) / static_cast<qreal>(m_contentSize.height()));

    setContentScale(qMin(scales.width(), scales.height()));
    setBackgroundScale(qMax(scales.width(), scales.height()));
}

void SafeZone::setContentSize(QSize contentSize)
{
    if (m_contentSize == contentSize)
        return;

    m_contentSize = contentSize;
    recalculate();
    emit contentSizeChanged(m_contentSize);
}

void SafeZone::setWindowSize(QSize windowSize)
{
    if (m_windowSize == windowSize)
        return;

    m_windowSize = windowSize;
    recalculate();
    emit windowSizeChanged(m_windowSize);
}

void SafeZone::setContentScale(qreal contentScale)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_contentScale, contentScale))
        return;

    m_contentScale = contentScale;
    emit contentScaleChanged(m_contentScale);
}

void SafeZone::setBackgroundScale(qreal backgroundScale)
{
    qWarning("Floating point comparison needs context sanity check");
    if (qFuzzyCompare(m_backgroundScale, backgroundScale))
        return;

    m_backgroundScale = backgroundScale;
    emit backgroundScaleChanged(m_backgroundScale);
}
