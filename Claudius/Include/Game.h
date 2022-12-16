#pragma once
#include "SDL.h"
#include "SDLInitializer.h"
#include "Window.h"
#include "Renderer.h"
#include "Apple.h"
#include "Player.h"
#include <random>



class Game {
	using WindowDimensions = Window::Dimensions;
	using WindowTitle = Window::Title;
	using Position = Utility::Position;
	using Size = Utility::Size;

public:
	void Run() noexcept;

private:
	void PollEvents() noexcept;
	void Update() noexcept;
	void Render() const noexcept;

private:
	void RunCollisionChecks() noexcept;
	[[nodiscard]] bool CheckPlayerAppleCollision(const SDL_Rect& player) const noexcept;
	[[nodiscard]] bool CheckPlayerBodyCollision(const SDL_Rect& player) const noexcept;
	[[nodiscard]] bool CheckPlayerBoundries() const noexcept;
	SDL_Rect CreateSDLRect(Position position) const noexcept;

private:
	void ResetGameState() noexcept;
	void AppleEaten() noexcept;
	void RandomizeEntitiesPositions() noexcept;

private:
	[[nodiscard]] float CalculateDeltaTime() noexcept;
	[[nodiscard]] bool ShouldUpdateGame(float deltaTime) noexcept;

private:
	int m_LastTick = 0;
	int m_CurrentTick = 0;
	float m_ElapsedTime = 0.0f;

private:
	bool m_Running = false;
	const float m_UpdateRate = 0.1f;
	float m_UpdateAccumulator = 0.0f;

private:
	Player m_Player = {};
	Apple m_Apple = {};

private:
	SDLInitializer m_SDLInitializer = { SDL_INIT_EVERYTHING };
	Window m_MainWindow = { WindowTitle{ "Snake" }, SDL_WINDOW_SHOWN };
	Renderer m_MainRenderer{ m_MainWindow.m_Window, SDL_RENDERER_ACCELERATED, SDL_BLENDMODE_BLEND };
};