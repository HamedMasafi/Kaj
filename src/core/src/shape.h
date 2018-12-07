#ifndef SHAPE_H
#define SHAPE_H

#include "kajglobal.h"
#include <QQuickPaintedItem>

KAJ_BEGIN_NAMESPACE

class Shape : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(ShapeType type READ type WRITE settype NOTIFY typeChanged)
    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

public:
    enum ShapeType {
        LineVertical,
        LineHorizontal,
        LineSlash,
        LineBackSlash,
        Circle,
        Oval,
        Square,
        Rectangle
    };
    Q_ENUM(ShapeType)

    Shape(QQuickItem *parent = nullptr);

    void paint(QPainter *painter);
    ShapeType type() const;
    QColor color() const;

signals:
    void typeChanged(ShapeType type);
    void colorChanged(QColor color);

public slots:
    void settype(ShapeType type);
    void setColor(QColor color);

private:
    ShapeType m_type;
    QColor m_color;
};

KAJ_END_NAMESPACE

#endif // SHAPE_H
