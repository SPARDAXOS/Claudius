#include "Player.h"

using Position = Utility::Position;
using SnakeVector = std::vector<Position>;


void Player::Update([[maybe_unused]] float deltaTime) noexcept {
	UpdatePosition();
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


size_t Player::GetSnakeBodySize() const noexcept {
	return m_SnakeBody.size();
}
Position Player::GetSnakeHead() const noexcept {
	return m_SnakeBody.front();
}
[[nodiscard]] SnakeVector Player::GetSnakeBodyOnly() const noexcept {
	SnakeVector CopiedVector;
	CopiedVector.reserve(m_SnakeBody.size());
	std::copy(std::begin(m_SnakeBody) + 1, std::end(m_SnakeBody), std::back_inserter(CopiedVector));
	return CopiedVector;
}


void Player::RandomizePosition(WindowDimensions windowDimensions) noexcept {
	const int RandomX = rand() % (windowDimensions.m_Width - EntitySize.m_Width);
	const int RandomY = rand() % (windowDimensions.m_Height - EntitySize.m_Height);

	m_SnakeBody.front() = { RandomX, RandomY };
}
void Player::AddBodyPart() noexcept {
	m_SnakeBody.emplace_back(m_SnakeBody.back());
}
void Player::Reset() noexcept {
	m_CurrentMovementDirection = MovementDirection::NONE;
	m_SnakeBody.clear();
	m_SnakeBody.push_back({});
}


void Player::UpdatePosition() noexcept {
	if (m_SnakeBody.size() > 1) {
		UpdateBodyPosition();
	}
	UpdateHeadPosition();
}
void Player::UpdateHeadPosition() noexcept {
	Position* SnakeHeadPosition = std::begin(m_SnakeBody)._Ptr;

	switch (m_CurrentMovementDirection) {
	case MovementDirection::LEFT: {
		SnakeHeadPosition->m_X -= SnakeMovementSpeed;
	}break;
	case MovementDirection::RIGHT: {
		SnakeHeadPosition->m_X += SnakeMovementSpeed;
	}break;
	case MovementDirection::UP: {
		SnakeHeadPosition->m_Y -= SnakeMovementSpeed;
	}break;
	case MovementDirection::DOWN: {
		SnakeHeadPosition->m_Y += SnakeMovementSpeed;
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
	renderer->Render(m_SnakeBody.front(), SnakeHeadColor);
}
void Player::RenderBody(const Renderer* renderer) const noexcept {
	if (renderer == nullptr)
		return;

	auto RenderEachPart = [this, renderer](const Position& body) noexcept {
		renderer->Render(body, SnakeBodyColor);
	};
	std::for_each(std::begin(m_SnakeBody), std::end(m_SnakeBody), RenderEachPart);
}


