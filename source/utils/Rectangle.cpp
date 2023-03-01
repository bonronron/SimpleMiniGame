#include "../../include/utils/Rectangle.h"


bool Rectangle::inside(float x, float y) const
{
    // IX.A Implement this function, that returns true if the point <x,y> is inside this rectangle.
    
    return topLeft.x > x && bottomRight.x < x&& topLeft.y > y && bottomRight.y < y;
    //return false; // you can delete this once IX.A is complete.
}

bool Rectangle::intersects(const Rectangle& rect) const
{
    // IX.B Implement this function, that returns true if the rectangle "rect" overlaps with this rectangle.
    
    bool intersect = false;

    return false; // you can delete this once IX.B is complete.
}

