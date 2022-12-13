#include "Rectangle.h"

Rectangle::Rectangle() : x(0), y(0), w(0), h(0)
{
}

Rectangle::Rectangle(const Rectangle& rhs) : x(rhs.x), y(rhs.y), w(rhs.w), h(rhs.h)
{
}

Rectangle::Rectangle(int x, int y, int w, int h) : x(x), y(y), w(w), h(h)
{
}

void Rectangle::SetBounds(int x, int y, int w, int h)
{
	this->x = x; this->y = y; this->w = w; this->h = h;
}
