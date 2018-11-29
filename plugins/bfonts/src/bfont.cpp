#include <QFontDatabase>
#include <QDebug>

#include "bfont.h"

KAJ_BEGIN_NAMESPACE

BFont::BFont(QObject *parent) : KajPluginBase(parent)
{

}

bool BFont::init()
{
    QStringList fonts = QString(KAJ_BFONTS).split(' ');
    foreach (QString font, fonts) {
        if(font.startsWith("-D"))
            font.remove(0, 2);

        int ret = QFontDatabase::addApplicationFont(":/fonts/" + font);

        if (ret == -1)
            qWarning("The font '%s' could not be loaded", qPrintable(font));
    }
    return fonts.count() > 0;
}

KAJ_END_NAMESPACE
