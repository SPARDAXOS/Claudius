#include "Renderer.h"



void Renderer::RenderToBackBuffer(Position drawPosition, Color drawColor, Size drawSize) const noexcept {
	SetRenderColor(ConstructSDLType(drawColor));
	const SDL_Rect DrawRect = ConstructSDLType(drawPosition, drawSize);
	SDL_RenderFillRect(m_Renderer, &DrawRect);
}


void Renderer::PresentBackBuffer() noexcept {
	SDL_RenderPresent(m_Renderer);
	Clear();
}


void Renderer::SetRenderColor(const SDL_Color color) const noexcept {
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
}
void Renderer::Clear() noexcept {
	SetRenderColor(SDL_Color(0));
	SDL_RenderClear(m_Renderer);
}


const SDL_Color Renderer::ConstructSDLType(Color color) const noexcept {
	return SDL_Color(color.m_R, color.m_G, color.m_B, color.m_A);
}
const SDL_Rect Renderer::ConstructSDLType(Position position, Size size) const noexcept {
	return SDL_Rect(position.m_X, position.m_Y, size.m_Width, size.m_Height);
}