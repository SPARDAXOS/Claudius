#pragma once
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"
#include "EntityAttributes.h"

#include <vector>
#include <algorithm>
#include <iterator>


class Player {
	using WindowDimensions = Window::Dimensions;
	using Position = Utility::Position;
	using SnakeVector = std::vector<Position>;

private:
	enum class MovementDirection {
		NONE,
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

public:
	void Update([[maybe_unused]] float deltaTime) noexcept;
	void UpdateInput(SDL_Keycode key) noexcept;
	void Render(const Renderer* renderer) const noexcept;

public:
	size_t GetSnakeBodySize() const noexcept;
	Position GetSnakeHead() const noexcept;
	[[nodiscard]] SnakeVector GetSnakeBodyOnly() const noexcept;

public:
	void RandomizeLocation(WindowDimensions screenSize) noexcept;
	void AddBodyPart() noexcept;
	void Reset() noexcept;

private:
	void UpdatePosition() noexcept;
	void UpdateBodyPosition() noexcept;
	void UpdateHeadPosition() noexcept;

private:
	void RenderHead(const Renderer* renderer) const noexcept;
	void RenderBody(const Renderer* renderer) const noexcept;

private:
	SnakeVector m_SnakeBody = { {} };

private:
	MovementDirection m_CurrentMovementDirection = MovementDirection::NONE;
};