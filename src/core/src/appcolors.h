#ifndef APPCOLORS_H
#define APPCOLORS_H

#include <QObject>
#include <QColor>

class AppColors : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QColor secondaryTextColor READ secondaryTextColor WRITE setSecondaryTextColor NOTIFY secondaryTextColorChanged)
    Q_PROPERTY(QColor disabledTextColor READ disabledTextColor WRITE setDisabledTextColor NOTIFY disabledTextColorChanged)

    QColor m_textColor;

    QColor m_secondaryTextColor;

    QColor m_disabledTextColor;

public:
    explicit AppColors(QObject *parent = nullptr);
    static AppColors *instance();

    QColor textColor() const;

    QColor secondaryTextColor() const;

    QColor disabledTextColor() const;

public slots:
    void setTextColor(QColor textColor);

    void setSecondaryTextColor(QColor secondaryTextColor);

    void setDisabledTextColor(QColor disabledTextColor);

signals:

    void textColorChanged(QColor textColor);
    void secondaryTextColorChanged(QColor secondaryTextColor);
    void disabledTextColorChanged(QColor disabledTextColor);
};

#endif // APPCOLORS_H
