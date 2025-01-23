#pragma once

#include <time.h>
#include <SDL.h>
#include <iostream>
#include "Variables.h"
#include "Player.h"

class Ball
{
public:
	// Constructor
	Ball();

	// Destructor
	virtual ~Ball() = default;

	// Diameter of the ball
	static const int BALL_DIAMETER = 12;

	// Max angle of the ball on serve in degrees
	static const int MAX_ANGLE = 35;

	// Random angle of variation on collision
	static const int MAX_VARIATION = 20;

	// Rect representing the actual dot
	SDL_Rect rect;

	// Command to make the ball move
	void Move(float deltaTime);

	// Render ball
	void Render();

	// Simply update the rect
	void updateRect();

	// Event handler for the ball
	bool onEvent(SDL_Event& e);

	// Get which player serves
	int getPlayerServe();

	// Set the server
	void setServer(int server);

	// Collision detection with player or ai
	void onCollision(Paddle* paddle);

	// Collision detection with top and bottom edges
	void onWallCollision();

	// Check if the ball goes off screen (score)
	int isOffScreen();

	// Reset the ball
	void reset();

	// Get Y location of ball
	float getLocY();

	// Get X location of ball
	float getLocX();

	// Get y vel
	float getVelY();

private:
	// Ball location
	float locX, locY;

	// Ball velocity
	float velX, velY;

	// Which player serves
	int playerServe;

	// Speed of the ball
	float ballSpeed;

	// Speed increase on contant
	float ballIncrease;
};

