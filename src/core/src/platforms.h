#ifndef PLATFORMS_H
#define PLATFORMS_H

#include "kajglobal.h"
#include <QtCore/QObject>
#include <QtCore/qglobal.h>

KAJ_BEGIN_NAMESPACE

class KAJ_EXPORT Platforms : public QObject
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

KAJ_END_NAMESPACE

#endif // PLATFORMS_H
