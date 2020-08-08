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
    Q_ENUMS(ScaleType)
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
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry) override;
    void itemChange(ItemChange, const ItemChangeData &) override;
    QSGNode *updatePaintNode(QSGNode *, UpdatePaintNodeData *) override;
};

KAJ_END_NAMESPACE

QML_DECLARE_TYPE(KAJ_WRAP_NAMESPACE(ScaleContainer))
QML_DECLARE_TYPEINFO(KAJ_WRAP_NAMESPACE(ScaleContainer), QML_HAS_ATTACHED_PROPERTIES)

#endif // SCALECONTAINER_H
