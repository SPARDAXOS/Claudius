#pragma once

struct Rectangle
{
	int x{}; 
	int y{};
	int w{}; 
	int h{};

	Rectangle();
	Rectangle(const Rectangle& rhs);
	Rectangle(int x, int y, int w, int h);

	void SetBounds(int x, int y, int w, int h);
};