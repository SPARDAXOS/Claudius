#pragma once
#include "Utility.h"

using Color = Utility::Color;
using Size = Utility::Size;

constexpr const Color AppleColor{ 255, 0, 0, 255 };
constexpr const Color SnakeHeadColor{ 0, 255, 0, 255 };
constexpr const Color SnakeBodyColor{ 0, 255, 0, 255 };

constexpr const int SnakeMovementSpeed = 15;

constexpr const Size EntitySize{ 10, 10 };