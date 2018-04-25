#include <QDebug>

#include "scalecontainer.h"

ScaleContainer::ScaleContainer(QQuickItem *parent, QQuickItem *child) : QQuickItem(parent)
{
    if(child)
        setChild(child);
}

void ScaleContainer::setChild(QQuickItem *child)
{
    child->setParent(this);
    setSize(child->boundingRect().size());
    setPosition(child->position());
    child->setTransformOrigin(QQuickItem::Center);
}

void ScaleContainer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
//    Q_ASSERT(childItems().count() == 1);
//    Q_UNUSED(newGeometry)
    Q_UNUSED(oldGeometry)

    QQuickItem *child = childItems().at(0);
    qreal scaleSize = qMin(newGeometry.width() / child->width(),
                           newGeometry.height() / child->height());
    qDebug() << child->scale() << scaleSize;
    child->setPosition(QPointF(
                (width() - child->width()) / 2,
                (height() - child->height()) / 2));
    child->setScale(scaleSize);
}

