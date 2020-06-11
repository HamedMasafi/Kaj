#include "icons.h"
#include "../plugins/mdi/_mdi_defines.h"

QString Icons::get(const Icons::IconType &type)
{
    switch (type) {
    case ArrowUp:
        return __mdi_arrow_up;
    case ArrowRight:
        return __mdi_arrow_right;
    case ArrowLeft:
        return __mdi_arrow_left;
    case ArrowDown:
        return __mdi_arrow_down;
    case Ellipsis:
        return __mdi_ellipse;
    }
    return "";
}

QString Icons::fontName() const
{
    return "Material Icons";
}
