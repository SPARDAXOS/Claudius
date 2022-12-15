#include "Apple.h"


void Apple::Render(const Renderer* renderer) const noexcept {
	if (renderer == nullptr) {
		return;
	}
	renderer->RenderToBackBuffer(m_Body, m_Color, m_Size);
}


void Apple::RandomizeLocation(Dimensions screenSize) noexcept {
	const int RandomX = rand() % (screenSize.m_Width - m_Size.m_Width);
	const int RandomY = rand() % (screenSize.m_Height - m_Size.m_Height);

	m_Body = Utility::Position(RandomX, RandomY);
}


Utility::Position Apple::GetPosition() const noexcept {
	return m_Body;
}
Utility::Size Apple::GetSize() const noexcept {
	return m_Size;
}
