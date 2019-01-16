/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * libcalendars is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef SHAPE_H
#define SHAPE_H

#include "kajglobal.h"
#include <QQuickPaintedItem>

KAJ_BEGIN_NAMESPACE

class Shape : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(ShapeType type READ type WRITE setType NOTIFY typeChanged)
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
    void setType(ShapeType type);
    void setColor(QColor color);

private:
    ShapeType m_type;
    QColor m_color;
};

KAJ_END_NAMESPACE

#endif // SHAPE_H
