#pragma once
#include "Utility.h"

using Color = Utility::Color;
using Size = Utility::Size;

static constexpr const Color AppleColor{ 255, 0, 0, 255 };
static constexpr const Color SnakeHeadColor{ 0, 255, 0, 255 };
static constexpr const Color SnakeBodyColor{ 0, 255, 0, 255 };

static constexpr const int SnakeMovementSpeed = 15;

static constexpr const Size EntitySize{ 10, 10 };