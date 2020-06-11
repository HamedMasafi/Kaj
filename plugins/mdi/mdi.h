#ifndef MDI_H
#define MDI_H

#include "../src/core/src/kajpluginbase.h"

class QQmlApplicationEngine;
class MDI : public KajPluginBase
{
    Q_OBJECT
public:
    explicit MDI(QObject *parent = nullptr);

public slots:
#if QT_QML_LIB
    static bool init(const QQmlApplicationEngine *engine);
#endif
};

KAJ_DECLARE_QML_PLUGIN(MDI)

#endif // MDI_H
