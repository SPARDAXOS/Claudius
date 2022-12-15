#pragma once
#include "Renderer.h"
#include "Window.h"

struct Apple {
	using Dimensions = Window::Dimensions;
	using Position = Utility::Position;

public:
	void Render(const Renderer* renderer) const noexcept {
		if (renderer == nullptr) {
			return;
		}
		renderer->Render(m_Body, AppleColor);
	}
	void RandomizeLocation(Dimensions screenSize) noexcept {
		const int RandomX = rand() % (screenSize.m_Width - EntitySize.m_Width);
		const int RandomY = rand() % (screenSize.m_Height - EntitySize.m_Height);

		m_Body = Position(RandomX, RandomY);
	}

public:
	Position m_Body;
};