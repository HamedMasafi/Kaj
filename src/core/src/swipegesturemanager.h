#ifndef SWIPEGESTUREMANAGER_H
#define SWIPEGESTUREMANAGER_H

#include <QQuickItem>
#include "kajglobal.h"

QT_BEGIN_NAMESPACE

class SwipeGestureManagerPrivate;
class KAJ_EXPORT SwipeGestureManager: public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int orientation READ orientation WRITE setOrientation NOTIFY orientationChanged)
    Q_PROPERTY(int minimum READ minimum WRITE setMinimum NOTIFY minimumChanged)
    Q_PROPERTY(int mouseX READ mouseX NOTIFY mouseXChanged)
    Q_PROPERTY(int mouseY READ mouseY NOTIFY mouseYChanged)

    enum GrabState {
        Grabbed,
        NotGrabbed,
        Unknown
    };

public:
    SwipeGestureManager(QQuickItem *parent = 0);
    ~SwipeGestureManager();

    void setMinimum(int min);
    int minimum() const;

    void setOrientation(int ori);
    int orientation() const;

    int mouseX() const;
    int mouseY() const;

signals:
    void minimumChanged();
    void orientationChanged();

    void positionChanged();
    void mouseXChanged();
    void mouseYChanged();
    void pressed();
    void released();

protected:
    bool childMouseEventFilter(QQuickItem *item, QEvent *event);

private:
    SwipeGestureManagerPrivate  *const d_ptr;
    Q_DECLARE_PRIVATE(SwipeGestureManager)
};

QT_END_NAMESPACE

#endif // SWIPEGESTUREMANAGER_H
