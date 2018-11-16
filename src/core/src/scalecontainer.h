#ifndef SCALECONTAINER_H
#define SCALECONTAINER_H

#include <QtCore/qglobal.h>
#include <QQuickItem>

#include "kajglobal.h"

class QQuickTransform;

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT ScaleContainer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(qreal scaleSize READ scaleSize WRITE setScaleSize NOTIFY scaleSizeChanged)

    QQuickTransform *transform;
    qreal m_scaleSize;

public:
    ScaleContainer(QQuickItem *parent = nullptr);
    void setChild(QQuickItem *child);
    qreal scaleSize() const;

public slots:
    void setScaleSize(qreal scaleSize);

signals:
    void scaleSizeChanged(qreal scaleSize);

private slots:
    void child_childrenRectChanged(const QRectF &);

protected:
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);
    void itemChange(ItemChange, const ItemChangeData &) Q_DECL_OVERRIDE;
};

KAJ_END_NAMESPACE

#endif // SCALECONTAINER_H
