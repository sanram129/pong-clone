#include "GameStates.h"

int main(int argc, char* argv[])
{
	// Initialize SDL
	if (init())
	{
		// Create state machine
		GameStates stateMachine;
		// Set the current state to the main menu
		stateMachine.switchState(MENU);
	}

	// Close SDL and subsystems if quit is called
	closeSDL();

	return 0;
}