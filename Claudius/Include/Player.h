#pragma once
#include "SDL.h"
#include "Renderer.h"
#include "Window.h"
#include "EntityAttributes.h"

#include <vector>
#include <algorithm>
#include <iterator>


class Player {
	using Dimensions = Window::Dimensions;
	using Position = Utility::Position;

private:
	enum class MovementDirection {
		NONE,
		RIGHT,
		LEFT,
		UP,
		DOWN
	};

public:
	void Update(float deltaTime) noexcept;
	void UpdateInput(SDL_Keycode key) noexcept;
	void Render(const Renderer* renderer) const noexcept;

public:
	Position GetSnakeHead() const noexcept;
	size_t GetSnakeBodySize() const noexcept;
	std::vector<Position> GetSnakeBodyOnly() const noexcept;

public:
	void RandomizeLocation(Dimensions screenSize) noexcept;
	void AddBodyPart() noexcept;
	void Reset() noexcept;

private:
	void UpdateBodyPosition() noexcept;
	void UpdateHeadPosition() noexcept;

private:
	void RenderHead(const Renderer* renderer) const noexcept;
	void RenderBody(const Renderer* renderer) const noexcept;

private:
	std::vector<Position> m_SnakeBody = { {} };

private:
	MovementDirection m_CurrentMovementDirection = MovementDirection::NONE;
};