#pragma once
#include "SDL.h"
#include "Utility.h"
#include <stdexcept>


class Renderer {
	using Color = Utility::Color;
	using Position = Utility::Position;
	using Size = Utility::Size;

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
		else {
			SDL_SetRenderDrawBlendMode(m_Renderer, m_BlendMode);
		}
	}
	~Renderer() noexcept {
		SDL_DestroyRenderer(m_Renderer);
	}

public:
	void RenderToBackBuffer(Position drawPosition, Color drawColor, Size drawSize) const noexcept;
	void PresentBackBuffer() noexcept;

private:
	void SetRenderColor(const SDL_Color color) const noexcept;
	void Clear() noexcept;

private:
	const SDL_Color ConstructSDLType(Color color) const noexcept;
	const SDL_Rect ConstructSDLType(Position position, Size size) const noexcept;

private:
	const SDL_BlendMode m_BlendMode = SDL_BlendMode::SDL_BLENDMODE_BLEND;

private:
	SDL_Renderer* m_Renderer = nullptr;
};
