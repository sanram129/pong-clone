/*
 * GameStates.cpp
 * This file contains all of the main game logic and rendering 
 * processes. Every state, or scene in the game is controlled
 * here. A single call in main is enough to run all of the code 
 * in this file. 
*/

#include "GameStates.h"

// Initialize current state to -1 (nothing)
int GameStates::currentState = -1;

// Initialize winning score to nothing
int GameStates::winningScore = -1;

GameStates::GameStates()
{
	// Default state set to menu if it was not already set
	this->currentState = MENU;
	this->winningScore = 11;
}

GameStates::GameStates(int currentState)
{
	// Set the current state to the defined one
	this->currentState = currentState;
}

int GameStates::getState()
{
	return this->currentState;
}

void GameStates::switchState(int state, int numOfPlayers, Ball* oldBall, GameTimer* oldTimer,
	Player* oldPlayer1, Player* oldPlayer2, AI_Paddle* ai)
{
	// Set the current state to the one provided
	this->currentState = state;

	// Switch through the states, calling the respective method
	switch (this->currentState)
	{
	case MENU:
		menuState();
		break;
	case SERVE:
		serveState(oldBall, numOfPlayers, oldTimer, oldPlayer1, oldPlayer2, ai);
		break;
	case GAME:
		playState(oldBall, numOfPlayers, oldTimer, oldPlayer1, oldPlayer2, ai);
		break;
	case FINALSCORE:
		gameOverState(oldPlayer1, oldPlayer2, ai);
		break;
	}
}

// Main menu state
void GameStates::menuState()
{
	// Set the render color to be a dark grey color
	setRenderColor(gameColors["Dark_Grey"], 255);

	// Clearing the screen will wash the screen with the current color
	SDL_RenderClear(mainRenderer);

	// User quit flag
	bool quitFlag = false;

	// Action flag for renderer
	bool action = false;

	// SDL event queue
	SDL_Event e;

	// Which option is selected (play by default)
	int selected = PVAI;

	// Instantiate the text used in the menu screen
	TextProperty title(SCREEN_WIDTH / 2, 126, 84, "Sanjay's Pong Clone", gameColors["White"]);
	TextProperty pvai(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 60, 60, "1 Player", gameColors["White"]);
	TextProperty pvp(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 150, 60, "2 Player", gameColors["White"]);
	TextProperty quit(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 240, 60, "Quit", gameColors["White"]);

	// Menu loop; run while the quit flag is false
	while (!quitFlag)
	{
		// Poll for events as long as they are in the queue
		while (SDL_PollEvent(&e) > 0)
		{
			// Check for a quit request
			if (e.type == SDL_QUIT)
			{
				quitFlag = true;
			}

			// Check to see what key is pressed down
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_DOWN:
				case SDLK_s:
					selected == QUIT ? selected = PVAI : selected++;
					break;
				case SDLK_UP:
				case SDLK_w:
					selected == PVAI ? selected = QUIT : selected--;
					break;
				case SDLK_RETURN:
					// Change action flag to true to get ready for game
					action = true;

					// Switch through possibilities
					switch (selected)
					{
					case PVAI:
					case PVP:
						// Switch to serve state
						this->switchState(SERVE, selected + 1);
						return;
					case QUIT:
						quitFlag = true;
						break;
					}
					break;
				default:
					break;
				}
			}
		}

		if (!action)
		{
			// Choose menu font color
			switch (selected)
			{
			case PVAI:
				pvai.setColor(gameColors["Green"]);
				pvp.setColor(gameColors["White"]);
				quit.setColor(gameColors["White"]);
				break;
			case PVP:
				pvai.setColor(gameColors["White"]);
				pvp.setColor(gameColors["Green"]);
				quit.setColor(gameColors["White"]);
				break;
			case QUIT:
				pvai.setColor(gameColors["White"]);
				pvp.setColor(gameColors["White"]);
				quit.setColor(gameColors["Green"]);
				break;
			}

			// Render the text
			title.renderText();
			pvai.renderText();
			pvp.renderText();
			quit.renderText();
		}

		// Update the renderer
		SDL_RenderPresent(mainRenderer);
	}

	// Close SDL and subsystems if quit is called
	closeSDL();
}

// Called when the ball is being served
void GameStates::serveState(Ball* oldBall, int numOfPlayers, GameTimer* oldTimer,
	Player* oldPlayer1, Player* oldPlayer2, AI_Paddle* ai)
{
	// Quit flag for main loop
	bool quitFlag = false;

	// Create an event queue
	SDL_Event e;

	// time for physics
	float deltaTime = 0.f;

	// Create a ball object if it doesn't already exist
	Ball* ball;
	if (oldBall == 0)
	{
		Ball newBall;
		ball = &newBall;
	}
	else
		ball = oldBall;

	// Reset the ball
	ball->reset();

	// Create a timer object if it doesn't already exist
	GameTimer* timer;
	if (oldTimer == NULL)
	{
		GameTimer newTimer;
		timer = &newTimer;
	}
	else
		timer = oldTimer;

	// Create first player (on left) if it doesn't exist
	Player* player1;
	if (oldPlayer1 == NULL)
	{
		// Create player
		Player temp(SDLK_w, SDLK_s, 32, SCREEN_HEIGHT / 2);
		player1 = &temp;
	}
	else
		player1 = oldPlayer1;

	// Create second (right) player or ai
	Player* player2 = NULL;
	AI_Paddle* ai2 = NULL;

	if (numOfPlayers == 2)
	{
		if (oldPlayer2 == NULL)
		{
			// New player
			Player temp(SDLK_UP, SDLK_DOWN,
				SCREEN_WIDTH - 32 - player1->getPaddleWidth(), SCREEN_HEIGHT / 2);
			player2 = &temp;
		}
		else
			player2 = oldPlayer2;
	}
	else
	{
		if (ai == NULL)
		{
			// Create new AI
			AI_Paddle temp(SCREEN_WIDTH - 32 - player1->getPaddleWidth(), SCREEN_HEIGHT / 2);
			ai2 = &temp;
		}
		else
		{
			ai2 = ai;
		}
	}

	// Stringstream for text
	std::stringstream serveText;
	serveText << "Player " << ball->getPlayerServe() << " serves!";

	// Text for who serves
	TextProperty whoServes(SCREEN_WIDTH / 2, 48, 48, serveText.str(), gameColors["White"]);

	// Helper text
	TextProperty pressEnter(SCREEN_WIDTH / 2, 90, 32, "Press enter to play!", gameColors["White"]);

	// Main loop
	while (!quitFlag) {

		// Read events in the queue
		while (SDL_PollEvent(&e) != 0) {
			// Check for quit
			if (e.type == SDL_QUIT)
			{
				quitFlag = true;
			}

			if (ball->onEvent(e))
			{
				// Switch state to play; ball has been served
				this->switchState(GAME, numOfPlayers, ball, timer, player1, player2, ai2);
				return;
			}
		}

		// Check the time since the last frame update 
		deltaTime = timer->Tick();

		// Move the ball with time-based movement
		ball->Move(deltaTime);

		// Set the render color to be a dark grey color
		setRenderColor(gameColors["Dark_Grey"], 255);

		// Make the background the currently set color
		SDL_RenderClear(mainRenderer);

		// Draw the net in the middle
		drawNet();

		// Render the title and helper text
		whoServes.renderText();
		pressEnter.renderText();

		// Render the ball over the net
		ball->Render();

		// Render players
		player1->Render();
		(numOfPlayers == 1) ? ai2->Render() : player2->Render();

		// Update the renderer
		SDL_RenderPresent(mainRenderer);
	}

	// Close SDL and subsystems if quit is called
	closeSDL();
}

void GameStates::playState(Ball* oldBall, int numOfPlayers, GameTimer* oldTimer, 
	Player* oldPlayer1, Player* oldPlayer2, AI_Paddle* ai)
{
	// Quit flag
	bool quitFlag = false;

	// Who scores
	int someoneScored = 0;

	// Event handler
	SDL_Event e;

	// Pointer to ball object
	Ball* ball = oldBall;

	// Pointer to timer
	GameTimer* timer = oldTimer;

	// Pointer to players
	Player* player1 = oldPlayer1;
	Player* player2 = oldPlayer2;
	AI_Paddle* ai2 = ai;

	// Bool representing if there is an ai
	bool isAI = (player2 == NULL) ? true : false;

	// Create player score objects
	TextProperty player1Score(SCREEN_WIDTH / 4, 96, 128, player1->getScore(), gameColors["Light_Grey"]);
	TextProperty player2Score(SCREEN_WIDTH / 4 * 3, 96, 128, isAI ? ai2->getScore() : player2->getScore(), gameColors["Light_Grey"]);
	
	// delta time for time-based physics
	float deltaTime = 0.f;

	// Game loop
	while (!quitFlag)
	{
		// Handle events
		if (SDL_PollEvent(&e) > 0)
		{
			// Handle quit
			if (e.type == SDL_QUIT)
			{
				quitFlag = true;
			}

			// Call the players' event handler
			player1->onEvent(e);
			if (isAI) {}
			else
				player2->onEvent(e);
		}

		// Move the computer boi
		if (isAI) 
			ai2->controller(ball);

		// Get the frame time for physics
		deltaTime = timer->Tick();

		// Move the ball to its new position
		ball->Move(deltaTime);

		// Move the players to their new positions
		player1->Move(deltaTime);
		(isAI) ? ai2->Move(deltaTime) : player2->Move(deltaTime);

		// Detect collision with both players
		ball->onCollision(player1);
		(isAI) ? ball->onCollision(ai2) : ball->onCollision(player2);

		// Detect the ball's collison with the wall
		ball->onWallCollision();

		// Get scores for checking
		int p1Score = player1->getIntScore();
		int p2Score = (isAI) ? ai2->getIntScore() : player2->getIntScore();

		// Deuce check
		if (p1Score == p2Score && p1Score + 1 == this->winningScore)
		{
			++this->winningScore;
		}

		// Check to see if someone scored and update text
		someoneScored = ball->isOffScreen();
		if (someoneScored) {
			if (someoneScored == 1)
			{
				player1->scored();
				player1Score.updateText(player1->getScore());
				ball->setServer(2);
				p1Score = player1->getIntScore();
			}
			else if (someoneScored == 2)
			{
				(isAI) ? ai2->scored() : player2->scored();
				player2Score.updateText((isAI) ? ai2->getScore() : player2->getScore());
				ball->setServer(1);
				p2Score = (isAI) ? ai2-> getIntScore() : player2->getIntScore();
			}

			// Win condition check (winner will be calculated in the final state)
			if (p1Score == this->winningScore
				|| p2Score == this->winningScore)
			{
				this->switchState(FINALSCORE, 0, NULL, NULL, player1, player2, ai2);
				return;
			}
			// No win? continue
			else {
				// Reset player positions
				player1->reset();
				(isAI) ? ai2->reset() : player2->reset();

				// Switch states to serve and return after
				this->switchState(SERVE, numOfPlayers, ball, timer, player1, player2, ai2);
				return;
			}
		}

		// Clear the screen
		setRenderColor(gameColors["Dark_Grey"], 255);
		SDL_RenderClear(mainRenderer);

		// Draw the net in the middle
		drawNet();

		// Render score
		player1Score.renderText();
		player2Score.renderText();

		// Render the ball
		ball->Render();

		// Render players
		player1->Render();
		(isAI) ? ai2->Render() : player2->Render();

		// Render everything
		SDL_RenderPresent(mainRenderer);
	}

	// Close SDL on quit
	closeSDL();
}

void GameStates::gameOverState(Player* player1, Player* player2, AI_Paddle* ai)
{
	// Quit flag
	bool quitFlag = false;

	// Event checker for the quit call
	SDL_Event e;

	// AI check
	int p2score;
	if (player2 == NULL)
	{
		p2score = ai->getIntScore();
	}
	else
	{
		p2score = player2->getIntScore();
	}

	// Figure out the winner
	int winner = (player1->getIntScore() > p2score) ? 1 : 2;

	// Compute text
	std::stringstream winText;
	winText << "Player " << winner << " wins!";

	// Text for the game over screen
	TextProperty winnerText(SCREEN_WIDTH / 2, 100, 120, winText.str(), gameColors["White"]);
	TextProperty finalScore(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 84,
		player1->getScore() + " - " + std::to_string(p2score), gameColors["White"]);

	// Quit button
	TextProperty pressEnter(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 4 * 3, 60, "Press Enter to quit", gameColors["Green"]);

	// Loop
	while (!quitFlag)
	{
		// Run through queue
		if (SDL_PollEvent(&e) > 0)
		{
			// Check for quit
			if (e.type == SDL_QUIT)
			{
				quitFlag = true;
			}

			// Check for enter (quit)
			if (e.type == SDL_KEYDOWN)
			{
				if (e.key.keysym.sym == SDLK_RETURN)
				{
					quitFlag = true;
				}
			}
		}

		// Clear screen
		setRenderColor(gameColors["Dark_Grey"], 255);
		SDL_RenderClear(mainRenderer);

		// Render text
		winnerText.renderText();
		finalScore.renderText();
		pressEnter.renderText();

		// Update screen
		SDL_RenderPresent(mainRenderer);
	}

	// Close SDL on quit (called also in main, this is just a failsafe)
	closeSDL();
}