#pragma once
#include "SDL_video.h"
#include <stdexcept>
#include <string.h>


struct Window final {
	struct Dimensions {
		unsigned int m_Width = 800;
		unsigned int m_Height = 600;
	};
	using Title = std::string_view;

public:
	Window(Title title, SDL_WindowFlags flags) {
		m_Window
			= SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Dimensions.m_Width, m_Dimensions.m_Height, flags);

		if (m_Window == nullptr) {
			throw std::runtime_error(SDL_GetError());
		}
	}
	~Window() noexcept {
		SDL_DestroyWindow(m_Window);
	}

	Window() = delete;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	const Dimensions m_Dimensions = { 800, 600 };
	SDL_Window* m_Window = nullptr;
};