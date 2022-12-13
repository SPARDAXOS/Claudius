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
		//Render(renderManager); //Not yet till i get rid of the render manager

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

		default: {
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


	playerOne.Update(DeltaTime);

	// Player colliding on theirself.
	for (int i = 0; i < playerOne.player_score; i++)
	{
		if (playerOne.trans.GetPosition() == playerOne.parts[i].trans.GetPosition())
		{
			playerOne.ResetPlayer();
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
	if (playerOne.trans.GetPosition() == apple.trans.GetPosition())
	{
		playerOne.player_score++;
		apple.trans.SetPosition((rand() % 125) * 10.0f, (rand() % 70) * 10.0f);
	}
}

void Game::Render(RenderManager& renderManager)
{
	playerOne.Render(renderManager);
	apple.Render(renderManager);
}

void Game::OnKeyDown(SDL_Keycode key) noexcept
{
	playerOne.OnKeyDown(key);
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

