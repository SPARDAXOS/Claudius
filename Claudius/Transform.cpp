#include "Transform.h"

Transform::Transform() : position(), rotation(0.0f)
{
}

Transform::Transform(const Transform& rhs) : position(rhs.position), rotation(rhs.rotation)
{
}

Transform::Transform(float x, float y, float rotation) : position(x,y), rotation(rotation)
{
}

void Transform::SetPosition(const float x, const float y)
{
	position.x = x;
	position.y = y;
}

void Transform::ChangePosition(const float x, const float y)
{
	position.x += x;
	position.y += y;
}

void Transform::SetRotation(const float rotation)
{
	this->rotation = rotation;
}

void Transform::ChangeRotation(const float rotation)
{
	this->rotation += rotation;
}

Vector2 Transform::GetPosition()
{
	return position;
}

float Transform::GetX()
{
	return position.x;
}

float Transform::GetY()
{
	return position.y;
}

float Transform::GetRotation()
{
	return rotation;
}
