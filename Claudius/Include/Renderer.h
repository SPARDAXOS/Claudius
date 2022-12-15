#pragma once
#include "SDL.h"
#include "Utility.h"
#include "EntityAttributes.h"
#include <stdexcept>


class Renderer {
	using Color = Utility::Color;
	using Position = Utility::Position;

public:
	Renderer(SDL_Window*& window, SDL_RendererFlags flags, SDL_BlendMode blendMode) {
		m_Renderer = SDL_CreateRenderer(window, -1, flags);
		if (m_Renderer == nullptr) {
			throw std::runtime_error::runtime_error(SDL_GetError());
		}
		else {
			SDL_SetRenderDrawBlendMode(m_Renderer, blendMode);
		}
	}
	~Renderer() noexcept {
		SDL_DestroyRenderer(m_Renderer);
	}

	Renderer() = delete;
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	Renderer(Renderer&&) = delete;
	Renderer& operator=(Renderer&&) = delete;

public:
	void Render(Position drawPosition, Color drawColor) const noexcept;
	void Present() const noexcept;

private:
	void SetRenderColor(const SDL_Color color) const noexcept;
	void Clear() const noexcept;

private:
	const SDL_Color ConstructSDLType(Color color) const noexcept;
	const SDL_Rect ConstructSDLType(Position position) const noexcept;

private:
	SDL_Renderer* m_Renderer = nullptr;
};
