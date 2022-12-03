#pragma once

#include <string>
#include <vector>
#include "KeyCode.h"
#include "Apple.h"
#include "Player.h"

struct RenderManager;
struct ResourceManager;

class Game
{
	Player playerOne;
	Apple apple;

	ResourceManager& m_resourceManager;

public:
	//Teemu Code Begin.

	// float timer; <- can be used in delta time
	// float updateInterval; <- check Game.h

	int width;
	int height;

	Game(ResourceManager& resourceManager);
	~Game();
	bool Enter(int& width, int& height, std::string& title);
	void Update(double dt);
	void Render(RenderManager& rendererManager);
	void OnKeyDown(KeyCode key);
	void OnKeyUp(KeyCode key);
};