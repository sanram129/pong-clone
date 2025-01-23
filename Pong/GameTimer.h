#pragma once

#include <iostream>
#include <SDL.h>

class GameTimer
{
public:
	GameTimer();

	// Get the ticks (for deltatime)
	uint64_t Tick();

private:
	// The amount of time between this frame render and the last
	uint64_t frameTime;

	// Time representing the last tick
	uint64_t lastTick;
};

