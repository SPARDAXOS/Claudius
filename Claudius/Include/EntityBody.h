#pragma once
#include "SDL.h"


struct EntityBody {
	SDL_Color m_Color{ 0 };
	SDL_Point m_Position{ 0, 0 };
	SDL_Rect m_Rect{0, 0, 20, 20};
};