#pragma once

#include "Rectangle.h"
#include "Color.h"
#include "Transform.h"

class RenderManager; //<- Kinda like #include "RenderManager.h", not exactly. Can't use functions. Google forward declaration.

struct Apple
{

	Apple(); //Rule of zero
	void Render(RenderManager& renderManager);

	Rectangle rect;
	Color color;
	Transform trans;

	bool new_apple = false;
};