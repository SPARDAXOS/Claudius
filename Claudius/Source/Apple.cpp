#pragma once

#include <iostream>
#include "Apple.h"
#include "RenderManager.h"

//Constructor.
Apple::Apple()
{
	color.SetColor(0, 255, 0, 0); //Could be initialized
	rect.SetBounds(0, 0, 10, 10); //it was 10 10 but should set those to some proper shit by the game.
	trans.SetPosition(100, 200); //Could be initialized by game
}

void Apple::Render(RenderManager& renderManager)
{
	renderManager.Render(rect, color, trans);
}


