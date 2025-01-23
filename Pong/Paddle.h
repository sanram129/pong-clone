/* Paddle.h
 * This class simply defines functionality for a paddle, such as 
 * the SDL_Rect, the score, the position, the velocity, etc.
 * For control, it can be extended by an AI class or by a 
 * Player class.
 */

#pragma once

#include <SDL.h>
#include <sstream>
#include "RenderTools.h"
#include "Variables.h"

class Paddle
{
public:
	// Constructor
	Paddle(int locX, int locY);

	// Destructor
	virtual ~Paddle() = default;

	// Paddle width
	static const int PADDLE_WIDTH = 12;

	// Paddle height
	static const int PADDLE_HEIGHT = 72;

	// Paddle speed constant
	static const int PADDLE_SPEED = 1;

	// Update the rect
	void updateRect();

	// Move functionality
	void Move(float deltaTime);

	// Render the paddle
	void Render();

	// Get the x position of the paddle
	int getPaddleX();

	// Get ypos of paddle
	int getPaddleY();

	// Get paddle width
	int getPaddleWidth();

	// Get paddle height
	int getPaddleHeight();

	// Set y pos of paddle
	void setPaddleY(int pos);

	// Get the score for rendering
	std::string getScore();
	int getIntScore();

	// Increase the score
	void scored();

	// Reset positions
	void reset();

protected:
	// Location on the x and y axes
	float locX, locY;

	// Initial location for reset
	float initlocX, initlocY;

	// Velocity on the y axis
	float velY;

	// The rect representing the visible paddle
	SDL_Rect rect;

	// An int representing the score
	int score;
};

