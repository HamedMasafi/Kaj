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

};

#endif // FILEUTILS_H
