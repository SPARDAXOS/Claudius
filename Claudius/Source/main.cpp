#include "SDL.h"
#include "SDLInitializer.h"
#include "Window.h"
#include "Renderer.h"
#include <iostream>
#include "RenderManager.h"
#include "ResourceManager.h"
#include "Game.h"
#include "Transform.h"

#undef main


int main()
{
	//try {
	//	SDLInitializer SDL;
	//	//Window NewWindow(Window::Title("Snake"), Window::Size(1920, 1080));
	//} //Score for those end here!
	//catch (const std::exception& exception) {
	//	std::cout << exception.what() << std::endl;
	//	return 1;
	//}


	SDLInitializer m_SDLInitializer;
	Window m_MainWindow(Window::Title("Snake"), Window::Dimensions{ 800, 600 });
	Renderer m_MainRenderer(m_MainWindow.m_Window);
	Game game;

	game.Run();



	

	RenderManager renderManager;

	



	game.Render(renderManager);



	m_MainRenderer.SetRenderColor(SDL_Color(0));
	m_MainRenderer.Clear();


	for (auto&& entry : renderManager.rectEntries)
	{
		SDL_Color EntryColor(entry.color.r, entry.color.g, entry.color.b, entry.color.a);
		m_MainRenderer.SetRenderColor(EntryColor);

		SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
					   static_cast<int>(entry.trans.position.y),
					   entry.rect.w,
					   entry.rect.h };

		m_MainRenderer.RenderRect(rect);
	}
	m_MainRenderer.PresentFrame();

	renderManager.Clear();

	return 0;
}
