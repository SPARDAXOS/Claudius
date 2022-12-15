#pragma once
#include "SDL.h"
#include "Utility.h"


struct Entity {
	using Position = Utility::Position;

	Entity() = default;
	Entity(int x, int y) noexcept
	{
		m_Position.m_X = x;
		m_Position.m_Y = y;
	};
	friend bool operator==(const Entity& lhs, const Entity& rhs) noexcept {
		return &lhs == &rhs;
	}

	Position m_Position;
};
