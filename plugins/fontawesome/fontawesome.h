#ifndef FONTAWESOME_H
#define FONTAWESOME_H

#include <kajpluginbase.h>

#include "fonticons.h"

class QQmlApplicationEngine;
class FontAwesome : public KajPluginBase
{
    Q_OBJECT
public:
    explicit FontAwesome(QObject *parent = 0);
    static void init();

public slots:
#if QT_QML_LIB
    static void init(const QQmlApplicationEngine *engine);
#endif

};

KAJ_DECLARE_QML_PLUGIN(FontAwesome)

#endif // FONTAWESOME_H
