/* AI_Paddle.h
 * Simply an AI-controlled paddle activated if the user chooses
 * the single player game mode. 
 */
#pragma once

#include "Paddle.h"
#include "Ball.h"

class AI_Paddle : public Paddle
{
public:
	// AI constructor
	AI_Paddle(int locX1, int locY1);

	// AI controller based on ball position
	void controller(Ball* ball);
};

