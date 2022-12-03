#pragma once

struct Vector2
{
	float x {}; 
	float y {};

	Vector2();
	Vector2(const Vector2& rhs);
	Vector2(const float x, const float y);

	Vector2& operator=(const Vector2& rhs);				 
	Vector2 operator+(const Vector2& rhs) const;		 
	Vector2 operator-(const Vector2& rhs) const;		 
	Vector2 operator*(const Vector2& rhs) const;	
	Vector2 operator/(const Vector2& rhs) const;
	Vector2 operator*(const float rhs) const;			 
	Vector2 operator/(const float rhs) const;		

	bool operator==(const Vector2& rhs) const;

	Vector2 perpendicular() const;
	Vector2 unit() const;

	float length() const;
	float length_squared() const;
	float dot(const Vector2& rhs) const;
	float cross(const Vector2& rhs) const;
	void normalize();

};