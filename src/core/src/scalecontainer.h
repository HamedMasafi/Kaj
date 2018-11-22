#ifndef SCALECONTAINER_H
#define SCALECONTAINER_H

#include <QtCore/qglobal.h>
#include <QQuickItem>

#include "kajglobal.h"

class QQuickTransform;

KAJ_BEGIN_NAMESPACE

class ScaleContainerAttached : public QObject{
    Q_OBJECT

    QQuickItem *_parent;
    Q_PROPERTY(ScaleType scaleType READ scaleType WRITE setScaleType NOTIFY scaleTypeChanged)

public:
    ScaleContainerAttached(QObject *parent = nullptr);

    enum ScaleType {
        None,
        FitAcceptRatio,
        FitCrop
    };
    Q_ENUM(ScaleType)
    ScaleType scaleType() const;

public slots:
    void setScaleType(ScaleType scaleType);

signals:
    void scaleTypeChanged(ScaleType scaleType);

private:
    ScaleType m_scaleType;
};

class KAJ_EXPORT ScaleContainer : public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(qreal scaleSize READ scaleSize WRITE setScaleSize NOTIFY scaleSizeChanged)

    QQuickTransform *transform;
    qreal m_scaleSize;

public:
    ScaleContainer(QQuickItem *parent = nullptr);

    static ScaleContainerAttached *qmlAttachedProperties(QObject *object);

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

QML_DECLARE_TYPE(KAJ_WRAP_NAMESPACE(ScaleContainer))
QML_DECLARE_TYPEINFO(KAJ_WRAP_NAMESPACE(ScaleContainer), QML_HAS_ATTACHED_PROPERTIES)

#endif // SCALECONTAINER_H
