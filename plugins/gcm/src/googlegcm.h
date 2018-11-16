#ifndef GOOGLEGCM_H
#define GOOGLEGCM_H

#include <kajpluginbase.h>

KAJ_BEGIN_NAMESPACE

class GoogleGcm : public KajPluginBase
{
    Q_OBJECT

    KAJ_SINGLETON_UNIT(GoogleGcm)


public:
    GoogleGcm(QObject *parent = nullptr);

public slots:
    static bool init();
#if QT_QML_LIB
    static bool init(const QQmlApplicationEngine *engine);
#endif
};

KAJ_END_NAMESPACE

KAJ_DECLARE_CPP_PLUGIN(GoogleGcm)
KAJ_DECLARE_QML_PLUGIN(GoogleGcm)

#endif // GOOGLEGCM_H
