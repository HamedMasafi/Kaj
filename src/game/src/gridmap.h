#ifndef GridMap_H
#define GridMap_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>
#include <QtQuick/QQuickPaintedItem>
#include <QTransform>

#include "kajglobal.h"

KAJ_BEGIN_NAMESPACE

class GridMap;
class GridMapPrivate;
class GridMapAttached : public QObject{
    Q_OBJECT

    QQuickItem *_parent;

    Q_PROPERTY(int x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(int y READ y WRITE setY NOTIFY yChanged)
    Q_PROPERTY(int width READ width WRITE setWidth NOTIFY widthChanged)
    Q_PROPERTY(int height READ height WRITE setHeight NOTIFY heightChanged)
    Q_PROPERTY(bool isFloat READ isFloat WRITE setIsFloat NOTIFY isFloatChanged)

public:
    GridMapAttached(QObject *parent = 0);

    int x() const;
    int y() const;
    int width() const;
    int height() const;
    bool isFloat() const;

public slots:
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    void setIsFloat(bool isFloat);

signals:
    void xChanged(int x);

    void yChanged(int y);

    void widthChanged(int width);

    void heightChanged(int height);

    void isFloatChanged(bool isFloat);

private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;

    QQuickItem *entity() const;
    GridMap *parentGrid() const;
    void invalidateItem() const;
    bool m_isFloat;
};

class KAJ_EXPORT GridMap : public QQuickPaintedItem
{
    Q_OBJECT
    GridMapPrivate *d_ptr;
    Q_DECLARE_PRIVATE(GridMap)

    Q_PROPERTY(int cols READ cols WRITE setCols NOTIFY colsChanged)
    Q_PROPERTY(int rows READ rows WRITE setRows NOTIFY rowsChanged)
    Q_PROPERTY(qreal degree READ degree WRITE setDegree NOTIFY degreeChanged)
    Q_PROPERTY(qreal gridOpacity READ gridOpacity WRITE setGridOpacity NOTIFY gridOpacityChanged)
    Q_PROPERTY(QColor gridColor READ gridColor WRITE setGridColor NOTIFY gridColorChanged)
    Q_PROPERTY(QUrl imageSource READ imageSource WRITE setImageSource NOTIFY imageSourceChanged)
    Q_PROPERTY(QRect hilightedRect READ hilightedRect WRITE setHilightedRect NOTIFY hilightedRectChanged)
    Q_PROPERTY(QColor highlightColor READ highlightColor WRITE setHighlightColor NOTIFY highlightColorChanged)


public:
    GridMap(QQuickItem *parent = 0);

    static GridMapAttached *qmlAttachedProperties(QObject *);

    Q_INVOKABLE int cols() const;
    Q_INVOKABLE int rows() const;
    Q_INVOKABLE qreal degree() const;

    Q_INVOKABLE QPointF demap(QPointF p) const;

    Q_INVOKABLE QPoint map(QPoint p) const;
    Q_INVOKABLE QPointF map(QPointF p) const;
    Q_INVOKABLE QRect map(QRect rc) const;
    Q_INVOKABLE QRectF map(QRectF rc) const;
    Q_INVOKABLE QRectF map(int col, int row, int width, int height) const;
    Q_INVOKABLE QPolygonF mapPolygon(QRectF rc) const;
    Q_INVOKABLE QPolygonF mapPolygon(int col, int row, int width, int height) const;
    Q_INVOKABLE qreal gridOpacity() const;
    Q_INVOKABLE QColor gridColor() const;
    Q_INVOKABLE QUrl imageSource() const;
    Q_INVOKABLE QRect hilightedRect() const;
    Q_INVOKABLE QPointF hotpoint(QQuickItem *child) const;
    Q_INVOKABLE QSizeF cellSize() const;
    Q_INVOKABLE QColor highlightColor() const;

    Q_INVOKABLE bool isFree(int col, int row) const;
    Q_INVOKABLE bool isFree(int col, int row, int width, int height) const;
    Q_INVOKABLE bool isFree(QRect rc) const;

public slots:
    void setCols(int cols);
    void setRows(int rows);
    void setDegree(qreal degree);
    void setGridOpacity(qreal gridOpacity);
    void setGridColor(QColor gridColor);
    void setImageSource(QUrl imageSource);
    void invalidate(QQuickItem *child);
    void setHilightedRect(QRect hilightedRect);
    void setHighlightColor(QColor highlightColor);

signals:
    void colsChanged(int cols);
    void rowsChanged(int rows);
    void degreeChanged(qreal degree);

    void gridOpacityChanged(qreal gridOpacity);

    void gridColorChanged(QColor gridColor);

    void imageSourceChanged(QUrl imageSource);

    void hilightedRectChanged(QRect hilightedRect);

    void highlightColorChanged(QColor highlightColor);

protected:
    void widthChanged();
    void heightChanged();

    void paint(QPainter *painter);

    void childEvent(QChildEvent *event);
    bool event(QEvent *);
};

KAJ_END_NAMESPACE

QML_DECLARE_TYPEINFO(KAJ_WRAP_NAMESPACE(GridMap), QML_HAS_ATTACHED_PROPERTIES)

#endif // GRIDMAP_H

