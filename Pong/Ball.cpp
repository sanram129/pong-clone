#include "Ball.h"

Ball::Ball()
{
	// Reset the ball
	this->reset();

	// Set starting ball speed
	this->ballSpeed = 0.75f;

	// Initialize random seed and which player serves
	srand(time(NULL));
	playerServe = rand() % 2 + 1; // Random between 1 and 2
}

bool Ball::onEvent(SDL_Event& e)
{
	// Check if a key was pushed
	// Repeat to check presses only once
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		// Serve the ball if enter was pressed
		if (e.key.keysym.sym == SDLK_RETURN)
		{
			// Check which player serves
			if (playerServe == 1)
			{
				// Increase the x velocity (go right) and slow down on serve
				this->velX += this->ballSpeed;
			}
			else if (playerServe == 2)
			{
				// Decrease the x velocity (go left)
				this->velX -= this->ballSpeed;
			}

			// Have a random serve angle for variation in both directions
			this->velY = (float)((rand() % MAX_ANGLE * 2) - MAX_ANGLE) / 100.f;

			// Return true to show that the ball has been served
			return true;
		}
	}

	// Return false; ball has not been served this frame
	return false;
}

void Ball::Move(float deltaTime)
{
	// Change the position based on the velocity
	this->locY += this->velY * deltaTime;
	this->locX += this->velX * deltaTime;

	// Update the ball rect
	updateRect();
}

void Ball::Render()
{
	setRenderColor(gameColors["White"], 255);
	SDL_RenderFillRect(mainRenderer, &this->rect);
}

void Ball::updateRect()
{
	// Cast the types to int to render properly
	this->rect = { (int)locX, (int)locY, BALL_DIAMETER, BALL_DIAMETER };
}

int Ball::getPlayerServe()
{
	return this->playerServe;
}

void Ball::setServer(int server)
{
	this->playerServe = server;
}

void Ball::onCollision(Paddle* paddle)
{
	// Get the X position of the player
	int playerX = paddle->getPaddleX();
	int playerY = paddle->getPaddleY();

	// Get paddle dimensions
	int paddleW = paddle->getPaddleWidth();
	int paddleH = paddle->getPaddleHeight();

	// Check collision laterally
	if (playerX + paddleW < this->locX || this->locX + BALL_DIAMETER < playerX)
		return;

	// Check collision vertically
	if (playerY + paddleH < this->locY || this->locY + BALL_DIAMETER < playerY)
		return;

	/* Reverse X velocity, but only if the ball is travelling
	towards the paddle in order to reduce glitches */
	if ((playerX > SCREEN_WIDTH / 2 && this->velX > 0)
		|| playerX < SCREEN_WIDTH / 2 && this->velX < 0)
	{
		// Invert X velocity and increase by a small constant amount
		this->velX = -this->velX;
		this->velX += (this->velX < 0) ? -this->ballIncrease : this->ballIncrease;

		// Change y velocity by a small random amount
		this->velY = this->velY + (float)((rand() % MAX_VARIATION * 2) - MAX_VARIATION) / 100.f;
	}
}

void Ball::onWallCollision()
{
	/* Simply check if the top edge of the ball is higher than
	the top edge of the screen, and the same for the bottom */
	if (this->locY < 0 && this->velY < 0 
		|| this->locY + BALL_DIAMETER > SCREEN_HEIGHT && this->velY > 0)
	{
		// Invert y velocity
		this->velY = -this->velY;
	}
}

int Ball::isOffScreen()
{
	// Check which side it goes off on and who scores
	if (this->locX > SCREEN_WIDTH)
		return 1;
	else if (this->locX + BALL_DIAMETER < 0)
		return 2;
	else
		return 0;
}

void Ball::reset()
{
	// Set the location of the ball to the centre of the screen
	this->locX = SCREEN_WIDTH / 2 - BALL_DIAMETER / 2;
	this->locY = SCREEN_HEIGHT / 2 - BALL_DIAMETER / 2;
	this->velX = 0;
	this->velY = 0;

	// Set ball increase speed
	this->ballIncrease = 0.03f;

	// Update the rect
	updateRect();
}

float Ball::getLocY()
{
	return this->locY;
}

float Ball::getLocX()
{
	return this->locX;
}

float Ball::getVelY()
{
	return this->velY;
}