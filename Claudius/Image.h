#pragma once

struct Image
{
	Image();
	Image(const Image& rhs);
	Image(unsigned int id, int width, int height);

	unsigned int id;
	int width;
	int height;

	unsigned int GetID();
	int GetWidth();
	int GetHeight();
};