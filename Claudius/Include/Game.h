#pragma once
#include "SDLInitializer.h"
#include "Window.h"
#include "Renderer.h"
#include "Player.h"
#include "Utility.h"
#include <random>



class Game final {
	using WindowDimensions = Window::Dimensions;
	using WindowTitle = Window::Title;
	using Position = DataTypes::Position;
	using Size = DataTypes::Size;
	using Apple = DataTypes::Position;

public:
	void Run();

private:
	void PollEvents() noexcept;
	void Update();
	void Render() const noexcept;

	void RunCollisionChecks();
	[[nodiscard]] bool IsPlayerCollidingWithApple(const SDL_Rect& player) const noexcept;
	[[nodiscard]] bool IsPlayerCollidingWithBody(const SDL_Rect& player) const noexcept;
	[[nodiscard]] bool IsPlayerCollidingWithScreenBounds() const noexcept;

	void ResetGameState() noexcept;
	void AppleEaten();
	void RandomizeEntitiesPositions() noexcept;

	[[nodiscard]] float CalculateDeltaTime() noexcept;
	[[nodiscard]] bool ShouldUpdateGame(float deltaTime) noexcept;

	int m_LastTick = 0;
	int m_CurrentTick = 0;
	float m_ElapsedTime = 0.0f;

	bool m_Running = false;
	float m_UpdateRate = 0.1f;
	float m_UpdateAccumulator = 0.0f;

	Player m_Player = {};
	Apple m_Apple = {};

	SDLInitializer m_SDLInitializer = { SDL_INIT_EVERYTHING };
	Window m_MainWindow = { WindowTitle{ "Snake" }, SDL_WINDOW_SHOWN };
	Renderer m_MainRenderer{ m_MainWindow.m_Window, SDL_RENDERER_ACCELERATED, SDL_BLENDMODE_BLEND };
};