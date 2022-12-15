#include "Player.h"


void Player::Update(float deltaTime) noexcept {
	if (m_SnakeBody.size() > 1) {
		UpdateBodyPosition();
	}
	UpdateHeadPosition();
}
void Player::UpdateInput(SDL_Keycode key) noexcept {
	switch (key) {
	case SDLK_LEFT: {
		if (m_CurrentMovementDirection != MovementDirection::RIGHT) {
			m_CurrentMovementDirection = MovementDirection::LEFT;
		}
	}break;
	case SDLK_RIGHT: {
		if (m_CurrentMovementDirection != MovementDirection::LEFT) {
			m_CurrentMovementDirection = MovementDirection::RIGHT;
		}
	}break;
	case SDLK_UP: {
		if (m_CurrentMovementDirection != MovementDirection::DOWN) {
			m_CurrentMovementDirection = MovementDirection::UP;
		}
	}break;
	case SDLK_DOWN: {
		if (m_CurrentMovementDirection != MovementDirection::UP) {
			m_CurrentMovementDirection = MovementDirection::DOWN;
		}
	}break;
	default: {
		return;
	}
	}
}
void Player::Render(const Renderer* renderer) const noexcept {
	RenderHead(renderer);
	RenderBody(renderer);
}


Utility::Position Player::GetSnakeHeadPosition() const noexcept {
	return std::begin(m_SnakeBody)->m_Position;
}
Utility::Size Player::GetSnakeHeadSize() const noexcept {
	return m_PartSize;
}
const std::vector<Entity>& Player::GetSnakeBody() const noexcept {
	return m_SnakeBody;
}


void Player::RandomizeLocation(Dimensions screenSize) noexcept {
	const int RandomX = rand() % (screenSize.m_Width - m_PartSize.m_Width);
	const int RandomY = rand() % (screenSize.m_Height - m_PartSize.m_Height);

	m_StartingPositionX = RandomX;
	m_StartingPositionY = RandomY;

	*std::begin(m_SnakeBody)._Ptr = Entity(RandomX, RandomY);
}


void Player::UpdateHeadPosition() noexcept {
	auto* SnakeHeadPosition = &std::begin(m_SnakeBody)->m_Position;

	switch (m_CurrentMovementDirection) {
	case MovementDirection::LEFT: {
		LastPosition = *SnakeHeadPosition;
		SnakeHeadPosition->m_X -= m_MovementSpeed;
	}break;
	case MovementDirection::RIGHT: {
		LastPosition = *SnakeHeadPosition;
		SnakeHeadPosition->m_X += m_MovementSpeed;
	}break;
	case MovementDirection::UP: {
		LastPosition = *SnakeHeadPosition;
		SnakeHeadPosition->m_Y -= m_MovementSpeed;
	}break;
	case MovementDirection::DOWN: {
		LastPosition = *SnakeHeadPosition;
		SnakeHeadPosition->m_Y += m_MovementSpeed;
	}break;
	default: {
		break;
	}
	}
}
void Player::UpdateBodyPosition() noexcept {
	std::shift_right(std::begin(m_SnakeBody), std::end(m_SnakeBody), 1);
}


void Player::RenderHead(const Renderer* renderer) const noexcept {
	if (renderer == nullptr)
		return;

	renderer->RenderToBackBuffer(std::begin(m_SnakeBody)->m_Position, m_HeadColor, m_PartSize);
}
void Player::RenderBody(const Renderer* renderer) const noexcept {
	if (renderer == nullptr)
		return;

	auto RenderEachPart = [this, renderer](const Entity& body) noexcept {
		renderer->RenderToBackBuffer(body.m_Position, m_BodyColor, m_PartSize);
	};
	std::for_each(std::begin(m_SnakeBody), std::end(m_SnakeBody), RenderEachPart);
}


void Player::AddBodyPart() noexcept {
	const Entity NewBodyPart = m_SnakeBody.back();
	m_SnakeBody.emplace_back(NewBodyPart);
}
void Player::Reset() noexcept {
	m_CurrentMovementDirection = MovementDirection::NONE;
	m_SnakeBody.clear();
	m_SnakeBody.push_back({ m_StartingPositionX, m_StartingPositionY });
}
