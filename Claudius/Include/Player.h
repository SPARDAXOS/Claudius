#pragma once
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"

#include <iostream>
#include <vector>
#include <algorithm>


class Player final {
	using WindowDimensions = Window::Dimensions;
	using Position = DataTypes::Position;
	using SnakeVector = std::vector<Position>;

public:
	void Update([[maybe_unused]] float deltaTime) noexcept;
	void UpdateInput(SDL_Keycode key) noexcept;
	void Render(const Renderer& renderer) const noexcept;

	size_t GetSnakeBodySize() const noexcept;
	const Position& GetSnakeHead() const noexcept;
	Position& GetSnakeHead() noexcept;
	[[nodiscard]] SnakeVector GetSnakeBodyOnly() const noexcept;

	void AddBodyPart();
	void Reset() noexcept;

private:
	void UpdatePosition() noexcept;
	void UpdateBodyPosition() noexcept;
	void UpdateHeadPosition() noexcept;

	void RenderHead(const Renderer& renderer) const noexcept;
	void RenderBody(const Renderer& renderer) const noexcept;

	SnakeVector m_SnakeBody = { {} };

	Position m_MovementVelocity = { 0, 0 };
};