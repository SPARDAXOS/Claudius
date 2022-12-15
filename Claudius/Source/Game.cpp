#include "Game.h"


void Game::Run() noexcept {
	std::srand(SDL_static_cast(unsigned int, time(nullptr)));

	m_Running = true;

	RandomizeEntitiesPositions();

	while (m_Running)
	{
		PollEvents();
		Update();
		Render(); 
	}
}


void Game::PollEvents() noexcept {
	SDL_Event Event;
	while (SDL_PollEvent(&Event)) {
		switch (Event.type)
		{
		case SDL_QUIT: {
			m_Running = false;
		}break;
		case SDL_KEYDOWN: { 
			m_Player.UpdateInput(Event.key.keysym.sym);
		}break;
		default: {
			continue;
		}
		}
	}
}




void Game::Update() noexcept {
	const float DeltaTime = CalculateDeltaTime();
	m_ElapsedTime += DeltaTime;

	if (!ShouldUpdateGame(DeltaTime))
		return;

	m_Player.Update(DeltaTime);
	RunCollisionChecks();
}

void Game::Render() const noexcept {
	m_Player.Render(&m_MainRenderer);
	m_Apple.Render(&m_MainRenderer);
	m_MainRenderer.PresentBackBuffer();
}


SDL_Rect Game::CreateSDLRect(Position position) const noexcept {
	return SDL_Rect(position.m_X, position.m_Y, EntitySize.m_Width, EntitySize.m_Height);
}
void Game::RunCollisionChecks() noexcept {
	const SDL_Rect SnakeHeadRect = CreateSDLRect(m_Player.GetSnakeHead());

	if (m_Player.GetSnakeBodySize() > 1) {
		std::vector<Position> Body = m_Player.GetSnakeBodyOnly();
		if (CheckPlayerBodyCollision(SnakeHeadRect, Body)) {
			ResetGameState();
		}
	}
	if (CheckPlayerAppleCollision(SnakeHeadRect)) {
		AppleEaten();
	}
	if (CheckPlayerBoundries()) {
		ResetGameState();
	}
}
[[nodiscard]] bool Game::CheckPlayerAppleCollision(const SDL_Rect& player) const noexcept {
	const SDL_Rect AppleRect = CreateSDLRect(m_Apple.m_Body);
	const auto Results = SDL_HasIntersection(&player, &AppleRect);
	if (Results == SDL_TRUE) {
		return true;
	}
	return false;
}
[[nodiscard]] bool Game::CheckPlayerBodyCollision(const SDL_Rect& player, const std::vector<Position>& body) const noexcept {
	auto CheckHeadWithBody = [this, &player](const Position& entity) noexcept {
		const SDL_Rect BodyPartRect = CreateSDLRect(entity);
		const auto Results = SDL_HasIntersection(&player, &BodyPartRect);
		if (Results == SDL_TRUE) {
			return true;
		}
		return false;
	};

	return std::any_of(std::begin(body), std::end(body), CheckHeadWithBody);
}
[[nodiscard]] bool Game::CheckPlayerBoundries() const noexcept {
	const WindowDimensions Boundries = m_MainWindow.m_Dimensions;
	const Position PlayerPosition = m_Player.GetSnakeHead();

	const bool ConditionPositiveX = PlayerPosition.m_X >= Boundries.m_Width;
	const bool ConditionNegativeX = PlayerPosition.m_X < 0;
	const bool ConditionPositiveY = PlayerPosition.m_Y >= Boundries.m_Height;
	const bool ConditionNegativeY = PlayerPosition.m_Y < 0;
	if (ConditionPositiveX || ConditionNegativeX || ConditionPositiveY || ConditionNegativeY) {
		return true;
	}
	return false;
}


void Game::ResetGameState() noexcept {
	m_Player.Reset();
	RandomizeEntitiesPositions();
}
void Game::AppleEaten() noexcept {
	m_Player.AddBodyPart();
	m_Apple.RandomizeLocation(m_MainWindow.m_Dimensions);
}
void Game::RandomizeEntitiesPositions() noexcept {
	m_Player.RandomizeLocation(m_MainWindow.m_Dimensions);
	m_Apple.RandomizeLocation(m_MainWindow.m_Dimensions);
}


float Game::CalculateDeltaTime() noexcept {
	m_LastTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
	return (m_CurrentTick - m_LastTick) / 1000.0f;
}
bool Game::ShouldUpdateGame(float deltaTime) noexcept {
	m_UpdateAccumulator += deltaTime;
	if (m_UpdateAccumulator >= m_UpdateRate) {
		m_UpdateAccumulator -= m_UpdateRate;
		return true;
	}
	return false;
}

