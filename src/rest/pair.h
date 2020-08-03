/*
 * Copyright 2017 - Hamed Masafi, <hamed@tooska-co.ir>
 * This file is part of Kaj.
 *
 * Kaj is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Kaj is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with libcalendars.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef PAIR_H
#define PAIR_H

#include <QObject>
#include "global.h"

KAJ_REST_BEGIN_NAMESPACE

class Pair : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString value READ value WRITE setValue NOTIFY valueChanged)

    QString m_name;
    QString m_value;

public:
    explicit Pair(QObject *parent = nullptr);

    QString name() const;
    QString value() const;

public slots:
    void setName(QString name);
    void setValue(QString value);

signals:
    void nameChanged(QString name);
    void valueChanged(QString value);
};

KAJ_REST_END_NAMESPACE

#endif // PAIR_H
