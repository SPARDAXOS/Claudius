#pragma once
#include "SDL_video.h"
#include <stdexcept>
#include <string.h>


struct Window {
	struct Dimensions {
		unsigned int m_Width = 800;
		unsigned int m_Height = 600;
	};
	using Title = std::string_view;

public:
	Window(Title title, SDL_WindowFlags flags)
		:m_Title(title)
	{
		m_Window
			= SDL_CreateWindow(m_Title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, m_Dimensions.m_Width, m_Dimensions.m_Height, flags);

		if (m_Window == nullptr) {
			throw std::runtime_error::runtime_error(SDL_GetError());
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

public:
	Title m_Title = "Default";
	const Dimensions m_Dimensions = { 800, 600 };
	SDL_Window* m_Window = nullptr;
};