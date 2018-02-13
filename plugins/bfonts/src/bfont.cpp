#include <QFontDatabase>

#include "bfont.h"

BFont::BFont(QObject *parent) : KajPluginBase(parent)
{

}

bool BFont::init()
{
    QStringList fonts = QString(KAJ_BFONTS).split(' ');
    foreach (QString font, fonts) {
        if(font.startsWith("-D"))
            font.remove(0, 2);

        QFontDatabase::addApplicationFont(":/fonts/" + font);
    }
    return fonts.count() > 0;
}

