#include "AI_Paddle.h"

AI_Paddle::AI_Paddle(int locX1, int locY1) : Paddle(locX1, locY1) {}

void AI_Paddle::controller(Ball* ball)
{
	/* Goal of this function is to get the paddle
	to move towards the ball while making the game fair */
	float ballY = ball->getLocY();
	float ballX = ball->getLocX();

	if (ballX > SCREEN_WIDTH / 3)
	{
		// Within > 1.5 paddles (move faster)
		if (!(ballY >= this->locY - PADDLE_HEIGHT / 2.f && ballY < this->locY + PADDLE_HEIGHT * 1.5f)) {
			if (this->locY > ballY)
				this->velY = -PADDLE_SPEED;
			else if (this->locY < ballY)
				this->velY = PADDLE_SPEED;
		}

		// Within the paddle (move slower)
		else if (!(ballY >= this->locY + PADDLE_HEIGHT && ballY < this->locY + PADDLE_HEIGHT)) {
			if (this->locY > ballY)
				this->velY = -PADDLE_SPEED / 2.f;
			else if (this->locY < ballY)
				this->velY = PADDLE_SPEED / 2.f;
		}
		else
		{
			this->velY = 0;
		}
	}
	else
	{
		this->velY = 0;
	}
}