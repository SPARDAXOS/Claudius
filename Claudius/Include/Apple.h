#pragma once
#include "Renderer.h"
#include "Window.h"

struct Apple {
	using WindowDimensions = Window::Dimensions;
	using Position = Utility::Position;

public:
	void Render(const Renderer* renderer) const noexcept {
		if (renderer == nullptr) {
			return;
		}
		renderer->Render(m_Body, AppleColor);
	}
	void RandomizePosition(WindowDimensions windowDimensions) noexcept {
		const int RandomX = rand() % (windowDimensions.m_Width - EntitySize.m_Width);
		const int RandomY = rand() % (windowDimensions.m_Height - EntitySize.m_Height);

		m_Body = Position(RandomX, RandomY);
	}

public:
	Position m_Body;
};