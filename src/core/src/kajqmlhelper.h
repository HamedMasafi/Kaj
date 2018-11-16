#ifndef KAJQMLHELPER_H
#define KAJQMLHELPER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "kajpluginbase.h"
#include "kajglobal.h"

class QQmlApplicationEngine;

KAJ_BEGIN_NAMESPACE
class KAJ_EXPORT KajQmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit KajQmlHelper(QObject *parent = 0);

    static void registerQmlTypes(QQmlApplicationEngine *engine);
    static void registerPlugins();
};

KAJ_END_NAMESPACE

#endif // KAJQMLHELPER_H
