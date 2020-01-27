#include "appcolors.h"

AppColors::AppColors(QObject *parent) : QObject(parent)
{

}

AppColors *AppColors::instance()
{
    static AppColors *ins = nullptr;
    if (!ins)
        ins = new AppColors;
    return ins;
}

QColor AppColors::textColor() const
{
    return m_textColor;
}

QColor AppColors::secondaryTextColor() const
{
    return m_secondaryTextColor;
}

QColor AppColors::disabledTextColor() const
{
    return m_disabledTextColor;
}

void AppColors::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(m_textColor);
}

void AppColors::setSecondaryTextColor(QColor secondaryTextColor)
{
    if (m_secondaryTextColor == secondaryTextColor)
        return;

    m_secondaryTextColor = secondaryTextColor;
    emit secondaryTextColorChanged(m_secondaryTextColor);
}

void AppColors::setDisabledTextColor(QColor disabledTextColor)
{
    if (m_disabledTextColor == disabledTextColor)
        return;

    m_disabledTextColor = disabledTextColor;
    emit disabledTextColorChanged(m_disabledTextColor);
}
