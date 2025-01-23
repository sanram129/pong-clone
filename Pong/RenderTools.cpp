#include "RenderTools.h"

// Initialize SDL and its subsystems
bool init()
{
	// Check to make sure SDL is initialized correctly
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "Video not initialized! Error: " << SDL_GetError() << std::endl;
		return false;
	}
	else
	{
		// Initialize TTF properly
		if (TTF_Init() < 0)
		{
			std::cout << "TTF not initialized properly! Error: " << TTF_GetError() << std::endl;
			return false;
		}

		// If initialized correctly, create the window
		mainWindow = SDL_CreateWindow("Sanjay's Pong Clone", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

		// Make sure the window was created successfully
		if (mainWindow == NULL)
		{
			std::cout << "Window not created! Error: " << SDL_GetError() << std::endl;
			return false;
		}
		else
		{
			// Create the renderer
			mainRenderer = SDL_CreateRenderer(mainWindow, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
			if (mainRenderer == NULL)
			{
				std::cout << "Renderer not created! Error: " << SDL_GetError() << std::endl;
				return false;
			}
			else
			{
				return true;
			}
		}
	}
}

// Open the font used in the game
bool openFont(int size)
{
	mainFont = TTF_OpenFont("res/fonts/Silkscreen-Regular.ttf", size);
	if (mainFont == NULL)
	{
		std::cout << "Font not loaded! Error: " << SDL_GetError() << std::endl;
		return false;
	}

	return true;
}

// Set the render color using the array
void setRenderColor(SDL_Color color, int alpha)
{
	SDL_SetRenderDrawColor(mainRenderer, color.r, color.g, color.b, alpha);
}

// Draw the net in the middle of the screen
void drawNet()
{
	// Set render color to white
	setRenderColor(gameColors["Light_Grey"], 255);

	// Initial rect for drawing dashes (they will be 24 x 60 px)
	SDL_Rect netRect = { SCREEN_WIDTH / 2 - NET_WIDTH, NET_HEIGHT / 2, NET_WIDTH, NET_HEIGHT };

	// Draw the dashes down the middle of the field
	for (int i = 0; i < (SCREEN_WIDTH / NET_HEIGHT * 2); i++)
	{
		SDL_RenderFillRect(mainRenderer, &netRect);
		netRect.y = i * NET_HEIGHT * 2 + NET_HEIGHT / 2;
	}
}

// Quit all SDL subsystems
void closeSDL()
{
	// Close window
	SDL_DestroyWindow(mainWindow);
	mainWindow = NULL;

	// Close renderer
	SDL_DestroyRenderer(mainRenderer);
	mainRenderer = NULL;

	// Close font
	TTF_CloseFont(mainFont);
	mainFont = NULL;

	// Quit SDL and TTF
	SDL_Quit();
	TTF_Quit();
}