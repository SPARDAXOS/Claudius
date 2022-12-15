#pragma once
#include "SDL.h"
#include "SDLInitializer.h"
#include "Window.h"
#include "Renderer.h"
#include "Apple.h"
#include "Player.h"
#include <random>


class Game {
public:
	void Run() noexcept;

private:
	void PollEvents() noexcept;
	void Update() noexcept;
	void Render() noexcept;

private:
	SDL_Rect CreateSDLRect(Utility::Position position, Utility::Size size) const noexcept;
	[[nodiscard]] bool CheckPlayerAppleCollision() const noexcept;
	[[nodiscard]] bool CheckPlayerBodyCollision() const noexcept;
	[[nodiscard]] bool CheckPlayerBoundries() const noexcept;

private:
	void ResetGameState() noexcept;
	void RandomizeEntitiesPositions() noexcept;

private:
	float CalculateDeltaTime() noexcept;
	[[nodiscard]] bool ShouldUpdateGame(float deltaTime) noexcept;

private:
	unsigned int m_CurrentScore = 0; //Could be moved back to player

private:
	int m_LastTick = 0;
	int m_CurrentTick = 0;
	float m_ElapsedTime = 0.0f;

private:
	bool m_Running = false;
	float m_UpdateRate = 0.1f;
	float m_UpdateAccumulator = 0.0f;

private:
	Player m_Player = {};
	Apple m_Apple = {};

private:
	SDLInitializer m_SDLInitializer = {};
	Window m_MainWindow{ Window::Title("Snake"), Window::Dimensions{ 800, 600 } };
	Renderer m_MainRenderer{ m_MainWindow.m_Window };
};