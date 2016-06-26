#ifndef SWIPEGESTUREMANAGER_P_H
#define SWIPEGESTUREMANAGER_P_H

#include "swipegesturemanager.h"

QT_BEGIN_NAMESPACE

class SwipeGestureManagerPrivate{
public:
    SwipeGestureManagerPrivate(SwipeGestureManager *parent);

    SwipeGestureManager::GrabState state;
    QPoint pin;
    int minimum;
    int orientation;
    QPoint position;

private :
    SwipeGestureManager  *q_ptr;
    Q_DECLARE_PUBLIC(SwipeGestureManager)
};

QT_END_NAMESPACE

#endif // SWIPEGESTUREMANAGER_P_H

