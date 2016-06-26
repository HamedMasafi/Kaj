#ifndef TOOJQMLHELPER_H
#define TOOJQMLHELPER_H

#include <QtCore/QObject>
#include <QtCore/qglobal.h>

#include "kajpluginbase.h"
#include "kajglobal.h"

QT_BEGIN_NAMESPACE

class QQmlApplicationEngine;
class KAJ_EXPORT KajQmlHelper : public QObject
{
    Q_OBJECT
public:
    explicit KajQmlHelper(QObject *parent = 0);

    static void registerQmlTypes(QQmlApplicationEngine *engine);
    static void registerPlugins();
};

QT_END_NAMESPACE

#endif // TOOJQMLHELPER_H
