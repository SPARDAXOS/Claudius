#pragma once
#include "SDL.h"
#include "Utility.h"
#include <stdexcept>


class Renderer final {
	using Color = DataTypes::Color;
	using Position = DataTypes::Position;

public:
	Renderer(SDL_Window*& window, SDL_RendererFlags flags, SDL_BlendMode blendMode) {
		m_Renderer = SDL_CreateRenderer(window, -1, flags);
		if (m_Renderer == nullptr) {
			throw std::runtime_error(SDL_GetError());
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

	void Render(Position drawPosition, Color drawColor) const noexcept;
	void Present() const noexcept;

private:
	void SetRenderColor(const SDL_Color color) const noexcept;
	void Clear() const noexcept;

	SDL_Renderer* m_Renderer = nullptr;
};
