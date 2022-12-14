#include "Game.h"
#include <iostream>



int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	try {
		Game SnakeGame;
		SnakeGame.Run();
	}
	catch (const std::exception& exception) {
		std::cout << exception.what() << std::endl;
		return 1;
	}

	return 0;
}
