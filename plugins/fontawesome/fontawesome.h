#ifndef FONTAWESOME_H
#define FONTAWESOME_H

#include <kajpluginbase.h>

//#include "fonticons.h"

class QQmlApplicationEngine;
class FontAwesome : public KajPluginBase
{
    Q_OBJECT
public:
    const QString fa;
#include "tool/_fontawesome_defines.h"
#define X(name, data) static const QString fa_##name;
    __fa_foreach(X)
//#include "tool/_fontawesome_undefs.h"

    explicit FontAwesome(QObject *parent = nullptr);

public slots:
#if QT_QML_LIB
    static bool init(const QQmlApplicationEngine *engine);
#endif

};

KAJ_DECLARE_QML_PLUGIN(FontAwesome)

#endif // FONTAWESOME_H
