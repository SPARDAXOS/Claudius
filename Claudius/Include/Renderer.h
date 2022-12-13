#pragma once
#include "SDL.h"
#include "Color.h"
#include <stdexcept>


//Note: I made this into its own class while the rest into wrappers. Am i right? I mean everything just manages one resource.

class Renderer {
public:
	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

	explicit Renderer(SDL_Window*& window) {
		m_Renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
		if (m_Renderer == nullptr)
		{
			throw std::runtime_error::runtime_error(SDL_GetError());
		}
	}
	~Renderer() noexcept {
		SDL_DestroyRenderer(m_Renderer);
	}

public:
	void RenderRect(const SDL_Rect& rect) noexcept;
	void PresentFrame() noexcept; //Not sure yet how i render stuff
	void SetRenderColor(SDL_Color color) noexcept;
	void Clear() noexcept;

private:


private: //Maybe you cant reach it? you just ask it to do stuff

	SDL_Renderer* m_Renderer = nullptr;
};
