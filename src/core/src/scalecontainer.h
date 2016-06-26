#ifndef SCALECONTAINER_H
#define SCALECONTAINER_H

#include <QtCore/qglobal.h>
#include <QQuickItem>

#include "kajglobal.h"

QT_BEGIN_NAMESPACE

class KAJ_EXPORT ScaleContainer : public QQuickItem
{
    Q_OBJECT

public:
    ScaleContainer(QQuickItem *parent, QQuickItem *child = 0);
    void setChild(QQuickItem *child);

protected:
    void geometryChanged(const QRectF & newGeometry, const QRectF & oldGeometry);

public slots:
};

QT_END_NAMESPACE

#endif // SCALECONTAINER_H
