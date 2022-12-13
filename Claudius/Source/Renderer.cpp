#include "Renderer.h"





void Renderer::RenderRect(const SDL_Rect& rect) noexcept {
	SDL_RenderFillRect(m_Renderer, &rect); //Weird looking
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