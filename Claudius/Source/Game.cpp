#include "Game.h"


void Game::Run() {
	std::srand(SDL_static_cast(unsigned int, time(nullptr)));

	m_Running = true;
	RandomizeEntitiesPositions();

	while (m_Running) {
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
void Game::Update() {
	const float DeltaTime = CalculateDeltaTime();
	m_ElapsedTime += DeltaTime;

	if (!ShouldUpdateGame(DeltaTime))
		return;

	m_Player.Update(DeltaTime);
	RunCollisionChecks();
}
void Game::Render() const noexcept {
	m_Player.Render(m_MainRenderer);
	m_MainRenderer.Render(m_Apple, EntityAttributes::APPLE_COLOR);
	m_MainRenderer.Present();
}


void Game::RunCollisionChecks() {
	const SDL_Rect SnakeHeadRect = SDLTypesConstruction::ConstructSDLType(m_Player.GetSnakeHeadCopy());

	if (m_Player.GetSnakeBodySize() > 1) {
		if (IsPlayerCollidingWithBody(SnakeHeadRect)) {
			ResetGameState();
		}
	}
	if (IsPlayerCollidingWithApple(SnakeHeadRect)) {
		AppleEaten();
	}
	if (IsPlayerCollidingWithScreenBounds()) {
		ResetGameState();
	}
}
[[nodiscard]] bool Game::IsPlayerCollidingWithApple(const SDL_Rect& player) const noexcept {
	const SDL_Rect AppleRect = SDLTypesConstruction::ConstructSDLType(m_Apple);
	return SDL_HasIntersection(&player, &AppleRect);;
}
[[nodiscard]] bool Game::IsPlayerCollidingWithBody(const SDL_Rect& player) const noexcept {
	std::vector<Position> Body = m_Player.GetSnakeBodyOnly();

	auto CheckHeadWithBody = [this, &player](const Position& entity) noexcept {
		const SDL_Rect BodyPartRect = SDLTypesConstruction::ConstructSDLType(entity);
		return SDL_HasIntersection(&player, &BodyPartRect);
	};
	return std::any_of(std::begin(Body), std::end(Body), CheckHeadWithBody);
}
[[nodiscard]] bool Game::IsPlayerCollidingWithScreenBounds() const noexcept {
	const WindowDimensions Boundries = m_MainWindow.m_Dimensions;
	const Position PlayerPosition = m_Player.GetSnakeHeadCopy();

	const bool ConditionPositiveX = PlayerPosition.m_X >= SDL_static_cast(int, Boundries.m_Width);
	const bool ConditionNegativeX = PlayerPosition.m_X < 0;
	const bool ConditionPositiveY = PlayerPosition.m_Y >= SDL_static_cast(int, Boundries.m_Height);
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
void Game::AppleEaten() {
	m_Player.AddBodyPart();
	Randomizer::RandomizePosition(m_Apple, m_MainWindow.m_Dimensions);
}
void Game::RandomizeEntitiesPositions() noexcept {
	Randomizer::RandomizePosition(m_Player.GetSnakeHeadReference(), m_MainWindow.m_Dimensions);
	Randomizer::RandomizePosition(m_Apple, m_MainWindow.m_Dimensions);
}


[[nodiscard]] float Game::CalculateDeltaTime() noexcept {
	m_LastTick = m_CurrentTick;
	m_CurrentTick = SDL_GetTicks();
	return (m_CurrentTick - m_LastTick) / 1000.0f;
}
[[nodiscard]] bool Game::ShouldUpdateGame(float deltaTime) noexcept {
	m_UpdateAccumulator += deltaTime;
	if (m_UpdateAccumulator >= m_UpdateRate) {
		m_UpdateAccumulator -= m_UpdateRate;
		return true;
	}
	return false;
}

