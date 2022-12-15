#pragma once
#include "SDL.h"
#include <stdexcept>

struct SDLInitializer {
	SDLInitializer(Uint32 flags) {
		const auto Results = SDL_Init(flags);
		if (Results == -1) {
			throw std::runtime_error::runtime_error(SDL_GetError());
		}
	}
	~SDLInitializer() noexcept {
		SDL_Quit();
	}

	SDLInitializer() = delete;
	SDLInitializer(const SDLInitializer&) = delete;
	SDLInitializer& operator=(const SDLInitializer&) = delete;

	SDLInitializer(SDLInitializer&&) = delete;
	SDLInitializer& operator=(SDLInitializer&&) = delete;
};