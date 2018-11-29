#include <QDebug>
#include <QSGNode>
#include "scalecontainer.h"

KAJ_BEGIN_NAMESPACE

ScaleContainer::ScaleContainer(QQuickItem *parent) : QQuickItem(parent)
{
}

ScaleContainerAttached *ScaleContainer::qmlAttachedProperties(QObject *object)
{
    return new ScaleContainerAttached(object);
}

void ScaleContainer::setChild(QQuickItem *child)
{
    child->setParent(this);
    setSize(child->boundingRect().size());
    setPosition(child->position());
    child->setTransformOrigin(QQuickItem::Center);
}

qreal ScaleContainer::scaleSize() const
{
    return m_scaleSize;
}

void ScaleContainer::setScaleSize(qreal scaleSize)
{
    if (qFuzzyCompare(m_scaleSize, scaleSize))
        return;

    m_scaleSize = scaleSize;
    emit scaleSizeChanged(m_scaleSize);
}

void ScaleContainer::child_childrenRectChanged(const QRectF &)
{
    QQuickItem *child = qobject_cast<QQuickItem*>(sender());
    child->setPosition(QPointF(
                           (width() - child->width()) / 2,
                           (height() - child->height()) / 2));
}

void ScaleContainer::geometryChanged(const QRectF &newGeometry, const QRectF &oldGeometry)
{
    Q_UNUSED(oldGeometry)

    if (!childItems().count())
        return;

    QQuickItem *child = childItems().at(0);
    qreal scaleSizeMin = qMin(newGeometry.width() / child->width(),
                           newGeometry.height() / child->height());

    qreal scaleSizeMax = qMax(newGeometry.width() / child->width(),
                           newGeometry.height() / child->height());

    foreach (child, childItems()) {
        ScaleContainerAttached *attached = qobject_cast<ScaleContainerAttached*>(qmlAttachedPropertiesObject<ScaleContainer>(child));
        switch(attached->scaleType()) {
        case ScaleContainerAttached::None:
            continue;

        case ScaleContainerAttached::FitAcceptRatio:
            child->setPosition(QPointF(
                                   (width() - child->width()) / 2,
                                   (height() - child->height()) / 2));
            child->setScale(scaleSizeMin);
            break;

        case ScaleContainerAttached::FitCrop:
            child->setPosition(QPointF(
                                   (width() - child->width()) / 2,
                                   (height() - child->height()) / 2));
            child->setScale(scaleSizeMax);
            break;
        }
    }
//    setScaleSize(scaleSize);
}

void ScaleContainer::itemChange(QQuickItem::ItemChange change, const QQuickItem::ItemChangeData &data)
{
    QQuickItem::itemChange(change, data);
    /*if (change == QQuickItem::ItemChildAddedChange) {
//        transform->appendToItem(data.item);
        data.item->setPosition(QPointF(
                    (width() - data.item->width()) / 2,
                    (height() - data.item->height()) / 2));
        connect(data.item, &QQuickItem::childrenRectChanged,
                this, &ScaleContainer::child_childrenRectChanged);
    }*/
}

QSGNode *ScaleContainer::updatePaintNode(QSGNode *node, QQuickItem::UpdatePaintNodeData *data)
{
    qDebug() << "updatePaintNode" << node->type();
    return QQuickItem::updatePaintNode(node, data);
}

ScaleContainerAttached::ScaleContainerAttached(QObject *parent)
{
    _parent = qobject_cast<QQuickItem*>(parent);
}

ScaleContainerAttached::ScaleType ScaleContainerAttached::scaleType() const
{
    return m_scaleType;
}

void ScaleContainerAttached::setScaleType(ScaleContainerAttached::ScaleType scaleType)
{
    if (m_scaleType == scaleType)
        return;

    m_scaleType = scaleType;
    emit scaleTypeChanged(m_scaleType);
}

KAJ_END_NAMESPACE
