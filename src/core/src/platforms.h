#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

class Platforms : public QObject
{
    Q_OBJECT
public:
    explicit Platforms(QObject *parent = 0);

public slots:
    bool isMobile();
    bool isDesktop();
    bool isAndroid();
    bool isIos();
    bool isLinux();
    bool isWindows();
    bool isMacOsX();
};

#endif // PLATFORMS_H
