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

#ifndef UNITS_H
#define UNITS_H

#include <QObject>
#include "kajglobal.h"

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT Units : public QObject
{
    Q_OBJECT
    Q_PROPERTY(qreal virtualDpi READ virtualDpi WRITE setVirtualDpi NOTIFY
                   virtualDpiChanged)
    Q_PROPERTY(qreal fontScale READ fontScale WRITE setFontScale NOTIFY
                   fontScaleChanged)

    qreal m_virtualDpi;
    qreal m_fontScale;

public:
    explicit Units(QObject *parent = 0);

    Q_INVOKABLE QString screenName() const;

    Q_INVOKABLE qreal dp(int number);
    Q_INVOKABLE int sp(int number);
    Q_INVOKABLE int pt(int number);
    Q_INVOKABLE qreal mm(int number);
    Q_INVOKABLE qreal in(int number);
    Q_INVOKABLE qreal cm(int number);


    Q_INVOKABLE qreal fromDp(int number);
//    Q_INVOKABLE int fromSp(int number);
//    Q_INVOKABLE int fromPt(int number);
//    Q_INVOKABLE qreal fromMm(int number);
//    Q_INVOKABLE qreal fromIn(int number);
//    Q_INVOKABLE qreal fromCm(int number);

    int virtualDpi() const;
    qreal fontScale() const;

signals:
    void virtualDpiChanged(qreal virtualDpi);
    void fontScaleChanged(qreal fontScale);

public slots:
    void setVirtualDpi(qreal virtualDpi);
    void setFontScale(qreal fontScale);
};

KAJ_END_NAMESPACE

#endif // UNITS_H
