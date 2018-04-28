#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QObject>

class FileUtils : public QObject
{
    Q_OBJECT
public:
    explicit FileUtils(QObject *parent = nullptr);

public slots:
    QString readFile(const QString &filePath);
    void writeFile(const QString &filePath, const QString &content);
    QStringList filesInDir(const QString &dirPath);

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

#endif // FILEUTILS_H
