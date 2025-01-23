#include "Paddle.h"

Paddle::Paddle(int locX, int locY)
{
	// Initialize values
	this->score = 0;
	this->velY = 0.f;
	this->locX= (float)locX;
	this->locY = (float)locY;
	this->initlocX = this->locX;
	this->initlocY = this->locY;

	// Initialize the rect
	updateRect();
}

void Paddle::updateRect()
{
	this->rect = { (int)this->locX, (int)this->locY, PADDLE_WIDTH, PADDLE_HEIGHT };
}

void Paddle::Move(float deltaTime)
{
	// Transfer velocity to location while ensuring they stay on screen
	this->locY = (this->velY <= 0) ? 
		std::max(this->locY + this->velY * deltaTime, 0.f)
		: std::min(this->locY + this->velY * deltaTime, (float)SCREEN_HEIGHT - PADDLE_HEIGHT);

	// Update the rect
	updateRect();
}

void Paddle::Render()
{
	setRenderColor(gameColors["White"], 255);
	SDL_RenderFillRect(mainRenderer, &this->rect);
}

int Paddle::getPaddleX()
{
	return this->locX;
}

int Paddle::getPaddleY()
{
	return this->locY;
}

int Paddle::getPaddleWidth()
{
	return this->PADDLE_WIDTH;
}

int Paddle::getPaddleHeight()
{
	return this->PADDLE_HEIGHT;
}

void Paddle::setPaddleY(int pos)
{
	this->locY = pos;
}

std::string Paddle::getScore()
{
	std::stringstream temp;
	temp << this->score;
	return temp.str();
}

int Paddle::getIntScore()
{
	return this->score;
}

void Paddle::scored()
{
	this->score++;
}

void Paddle::reset()
{
	// Reset positions, velocity and rect
	this->locX = this->initlocX;
	this->locY = this->initlocY;

	this->velY = 0.f;

	updateRect();
}