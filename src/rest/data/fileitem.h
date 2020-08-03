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

#ifndef FILEITEM_H
#define FILEITEM_H

#include "../global.h"
#include "../pair.h"
#include <QObject>
#include <QUrl>

KAJ_REST_BEGIN_NAMESPACE

class FileItem : public Pair
{
    Q_OBJECT
    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)

    QUrl m_source;

public:
    explicit FileItem(QObject *parent = nullptr);

    QUrl source() const;

public slots:
    void setSource(QUrl source);

signals:
    void sourceChanged(QUrl source);
};

KAJ_REST_END_NAMESPACE

#endif // FILEITEM_H
