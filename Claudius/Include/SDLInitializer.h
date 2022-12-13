#pragma once
#include "SDL.h"
#include <stdexcept>

struct SDLInitializer {
	SDLInitializer(const SDLInitializer&) = delete;
	SDLInitializer& operator=(const SDLInitializer&) = delete;

	SDLInitializer(SDLInitializer&&) = delete;
	SDLInitializer& operator=(SDLInitializer&&) = delete;

	SDLInitializer() {
		const auto Results = SDL_Init(SDL_INIT_EVERYTHING);
		if (Results == -1) {
			throw std::runtime_error::runtime_error(SDL_GetError());
		}
	}
	~SDLInitializer() noexcept {
		SDL_Quit();
	}
};