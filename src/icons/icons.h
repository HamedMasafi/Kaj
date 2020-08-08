#ifndef ICONS_H
#define ICONS_H

#include <QObject>

class Icons : public QObject
{
    Q_OBJECT
public:
    enum IconType {
        ArrowLeft,
        ArrowRight,
        ArrowUp,
        ArrowDown,
        Ellipsis
    };
    Q_ENUMS(IconType);

    explicit Icons(QObject *parent = nullptr);

public Q_SLOTS:
    QString get(const IconType &type);
    QString fontName() const;
};

#endif // ICONS_H
