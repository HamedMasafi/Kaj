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

