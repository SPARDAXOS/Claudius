// 2019-12-05 Teemu Laiho

#include "Game.h"
#include "RenderManager.h"
#include <iostream>


void Game::Run() {

	m_Running = true;

	while (m_Running)
	{
		PollEvents();
		
		Update();
		Render(); //Not yet till i get rid of the render manager

	}
}


void Game::PollEvents() noexcept {
	SDL_Event Event;
	while (SDL_PollEvent(&Event))
	{
		switch (Event.type)
		{
		case SDL_QUIT: m_Running = false; break;
		case SDL_KEYDOWN: OnKeyDown(Event.key.keysym.sym); break;

		default: { //Bad the message will always be there!
			printf("Error: unhandled event \n");
		}
		}
	}
}




void Game::Update() {
	const float DeltaTime = CalculateDeltaTime();
	m_ElapsedTime += DeltaTime;

	if (!ShouldUpdateGame(DeltaTime))
		return;


	m_Player.Update(DeltaTime);


	//Move to collision or something and also use an sdl collision function instead of this shit
	// Player colliding on theirself.
	for (int i = 0; i < m_Player.player_score; i++)
	{
		if (m_Player.trans.GetPosition() == m_Player.parts[i].trans.GetPosition())
		{
			m_Player.ResetPlayer();
		}
	}

	//DISABLED AFTER THE NEW WINDOW WAS ADDED!
	// Player going out of X bounds.
	//if (playerOne.trans.GetX() > width || playerOne.trans.GetX() < 0)
	//{
	//	playerOne.ResetPlayer();
	//}

	//// Player going out of Y bounds.
	//if (playerOne.trans.GetY() > height || playerOne.trans.GetY() < 0)
	//{
	//	playerOne.ResetPlayer();
	//}

	// Player collide on apple.
	if (m_Player.trans.GetPosition() == apple.trans.GetPosition())
	{
		m_Player.player_score++;
		apple.trans.SetPosition((rand() % 125) * 10.0f, (rand() % 70) * 10.0f);
	}
}

void Game::Render() noexcept
{
	m_MainRenderer.Render(m_Player.m_Body);





	//m_MainRenderer.SetRenderColor(SDL_Color(0));
	//m_MainRenderer.Clear();


	//for (auto&& entry : renderManager.rectEntries)
	//{
	//	SDL_Color EntryColor(entry.color.r, entry.color.g, entry.color.b, entry.color.a);
	//	m_MainRenderer.SetRenderColor(EntryColor);

	//	SDL_Rect rect{ static_cast<int>(entry.trans.position.x),
	//				   static_cast<int>(entry.trans.position.y),
	//				   entry.rect.w,
	//				   entry.rect.h };

	//	m_MainRenderer.Render(rect);
	//}
	//m_MainRenderer.PresentFrame();






	//playerOne.Render(renderManager);
	//apple.Render(renderManager);
}

void Game::OnKeyDown(SDL_Keycode key) noexcept
{
	m_Player.OnKeyDown(key);
}


bool Game::ShouldUpdateGame(float deltaTime) noexcept {
	m_UpdateAccumulator += deltaTime;
	if (m_UpdateAccumulator >= m_UpdateRate) {
		m_UpdateAccumulator -= m_UpdateRate;
		return true;
	}

	return false;
}


float Game::CalculateDeltaTime() noexcept {
	m_LastTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();

	return (m_CurrentTick - m_LastTick) / 1000.0f;
}

