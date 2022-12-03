#pragma once

#include "Rectangle.h"

struct Collider
{
	Collider();
	Collider(const Collider& rhs);
	Collider(int x, int y, int w, int h);

	void SetBounds(int x, int y, int w, int h);

	Rectangle rect;
};