#include "GameTimer.h"

GameTimer::GameTimer()
{
	this->lastTick = SDL_GetTicks64();
	this->frameTime = 0;
}

// Return the difference in time since the last frame
uint64_t GameTimer::Tick()
{
	this->frameTime = SDL_GetTicks64() - this->lastTick;
	this->lastTick = SDL_GetTicks64();
	return frameTime;
}