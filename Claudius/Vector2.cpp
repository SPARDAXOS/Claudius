#include "Vector2.h"
#include <cmath>

Vector2::Vector2() : x(0.0f), y(0.0f)
{
}

Vector2::Vector2(const Vector2& rhs) : x(rhs.x), y(rhs.y) 
{
}

Vector2::Vector2(const float x, const float y) : x(x), y(y) 
{
}

Vector2& Vector2::operator=(const Vector2& rhs) 
{ 
	x = rhs.x; 
	y = rhs.y; 
	return *this; 
};

Vector2 Vector2::operator+(const Vector2& rhs) const
{
	return Vector2(x + rhs.x, y + rhs.y);
}

Vector2 Vector2::operator-(const Vector2& rhs) const
{
	return Vector2(x - rhs.x, y - rhs.y);
}

Vector2 Vector2::operator*(const Vector2& rhs) const
{
	return Vector2(x * rhs.x, y * rhs.y);
}

Vector2 Vector2::operator/(const Vector2& rhs) const
{
	return Vector2(x / rhs.x, y / rhs.y);
}

Vector2 Vector2::operator*(const float rhs) const
{
	return Vector2(x * rhs, y * rhs);
}

Vector2 Vector2::operator/(const float rhs) const
{
	return Vector2(x / rhs, y / rhs);
}

bool Vector2::operator==(const Vector2& rhs) const
{
	return (this->x == rhs.x && this->y == rhs.y);
}

Vector2 Vector2::perpendicular() const
{
	return Vector2(-y, x); // 90 degrees to the right
}

Vector2 Vector2::unit() const
{
	Vector2 result(*this); 
	result.normalize(); 
	return result;
}

float Vector2::length() const
{
	return sqrtf(x * x + y * y);
}

float Vector2::length_squared() const
{
	return x * x + y * y;
}

float Vector2::dot(const Vector2& rhs) const
{
	return x * rhs.x + y * rhs.y;
}

float Vector2::cross(const Vector2& rhs) const
{
	return x * rhs.y - y * rhs.x;
}

void Vector2::normalize()
{
	float len = length(); 
	if (len <= 0.0f) return;
	x /= len; 
	y /= len;
}
