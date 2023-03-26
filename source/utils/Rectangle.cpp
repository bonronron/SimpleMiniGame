#include "../../include/utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    return x >= topLeft.x && x <= bottomRight.x && y >= topLeft.y && y <= bottomRight.y;
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    return ((inside(rect.topLeft.x, rect.bottomRight.y)) || 
        (inside(rect.bottomRight.x, rect.bottomRight.y)) || 
            (inside(rect.bottomRight.x, rect.topLeft.y)) || 
                (inside(rect.topLeft.x, rect.topLeft.y)) ||
        (rect.inside(topLeft.x, bottomRight.y)) ||
        (rect.inside(bottomRight.x, bottomRight.y)) ||
        (rect.inside(bottomRight.x, topLeft.y)) ||
        (rect.inside(topLeft.x, topLeft.y)));
}

