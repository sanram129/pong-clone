/* Player.h
 * This class only includes the event handler and other things
 * exclusive to the player-controlled paddles. Everything else
 * is inherited from the Paddle class.
 */

#pragma once
#include "Paddle.h"
class Player : public Paddle
{
public:
	// Player constructor
	Player(int up, int down, int locX1, int locY1);

	// Handle events
	void onEvent(SDL_Event& e);

private:
	// Choose which buttons are used for control
	int upButton, downButton;
};

