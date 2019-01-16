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

#ifndef GRIDMAP_P_H
#define GRIDMAP_P_H

#include "gridmap.h"

KAJ_BEGIN_NAMESPACE

class GridMapPrivate{
private:
    GridMap *q_ptr;
    Q_DECLARE_PUBLIC(GridMap)

public:

    GridMapPrivate(GridMap *parent);

    QTransform transform;
    QTransform detransform;

    QColor gridColor;
    QUrl imageSource;
    QImage image;

    qreal gridOpacity;
    qreal deg;
    int cols;
    int rows;

    qreal cell_width;
    qreal cell_height;
    qreal cell_size;
    qreal paddingX, paddingY;


    QRect hilightedRect;
    QColor highlightColor;

    bool transformChanged;

    void reNewTranform();
    int min(int a, int b, int c, int d) const;
    int max(int a, int b, int c, int d) const;
};

KAJ_END_NAMESPACE

#endif // GRIDMAP_P_H

