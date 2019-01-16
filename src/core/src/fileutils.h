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

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include "kajglobal.h"
#include <QObject>

KAJ_BEGIN_NAMESPACE

class FileUtils : public QObject
{
    Q_OBJECT
public:
    explicit FileUtils(QObject *parent = nullptr);

    void writeFile(const QString &filePath, const QString &content);
    QStringList filesInDir(const QString &dirPath);

public slots:
    QString readFile(const QString &filePath);
    QString readFile(const QUrl &fileUrl);
    void writeFile(const QUrl &filePath, const QString &content);
    QStringList filesInDir(const QUrl &dirPath);
    bool fileExists(const QUrl &fileUrl);
    bool dirExists(const QUrl &dirUrl);
    bool mkdir(const QUrl &dirUrl);
    QString dirname(const QUrl &fileUrl);
    bool removeFile(const QUrl &fileUrl);
    bool copyFile(const QUrl &from, const QUrl &to);
};

KAJ_END_NAMESPACE

#endif // FILEUTILS_H
