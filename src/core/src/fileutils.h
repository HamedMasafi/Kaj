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

    QString readFile(const QString &filePath);
    void writeFile(const QString &filePath, const QString &content);
    QStringList filesInDir(const QString &dirPath);

public slots:
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
