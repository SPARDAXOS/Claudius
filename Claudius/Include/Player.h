#pragma once
#include "SDL.h"
#include "Entity.h"
#include "Renderer.h"
#include "Window.h"

#include <vector>
#include <algorithm>
#include <iterator>


class Player {
	using Dimensions = Window::Dimensions;
	using Position = Utility::Position;
	using Color = Utility::Color;
	using Size = Utility::Size;

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
	Position GetSnakeHeadPosition() const noexcept;
	Size GetSnakeHeadSize() const noexcept;
	const std::vector<Entity>& GetSnakeBody() const noexcept;

public:
	void RandomizeLocation(Dimensions screenSize) noexcept;
	void AddBodyPart() noexcept;
	void Reset() noexcept;

private:
	void UpdateBodyPosition() noexcept;
	void UpdateHeadPosition() noexcept;
	void CheckForBounds() noexcept;

private:
	void RenderHead(const Renderer* renderer) const noexcept;
	void RenderBody(const Renderer* renderer) const noexcept;

private:
	const Color m_HeadColor{ 255, 0, 0, 255 };
	const Color m_BodyColor{ 0, 255, 0, 255 };
	const Size m_PartSize{ 10, 10 };

private:
	const int m_MovementSpeed =15;
	int m_StartingPositionX = 0;
	int m_StartingPositionY = 0;

	Position LastPosition;

private:
	std::vector<Entity> m_SnakeBody = { { m_StartingPositionX, m_StartingPositionY } };

private:
	MovementDirection m_CurrentMovementDirection = MovementDirection::NONE;
};