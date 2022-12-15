#pragma once
#include "Renderer.h"
#include "Window.h"

class Apple {
	using Dimensions = Window::Dimensions;

public:
	void Render(const Renderer* renderer) const noexcept;

public:
	void RandomizeLocation(Dimensions screenSize) noexcept;

public:
	Utility::Position GetPosition() const noexcept;
	Utility::Size GetSize() const noexcept;

private:
	Utility::Position m_Body;
	const Utility::Color m_Color{ 255, 0, 0, 255 };
	Utility::Size m_Size{ 20, 20 };
};