#pragma once

#include <string>
#include <vector>
#include "SDL.h"
#include <stdio.h>
#include "Apple.h"
#include "Player.h"

class RenderManager;
struct ResourceManager;

class Game
{
	Player playerOne;
	Apple apple;

public:
	void Run();

	void Render(RenderManager& rendererManager);

private:
	void PollEvents() noexcept;

private:
	void Update();
	void OnKeyDown(SDL_Keycode key) noexcept;



private:
	[[nodiscard]] bool ShouldUpdateGame(float deltaTime) noexcept;

private:
	float CalculateDeltaTime() noexcept;

private:
	float m_UpdateRate = 1.0f;
	float m_UpdateAccumulator = 0.0f;

private: //Time
	int m_LastTick = 0;
	int m_CurrentTick = 0;
	float m_ElapsedTime = 0.0f;

private:
	bool m_Running = false;
};