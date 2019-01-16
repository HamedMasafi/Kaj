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

#ifndef SWIPEGESTUREMANAGER_H
#define SWIPEGESTUREMANAGER_H

#include <QQuickItem>
#include "kajglobal.h"

KAJ_BEGIN_NAMESPACE

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

KAJ_END_NAMESPACE

#endif // SWIPEGESTUREMANAGER_H
