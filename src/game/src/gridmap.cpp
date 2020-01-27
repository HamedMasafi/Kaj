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

#include <QList>
#include <QTransform>
#include <QtMath>
#include <QDebug>
#include <QPainter>

#include "gridmap_p.h"
#include "gridmap.h"

KAJ_BEGIN_NAMESPACE

GridMapPrivate::GridMapPrivate(GridMap *parent) : q_ptr(parent),
    gridColor(Qt::white),
    imageSource(QUrl()),
    gridOpacity(1),
    deg(0),
    cols(20),
    rows(20),
    hilightedRect(QRect()),
    highlightColor(Qt::green),
    transformChanged(true)
{

}

void GridMapPrivate::reNewTranform(){
    Q_Q(GridMap);

    if(!transformChanged)
        return;

    cell_width = q->width() / cols;
    cell_height = q->height() / rows;
    cell_size = qMin(cell_height, cell_width);

    QRectF rc;
    rc.setSize(QSizeF(cols * cell_size, rows * cell_size));
    rc.moveCenter(q->boundingRect().center());
    paddingX = rc.x();
    paddingY = rc.y();

    qreal rad = deg * (M_PI / 180);
    qreal realH = qAbs(qCos(rad) * rc.height()) + qAbs(qSin(rad) * rc.width());
    qreal realW = qAbs(qSin(rad) * rc.height()) + qAbs(qCos(rad) * rc.width());


    transform.reset();
    transform.translate(q->width() / 2, q->height() / 2);
    transform.scale(q->width() / realW, q->height() / realH);
    transform.rotate(deg);
    transform.translate(q->width() / -2, q->height() / -2);
    transform.translate(paddingX, paddingY);
    transform.scale(cell_size, cell_size);

    //detransform.reset();
    //detransform.scale(1/ cell_size, 1/ cell_size);
    //detransform.translate(-paddingX, -paddingY);
    //detransform.translate(q->width() / 2, q->height() / 2);
    //detransform.rotate(-deg);
    //detransform.scale(realW / q->width(), realH / q->height());
    //detransform.translate(q->width() / -2, q->height() / -2);
    detransform = transform.inverted();

    transformChanged = false;
    q->update();

    QList<QQuickItem *>  childs = q->childItems();
    foreach (QQuickItem *child, childs)
        q->invalidate(child);
}

int GridMapPrivate::min(int a, int b, int c, int d) const{
    return qMin(qMin(a ,b),
                qMin(c, d));
}
int GridMapPrivate::max(int a, int b, int c, int d) const{
    return qMax(qMax(a ,b),
                qMax(c, d));
}



GridMapAttached::GridMapAttached(QObject *parent) : QObject(parent)
{
    _parent = qobject_cast<QQuickItem*>(parent);
}

int GridMapAttached::x() const
{
    return m_x;
}

int GridMapAttached::y() const
{
    return m_y;
}

int GridMapAttached::width() const
{
    return m_width;
}

int GridMapAttached::height() const
{
    return m_height;
}

bool GridMapAttached::isFloat() const
{
    return m_isFloat;
}

void GridMapAttached::setX(int x)
{
    if (m_x == x)
        return;

    m_x = x;
    invalidateItem();
    emit xChanged(x);
}

void GridMapAttached::setY(int y)
{
    if (m_y == y)
        return;

    m_y = y;
    invalidateItem();
    emit yChanged(y);
}

void GridMapAttached::setWidth(int width)
{
    if (m_width == width)
        return;

    m_width = width;
    invalidateItem();
    emit widthChanged(width);
}

void GridMapAttached::setHeight(int height)
{
    if (m_height == height)
        return;

    m_height = height;
    invalidateItem();
    emit heightChanged(height);
}

void GridMapAttached::setIsFloat(bool isFloat)
{
    if (m_isFloat == isFloat)
        return;

    m_isFloat = isFloat;
    emit isFloatChanged(isFloat);
}

QQuickItem *GridMapAttached::entity() const
{
    return qobject_cast<QQuickItem *>(parent());
}

GridMap *GridMapAttached::parentGrid() const
{
    QQuickItem *parentItem = entity();
    if (parentItem) {
        parentItem = parentItem->parentItem();
        return qobject_cast<GridMap*>(parentItem);
    } else {
        qWarning("GridMap must be attached to Item elements");
    }
    return nullptr;
}

void GridMapAttached::invalidateItem() const
{
    //    if (!m_changesNotificationEnabled)
    //        return;

    //    quickLayoutDebug() << "QQuickLayoutAttached::invalidateItem";
    if(!m_isFloat)
        if (GridMap *layout = parentGrid()) {
            layout->invalidate(entity());
        }
}


GridMap::GridMap(QQuickItem *parent) : QQuickPaintedItem(parent),
    d_ptr(new GridMapPrivate(this))
{
}

GridMapAttached *GridMap::qmlAttachedProperties(QObject *object)
{
    return new GridMapAttached(object);
}

int GridMap::cols() const
{
    Q_D(const GridMap);
    return d->cols;
}

int GridMap::rows() const
{
    Q_D(const GridMap);
    return d->rows;
}

QPointF GridMap::demap(const QPointF &p) const
{
    Q_D(const GridMap);

    return d->detransform.map(p);
}

QRect GridMap::demap(const QRect &rc) const
{
    Q_D(const GridMap);

    return QRect(d->detransform.map(rc.topLeft()),
                  d->detransform.map(rc.bottomRight()));
}

QPoint GridMap::map(QPoint p) const
{
    Q_D(const GridMap);

    return d->transform.map(p);
}

QPointF GridMap::map(QPointF p) const
{
    Q_D(const GridMap);

    return d->transform.map(p);
}

QRect GridMap::map(QRect rc) const
{
    return map(rc.left(), rc.top(), rc.width(), rc.height()).toRect();
}

QRectF GridMap::map(QRectF rc) const
{
    return map(rc.left(), rc.top(), rc.width(), rc.height());
}

QRectF GridMap::map(int col, int row, int width, int height) const
{
    Q_D(const GridMap);

    QPointF pt1 = map(QPointF(col,          row));
    QPointF pt2 = map(QPointF(col + width,  row));
    QPointF pt3 = map(QPointF(col,          row + height));
    QPointF pt4 = map(QPointF(col + width,  row + height));

    qreal l = d->min(pt1.x(), pt2.x(), pt3.x(), pt4.x());
    qreal t = d->min(pt1.y(), pt2.y(), pt3.y(), pt4.y());
    qreal w = (d->max(pt1.x(), pt2.x(), pt3.x(), pt4.x())) - l;
    qreal h = (d->max(pt1.y(), pt2.y(), pt3.y(), pt4.y())) - t;

    return QRectF(l, t, w, h);
}

QPolygonF GridMap::mapPolygon(QRectF rc) const
{
    return mapPolygon(rc.left(), rc.top(), rc.width(), rc.height());
}

QPolygonF GridMap::mapPolygon(int col, int row, int width, int height) const
{
    QPointF pt1 = map(QPointF(col,          row));
    QPointF pt2 = map(QPointF(col + width,  row));
    QPointF pt3 = map(QPointF(col + width,  row + height));
    QPointF pt4 = map(QPointF(col,          row + height));

    //    qreal l = d->min(pt1.x(), pt2.x(), pt3.x(), pt4.x());
    //    qreal t = d->min(pt1.y(), pt2.y(), pt3.y(), pt4.y());
    //    qreal w = (d->max(pt1.x(), pt2.x(), pt3.x(), pt4.x())) - l;
    //    qreal h = (d->max(pt1.y(), pt2.y(), pt3.y(), pt4.y())) - t;

    QPolygonF poly;
    poly.append(pt1);
    poly.append(pt2);
    poly.append(pt3);
    poly.append(pt4);
    return poly;
}

qreal GridMap::gridOpacity() const
{
    Q_D(const GridMap);
    return d->gridOpacity;
}

QColor GridMap::gridColor() const
{
    Q_D(const GridMap);
    return d->gridColor;
}

QUrl GridMap::imageSource() const
{
    Q_D(const GridMap);
    return d->imageSource;
}

QRect GridMap::hilightedRect() const
{
    Q_D(const GridMap);
    return d->hilightedRect;
}

// TODO: is not completed
QPointF GridMap::hotpoint(QQuickItem *child) const
{
    if(!child)
        return QPoint();

    QPointF pt = map(QPointF(0, 0));
    pt.setX(pt.x() * (child->width() / width()));
    pt.setY(pt.y() * (child->height() / height()));
    return pt;
}

QSizeF GridMap::cellSize() const
{
    Q_D(const GridMap);
    return QSizeF(d->cell_width, d->cell_height);
}

QColor GridMap::highlightColor() const
{
    Q_D(const GridMap);
    return d->highlightColor;
}

bool GridMap::isFree(int col, int row) const
{
    return isFree(col, row, 1, 1);
}

bool GridMap::isFree(int col, int row, int width, int height) const
{
    return isFree(QRect(col, row, width, height));
}

bool GridMap::isFree(QRect rc) const
{
    QList<QQuickItem *>  childs = childItems();
    foreach (QQuickItem *child, childs){
        GridMapAttached *attached = qobject_cast<GridMapAttached*>(qmlAttachedPropertiesObject<GridMap>(child));
        if(attached->isFloat())
            continue;

        QRect r(attached->x(), attached->y(), attached->width(), attached->height());

        if(rc.intersects(r))
            return false;
    }
    return true;
}

qreal GridMap::degree() const
{
    Q_D(const GridMap);
    return d->deg;
}

void GridMap::setCols(int cols)
{
    Q_D(GridMap);
    if (d->cols == cols)
        return;

    d->cols = cols;
    d->transformChanged = true;
    emit colsChanged(cols);
}

void GridMap::setRows(int rows)
{
    Q_D(GridMap);
    if (d->rows == rows)
        return;

    d->rows = rows;
    d->transformChanged = true;
    emit rowsChanged(rows);
}

void GridMap::setDegree(qreal degree)
{
    Q_D(GridMap);

    if (d->deg == degree)
        return;

    d->deg = degree;
    d->transformChanged = true;
    emit degreeChanged(degree);
}

void GridMap::setGridOpacity(qreal gridOpacity)
{
    Q_D(GridMap);

    if (d->gridOpacity == gridOpacity)
        return;

    d->gridOpacity = gridOpacity;
    update();
    emit gridOpacityChanged(gridOpacity);
}

void GridMap::setGridColor(QColor gridColor)
{
    Q_D(GridMap);
    if (d->gridColor == gridColor)
        return;

    d->gridColor = gridColor;
    update();
    emit gridColorChanged(gridColor);
}

void GridMap::setImageSource(QUrl imageSource)
{
    Q_D(GridMap);
    if (d->imageSource == imageSource)
        return;

    d->image = QImage(imageSource.toString().replace("qrc:/", ":/"));
    d->imageSource = imageSource;
    update();
    emit imageSourceChanged(imageSource);
}

void GridMap::invalidate(QQuickItem *child)
{
    //    if (m_dirty)
    //        return;

    //    m_dirty = true;

    //    if (!qobject_cast<QQuickLayout *>(parentItem())) {
    //        quickLayoutDebug() << "QQuickLayout::invalidate(), polish()";
    //        polish();
    //    }


//    QRectF childRect = child->boundingRect();
    //    if(childRect.size().width() + childRect.size().height()){
    //        GridMapAttached *attached = qobject_cast<GridMapAttached*>(qmlAttachedPropertiesObject<GridMap>(child));
    //        QRectF rc = map(attached->x(), attached->y(), attached->width(), attached->height());
    //        QPointF pt = map(QPoint(attached->x(), attached->y()));

    //        childRect.setHeight(childRect.height() * (rc.width() / childRect.width()) );
    //        childRect.setWidth(rc.width());
    //        //attached->verticalMargin()
    //        childRect.translate(3,4);
    //        pt = rc.topLeft();
    //        pt.setY(rc.top() - (childRect.height() - rc.height()));
    //        child->setPosition(pt);
    //        child->setSize(childRect.size());
    //    }else{
    GridMapAttached *attached = qobject_cast<GridMapAttached*>(qmlAttachedPropertiesObject<GridMap>(child));

    if(!attached->isFloat()){
        QRectF rc = map(attached->x(), attached->y(), attached->width(), attached->height());
        child->setPosition(rc.topLeft());
        child->setSize(rc.size());
    }
}

void GridMap::validatePos(QQuickItem *child)
{
    GridMapAttached *attached = qobject_cast<GridMapAttached*>(qmlAttachedPropertiesObject<GridMap>(child));

    if(!attached->isFloat()){

        QRectF rc = map(attached->x(), attached->y(), attached->width(), attached->height());
        child->setPosition(rc.topLeft());
        child->setSize(rc.size());
    }
}

void GridMap::setHilightedRect(QRect hilightedRect)
{
    Q_D(GridMap);

    if (d->hilightedRect == hilightedRect)
        return;

    update();
    d->hilightedRect = hilightedRect;
    emit hilightedRectChanged(hilightedRect);
}

void GridMap::setHighlightColor(QColor highlightColor)
{
    Q_D(GridMap);

    if (d->highlightColor == highlightColor)
        return;

    update();
    d->highlightColor = highlightColor;
    emit highlightColorChanged(highlightColor);
}

void GridMap::clearHilightedRect()
{
    setHilightedRect(QRect());
}

int GridMap::cellWidth() const
{
    Q_D(const GridMap);
    return d->cell_width;
}

int GridMap::cellHeigth() const
{
    Q_D(const GridMap);
    return d->cell_height;
}

void GridMap::widthChanged()
{
    Q_D(GridMap);
    d->transformChanged = true;
}

void GridMap::heightChanged()
{
    Q_D(GridMap);
    d->transformChanged = true;
}

void GridMap::paint(QPainter *painter)
{
    Q_D(GridMap);
    //d->transformChanged=true;
    if(d->transformChanged)
        d->reNewTranform();

    painter->setRenderHint(QPainter::Antialiasing);

    if(!d->image.isNull())
        painter->drawImage(QPoint(0, 0), d->image);

    if(d->gridOpacity){
        painter->setOpacity(d->gridOpacity);
        if(d->hilightedRect != QRect()){
            //            painter->setPen(Qt::red);
            QPainterPath tmpPath;
            tmpPath.addPolygon(mapPolygon(d->hilightedRect));

            painter->fillPath(tmpPath, d->highlightColor);
            //            painter->drawPolygon(mapPolygon(m_hilightedRect), Qt::WindingFill);
        }

        painter->setPen(d->gridColor);
        for(int c = 0; c <= d->cols; c++)
            painter->drawLine(map(QPointF(c, 0)), map(QPointF(c, d->rows)));

        for(int r = 0; r <= d->rows; r++)
            painter->drawLine(map(QPointF(0, r)), map(QPointF(d->cols, r)));

    }
}

void GridMap::childEvent(QChildEvent *event)
{
    if (event->added()) {
        qDebug() << event->child();
    }
    Q_UNUSED(event);
    //    qDebug()<<event;
    //    if(event->added()){
    //        QQmlComponentAttached *attached = QQmlComponent::qmlAttachedProperties(event->child());
    //        qDebug()<<attached;
    //    }
}

bool GridMap::event(QEvent *e)
{
    //    qDebug()<<e;
    return QQuickPaintedItem::event(e);
}

KAJ_END_NAMESPACE
