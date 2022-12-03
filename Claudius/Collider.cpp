#include "Collider.h"

Collider::Collider() : rect(0,0,0,0)
{
}

Collider::Collider(const Collider& rhs) : rect(rhs.rect)
{
}

Collider::Collider(int x, int y, int w, int h) : rect(x,y,w,h)
{
}

void Collider::SetBounds(int x, int y, int w, int h)
{
	rect.SetBounds(x, y, w, h);
}
