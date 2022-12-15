#pragma once
#include "SDL_video.h"
#include <stdexcept>
#include <string.h>


struct Window {
public:
	struct Dimensions {
		unsigned int m_Width = 800;
		unsigned int m_Height = 600;
	};
	using Title = std::string_view;

public:
	Window() = delete;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;

	Window(Window&&) = delete;
	Window& operator=(Window&&) = delete;

	Window(Title title, Dimensions dimensions)
		: m_Title(title), m_Dimensions(dimensions)
	{
		m_Window 
			= SDL_CreateWindow(title.data(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, dimensions.m_Width, dimensions.m_Height, SDL_WindowFlags::SDL_WINDOW_SHOWN);

		if (m_Window == nullptr)
		{
			throw std::runtime_error::runtime_error(SDL_GetError());
		}
	}
	~Window() noexcept {
		SDL_DestroyWindow(m_Window);
	}

public:
	Title m_Title = "Error";
	Dimensions m_Dimensions = {};
	SDL_Window* m_Window = nullptr;
};