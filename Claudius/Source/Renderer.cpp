#include "Renderer.h"



void Renderer::Render(Position drawPosition, Color drawColor) const noexcept {
	using namespace SDLTypesConstruction;

	SetRenderColor(ConstructSDLType(drawColor));
	const SDL_Rect DrawRect = ConstructSDLType(drawPosition);
	SDL_RenderFillRect(m_Renderer, &DrawRect);
}
void Renderer::Present() const noexcept {
	SDL_RenderPresent(m_Renderer);
	Clear();
}


void Renderer::SetRenderColor(const SDL_Color color) const noexcept {
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
}
void Renderer::Clear() const noexcept {
	SetRenderColor(SDL_Color(0));
	SDL_RenderClear(m_Renderer);
}