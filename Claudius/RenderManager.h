#pragma once

#include <vector>

struct Sprite;
struct Transform;
struct Rectangle;
struct Color;

struct RenderManager
{
	struct SpriteEntry
	{
		const Sprite& sprite;
		const Transform& trans;
	};

	struct RectEntry
	{
		const Rectangle& rect;
		const Color& color;
		const Transform& trans;
	};


	void Render(const Sprite& sprite, const Transform& trans);
	void Render(const Rectangle& rect, const Color& color, const Transform& trans);
	void Clear();

	std::vector<SpriteEntry> spriteEntries;
	std::vector<RectEntry> rectEntries;
};
