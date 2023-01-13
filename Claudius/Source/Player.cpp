#include "Player.h"

using Position = DataTypes::Position;
using SnakeVector = std::vector<Position>;


void Player::Update([[maybe_unused]] float deltaTime) noexcept {
	UpdatePosition();
}
void Player::UpdateInput(SDL_Keycode key) noexcept {
	using namespace EntityAttributes;
	using namespace MovementDirections;

	switch (key) {
	case SDLK_LEFT: {
		if (m_MovementVelocity != RIGHT) {
			m_MovementVelocity = LEFT;
		}
	}break;
	case SDLK_RIGHT: {
		if (m_MovementVelocity != LEFT) {
			m_MovementVelocity = RIGHT;
		}
	}break;
	case SDLK_UP: {
		if (m_MovementVelocity != DOWN) {
			m_MovementVelocity = UP;
		}
	}break;
	case SDLK_DOWN: {
		if (m_MovementVelocity != UP) {
			m_MovementVelocity = DOWN;
		}
	}break;
	default: {
		return;
	}
	}
}
void Player::Render(const Renderer& renderer) const noexcept {
	RenderHead(renderer);
	RenderBody(renderer);
}


size_t Player::GetSnakeBodySize() const noexcept {
	return m_SnakeBody.size();
}
const Position& Player::GetSnakeHead() const noexcept {
	return m_SnakeBody.front();
}
Position& Player::GetSnakeHead() noexcept {
	return m_SnakeBody.front();
}
[[nodiscard]] SnakeVector Player::GetSnakeBodyOnly() const noexcept {
	SnakeVector CopiedVector;
	CopiedVector.reserve(m_SnakeBody.size());
	std::copy(std::begin(m_SnakeBody) + 1, std::end(m_SnakeBody), std::back_inserter(CopiedVector));
	return CopiedVector;
}


void Player::AddBodyPart() {
	try {
		m_SnakeBody.emplace_back(m_SnakeBody.back());
	}
	catch (const std::exception& exception) {
		std::cerr << exception.what() << std::endl;
		return;
	}
}
void Player::Reset() noexcept {
	m_MovementVelocity = { 0, 0 };
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
	m_SnakeBody.front() += m_MovementVelocity;
}
void Player::UpdateBodyPosition() noexcept {
	std::shift_right(std::begin(m_SnakeBody), std::end(m_SnakeBody), 1);
}


void Player::RenderHead(const Renderer& renderer) const noexcept {
	renderer.Render(m_SnakeBody.front(), EntityAttributes::SNAKE_HEAD_COLOR);
}
void Player::RenderBody(const Renderer& renderer) const noexcept {
	auto RenderEachPart = [this, &renderer](const Position& body) noexcept {
		renderer.Render(body, EntityAttributes::SNAKE_BODY_COLOR);
	};
	std::for_each(std::begin(m_SnakeBody), std::end(m_SnakeBody), RenderEachPart);
}


