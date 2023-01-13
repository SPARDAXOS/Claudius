#include "Utility.h"


void Randomizer::RandomizePosition(Position& position, Window::Dimensions windowDimensions) noexcept {
	using namespace EntityAttributes;

	const int RandomX = rand() % (windowDimensions.m_Width - ENTITY_SIZE.m_Width);
	const int RandomY = rand() % (windowDimensions.m_Height - ENTITY_SIZE.m_Height);
	position = { RandomX, RandomY };
}
