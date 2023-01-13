#pragma once
#include "SDL.h"
#include <iostream>
#include "Window.h"

namespace DataTypes {

	struct Position {
		int m_X = 0, m_Y = 0;

		Position& operator+=(const Position& rhs) noexcept {
			m_X += rhs.m_X;
			m_Y += rhs.m_Y;
			return *this;
		}
		bool operator==(const Position& rhs) const noexcept {
			if (m_X == rhs.m_X && m_Y == rhs.m_Y) {
				return true;
			}
			return false;
		}
		bool operator!=(const Position& rhs) const noexcept {
			return !(*this == rhs);
		}
	};

	struct Color {
		Uint8 m_R = 0, m_G = 0, m_B = 0, m_A = 255;
	};

	struct Size {
		unsigned int m_Width = 0, m_Height = 0;
	};
}


namespace EntityAttributes {
	using Color = DataTypes::Color;
	using Size = DataTypes::Size;

	static constexpr Color APPLE_COLOR{ 255, 0, 0, 255 };
	static constexpr Color SNAKE_HEAD_COLOR{ 0, 255, 0, 255 };
	static constexpr Color SNAKE_BODY_COLOR{ 0, 255, 0, 255 };

	static constexpr int SNAKE_MOVEMENT_SPEED = 15;

	static constexpr Size ENTITY_SIZE{ 10, 10 };
}

namespace MovementDirections {
	using DataTypes::Position;
	using namespace EntityAttributes;

	static constexpr Position UP{ 0, -SNAKE_MOVEMENT_SPEED };
	static constexpr Position DOWN{ 0, SNAKE_MOVEMENT_SPEED };
	static constexpr Position LEFT{ -SNAKE_MOVEMENT_SPEED, 0 };
	static constexpr Position RIGHT{ SNAKE_MOVEMENT_SPEED, 0 };
	static constexpr Position NONE{ 0, 0 };
}

namespace Randomizer {
	using namespace DataTypes;

	void RandomizePosition(Position& position, Window::Dimensions windowDimensions) noexcept;
}

namespace SDLTypesConstruction {
	constexpr SDL_Color ConstructSDLType(DataTypes::Color color) noexcept {
		return SDL_Color(color.m_R, color.m_G, color.m_B, color.m_A);
	}
	constexpr SDL_Rect ConstructSDLType(const DataTypes::Position position) noexcept {
		using namespace EntityAttributes;
		return SDL_Rect(position.m_X, position.m_Y, ENTITY_SIZE.m_Width, ENTITY_SIZE.m_Height);
	}
}
