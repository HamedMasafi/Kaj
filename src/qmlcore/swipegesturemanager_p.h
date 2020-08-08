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

#ifndef SWIPEGESTUREMANAGER_P_H
#define SWIPEGESTUREMANAGER_P_H

#include "swipegesturemanager.h"

KAJ_BEGIN_NAMESPACE

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

KAJ_END_NAMESPACE

#endif // SWIPEGESTUREMANAGER_P_H

