#pragma once

namespace Utility{

	struct Position {
		int m_X = 0, m_Y = 0;
	};

	struct Color {
		Uint8 m_R = 0, m_G = 0, m_B = 0, m_A = 255;
	};

	struct Size {
		unsigned int m_Width = 0, m_Height = 0;
	};


	inline bool operator==(const Position& lhs, const Position& rhs) noexcept {
		return &lhs == &rhs;
	}
}

