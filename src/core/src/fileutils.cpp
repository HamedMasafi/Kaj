#include "fileutils.h"

#include <QDir>
#include <QFile>
#include <QUrl>

FileUtils::FileUtils(QObject *parent) : QObject(parent)
{

}

QString FileUtils::readFile(const QString &filePath)
{
    QFile f(filePath);

    if (!f.exists())
        return "";
    if (!f.open(QIODevice::ReadOnly))
        return "";

    auto buffer = f.readAll();
    f.close();
    return buffer;
}

void FileUtils::writeFile(const QString &filePath, const QString &content)
{
    QFile f(filePath);
    if (!f.open(QIODevice::WriteOnly))
        return;

    f.write(content.toLocal8Bit());
    f.close();
}

QStringList FileUtils::filesInDir(const QString &dirPath)
{
    QDir d(dirPath);
    if (!d.exists())
        return QStringList();
    return d.entryList();
}

QString FileUtils::readFile(const QUrl &fileUrl)
{
    return readFile(fileUrl.toLocalFile());
}

void FileUtils::writeFile(const QUrl &fileUrl, const QString &content)
{
    writeFile(fileUrl.toLocalFile(), content);
}

QStringList FileUtils::filesInDir(const QUrl &dirUrl)
{
    return filesInDir(dirUrl.toLocalFile());
}

bool FileUtils::fileExists(const QUrl &fileUrl)
{
    return QFile(fileUrl.toLocalFile()).exists();
}

bool FileUtils::dirExists(const QUrl &dirUrl)
{
    return QDir(dirUrl.toLocalFile()).exists();
}
