#include "Player.h"

Player::Player(int up, int down, int locX1, int locY1) 
	: Paddle(locX1, locY1)
{
	this->upButton = up;
	this->downButton = down;
}

void Player::onEvent(SDL_Event& e)
{
	// Check for the first keydown event of its type
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// Check for up press
		if (e.key.keysym.sym == this->upButton)
			this->velY -= PADDLE_SPEED;
		// Down press
		else if (e.key.keysym.sym == this->downButton)
			this->velY += PADDLE_SPEED;
	}

	// Reset the velocities if button is released
	if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		// Up release
		if (e.key.keysym.sym == this->upButton)
			this->velY += PADDLE_SPEED;
		else if (e.key.keysym.sym == this->downButton)
			this->velY -= PADDLE_SPEED;
	}
}