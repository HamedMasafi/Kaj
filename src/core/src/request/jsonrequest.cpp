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

#include "jsonrequest.h"

#include <QtCore/QJsonDocument>

KAJ_BEGIN_NAMESPACE

JsonObjectRequest::JsonObjectRequest(QObject *parent) : WebRequest(parent)
{ }

void JsonObjectRequest::processResponse(QByteArray buffer)
{
    QJsonObject obj = QJsonDocument::fromJson(buffer).object();
    if (obj.isEmpty())
        emit replyError(0, "");
    else
        emit finished(obj);
}

void JsonObjectRequest::beforeSend(QNetworkRequest &request)
{

}

KAJ_END_NAMESPACE
