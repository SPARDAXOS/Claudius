#include "Renderer.h"





void Renderer::Render(const EntityBody& body) noexcept {
	//So why in the fuck do i need a position? Its the rect first two vars isnt it?

	SetRenderColor(body.m_Color);
	SDL_RenderFillRect(m_Renderer, &body.m_Rect); //Weird looking
}


void Renderer::PresentFrame() noexcept {
	SDL_RenderPresent(m_Renderer);
	SetRenderColor(SDL_Color(0));
	Clear();
}


void Renderer::Clear() noexcept {
	SDL_RenderClear(m_Renderer);
}
void Renderer::SetRenderColor(SDL_Color color) noexcept {
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
}