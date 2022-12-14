#pragma once
#include "SDL.h"
#include "SDLInitializer.h"
#include "Window.h"
#include "Renderer.h"



#include <string>
#include <vector>
#include <stdio.h>
#include "Apple.h"
#include "Player.h"

class RenderManager;
struct ResourceManager;

class Game
{
	Player m_Player;
	Apple apple;

public:
	void Run();

private:
	void PollEvents() noexcept;
	void Update();
	void Render() noexcept;

private:
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

private:
	SDLInitializer m_SDLInitializer = {};
	Window m_MainWindow{ Window::Title("Snake"), Window::Dimensions{ 800, 600 } };
	Renderer m_MainRenderer{ m_MainWindow.m_Window };
};