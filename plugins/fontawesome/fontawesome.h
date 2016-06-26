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
    static void registerFontAwesome(QQmlApplicationEngine *engine);
#endif

};

KAJ_DECLARE_PLUGIN(FontAwesome)

#endif // FONTAWESOME_H
