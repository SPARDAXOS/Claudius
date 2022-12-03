#pragma once

struct Color
{
	unsigned char r, g, b, a;

	Color();
	Color(const Color& rhs);
	Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a);

	void SetColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
};