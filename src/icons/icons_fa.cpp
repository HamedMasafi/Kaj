#include "icons.h"
#include "fontawesome/fonticons.h"

QString Icons::get(const Icons::IconType &type)
{
    switch (type) {
    case ArrowUp:
        return fa_arrow_up;
    case ArrowRight:
        return fa_arrow_right;
    case ArrowLeft:
        return fa_arrow_left;
    case ArrowDown:
        return fa_arrow_down;
    case Ellipsis:
        return fa_ellipsis_v;
    }
    return "";
}

QString Icons::fontName() const
{
    return "FontAwesome";
}
