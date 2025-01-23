#pragma once


#include <sstream>
#include <SDL.h>

#include "Variables.h"
#include "RenderTools.h"
#include "TextProperty.h"
#include "Ball.h"
#include "GameTimer.h"
#include "Player.h"
#include "AI_Paddle.h"

class GameStates
{
public:
	// Constructors
	GameStates();
	GameStates(int currentState);

	// Destructor
	virtual ~GameStates() = default;

	// Method for switching to the correct state in currentState (a setter)
	void switchState(int state, int numOfPlayers = 0, Ball* oldBall = NULL, GameTimer* oldTimer = NULL, 
		Player* oldPlayer1 = NULL, Player* oldPlayer2 = NULL, AI_Paddle* ai = NULL);

	// Get the current state
	int getState();

	/* Below are the prototypes for the game states. When the switchState()
	 * method is called, the state will switch to the corresponding
	 * one in the enum. */
	void menuState();
	void serveState(Ball* oldBall, int numOfPlayers, GameTimer* oldTimer, Player* oldPlayer1,
		Player* oldPlayer2 = NULL, AI_Paddle* ai = NULL);
	void playState(Ball* oldBall, int numOfPlayers, GameTimer* timer, Player* oldPlayer1, 
		Player* oldPlayer2 = NULL, AI_Paddle* ai = NULL);
	void gameOverState(Player* player1, Player* player2 = NULL, AI_Paddle* ai = NULL);

private:
	// Represents the current state (based on enum)
	static int currentState;

	// Score needed to win; can increase with deuces
	static int winningScore;
};

