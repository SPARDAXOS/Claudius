#pragma once
#include "Entity.h"
#include "Renderer.h"
#include "Window.h"

class Apple {
	using Dimensions = Window::Dimensions;
	using Position = Utility::Position;
	using Color = Utility::Color;
	using Size = Utility::Size;

public:
	void Render(const Renderer* renderer) const noexcept;

public:
	void RandomizeLocation(Dimensions screenSize) noexcept;

public:
	Position GetPosition() const noexcept;
	Size GetSize() const noexcept;

private:
	Entity m_Body;
	const Color m_Color{ 255, 0, 0, 255 };
	Size m_Size{ 20, 20 };
};