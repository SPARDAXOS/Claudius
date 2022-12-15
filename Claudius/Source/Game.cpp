#include "Game.h"


void Game::Run() noexcept {
	std::srand(static_cast<unsigned int>(time(nullptr)));

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
	while (SDL_PollEvent(&Event))
	{
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


	//I might want to rework some things here. 
	//The collision with apple causes a part to be created on top of the snake head.
	//The update moves the snake and fixes any parts on top of the snake head.
	//The collision with body will work successfully as long as:
	//Update puts the snake in a good state where no body part is on top of the other.
	//Collision with body is done after update and after collision with apple.
	//Consider moving some collision functions into the snake or something so it doesnt look so suspecsios.

	m_Player.Update(DeltaTime);
	
	if (CheckPlayerBodyCollision()) {
		ResetGameState();
	}

	if (CheckPlayerAppleCollision()) {
		m_Player.AddBodyPart();
		m_Apple.RandomizeLocation(m_MainWindow.m_Dimensions);
		m_CurrentScore++;
	}
	if (CheckPlayerBoundries()) {
		ResetGameState();
	}
	//TODO: make func for it. Like add score or something
	//TODO: make func for collisions so i can hide the order importance better
}

void Game::Render() noexcept {
	m_Player.Render(&m_MainRenderer);
	m_Apple.Render(&m_MainRenderer);
	m_MainRenderer.PresentBackBuffer();
}


SDL_Rect Game::CreateSDLRect(Utility::Position position, Utility::Size size) const noexcept {
	return SDL_Rect(position.m_X, position.m_Y, size.m_Width, size.m_Height);
}
[[nodiscard]] bool Game::CheckPlayerAppleCollision() const noexcept {
	const auto SnakeHeadPosition = m_Player.GetSnakeHead();
	const auto SnakeHeadSize = m_Player.GetSnakeHeadSize();
	const SDL_Rect PlayerRect = CreateSDLRect(SnakeHeadPosition, SnakeHeadSize);

	const auto ApplePosition = m_Apple.GetPosition();
	const auto AppleSize = m_Apple.GetSize();
	const SDL_Rect AppleRect = CreateSDLRect(ApplePosition, AppleSize);

	const auto Results = SDL_HasIntersection(&PlayerRect, &AppleRect);
	if (Results == SDL_TRUE){
		return true;
	}
	return false;
}
[[nodiscard]] bool Game::CheckPlayerBodyCollision() const noexcept {
	std::vector<Utility::Position> Body = m_Player.GetSnakeBody();
	if (Body.size() <= 1) {
		return false;
	}

	Body.erase(std::begin(Body)); //Get rid of head

	const auto Head = m_Player.GetSnakeHead();
	const auto HeadSize = m_Player.GetSnakeHeadSize();
	const SDL_Rect HeadRect = CreateSDLRect(Head, HeadSize);

	auto CheckHeadWithBody = [this, HeadRect, &Body, HeadSize](const Utility::Position& entity) noexcept {
		//if (entity == *std::begin(Body)) {
		//	return false;
		//}

		const SDL_Rect BodyPartRect = CreateSDLRect(entity, HeadSize);
		const auto Results = SDL_HasIntersection(&HeadRect, &BodyPartRect);
		if (Results == SDL_TRUE) {
			return true;
		}
		return false;
	};

	return std::any_of(std::begin(Body), std::end(Body), CheckHeadWithBody);
}
[[nodiscard]] bool Game::CheckPlayerBoundries() const noexcept {
	const Window::Dimensions Boundries = m_MainWindow.m_Dimensions;
	const Utility::Position PlayerPosition = m_Player.GetSnakeHead();

	const bool ConditionPositiveX = PlayerPosition.m_X >= Boundries.m_Width;
	const bool ConditionNegativeX = PlayerPosition.m_X < 0;
	const bool ConditionPositiveY = PlayerPosition.m_Y >= Boundries.m_Height;
	const bool ConditionNegativeY = PlayerPosition.m_Y < 0;
	if (ConditionPositiveX || ConditionNegativeX || ConditionPositiveY || ConditionNegativeY) {
		return true;
	}
	return false;
}


void Game::RandomizeEntitiesPositions() noexcept {
	m_Player.RandomizeLocation(m_MainWindow.m_Dimensions);
	m_Apple.RandomizeLocation(m_MainWindow.m_Dimensions);
}
void Game::ResetGameState() noexcept {
	m_Player.Reset();
	RandomizeEntitiesPositions();
	m_CurrentScore = 0;
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

