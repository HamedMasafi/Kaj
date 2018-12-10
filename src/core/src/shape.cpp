#include "shape.h"

#include <QPainter>

KAJ_BEGIN_NAMESPACE

Shape::Shape(QQuickItem *parent) : QQuickPaintedItem(parent), m_color(Qt::black)
{

}

Shape::ShapeType Shape::type() const
{
    return m_type;
}

void Shape::paint(QPainter *painter)
{
    if (!width() || !height())
        return;

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(m_color);
    switch (m_type) {
    case LineVertical:
        painter->drawLine(width() / 2, 0, width() / 2, height() - 1);
        break;

    case LineHorizontal:
        painter->drawLine(0, height() / 2, width() - 1, height() / 2);
        break;

    case LineSlash:
        painter->drawLine(width() - 1, 0, 0, height() - 1);
        break;

    case LineBackSlash:
        painter->drawLine(0, 0, width() - 1, height() - 1);
        break;

    case Oval:
        painter->drawEllipse(0, 0, width() -1, height() - 1);
        break;

    case Rectangle:
        painter->drawRect(0, 0, width() -1, height() - 1);
        break;

    case Circle: {
        qreal r = qMin(width(), height());
        painter->drawEllipse(QPointF(width() / 2, height() /2), r / 2, r / 2);
    }
        break;

    case Square: {
        qreal rs = qMin(width(), height());
        painter->drawRect(width() - rs / 2, height() - rs / 2, rs, rs);
    }
        break;
    }
}

void Shape::setType(Shape::ShapeType type)
{
    if (m_type == type)
        return;

    m_type = type;
    update();
    emit typeChanged(m_type);
}

QColor Shape::color() const
{
    return m_color;
}

void Shape::setColor(QColor color)
{
    if (m_color == color)
        return;

    m_color = color;
    update();
    emit colorChanged(m_color);
}

KAJ_END_NAMESPACE
