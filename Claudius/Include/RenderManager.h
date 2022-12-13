#pragma once

#include <vector>

struct Transform;
struct Rectangle;
struct Color;

class RenderManager
{
public:
	struct RectEntry
	{
		const Rectangle& rect;
		const Color& color;
		const Transform& trans;
	};

	void Render(const Rectangle& rect, const Color& color, const Transform& trans);
	void Clear();

	std::vector<RectEntry> rectEntries;
};
