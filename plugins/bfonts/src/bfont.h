#ifndef BFONT_H
#define BFONT_H

#include "kajpluginbase.h"

KAJ_BEGIN_NAMESPACE

class BFont : public KajPluginBase
{
    Q_OBJECT

public:
    BFont(QObject *parent = 0);

    static bool init();
};

KAJ_END_NAMESPACE

KAJ_DECLARE_CPP_PLUGIN(BFont)

#endif // BFONT_H
