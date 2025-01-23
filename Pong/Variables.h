// This file contains all of the main variables used throughout the game.

#pragma once
#include <unordered_map>
#include "RenderTools.h"

// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

// Gap between each dash representing the net
const int NET_HEIGHT = 18;

// Width of each dash
const int NET_WIDTH = 6;

// Menu options
enum menuOptions
{
	PVAI,
	PVP,
	QUIT
};

// Enum representing the states
enum states
{
	MENU,
	SERVE,
	GAME,
	FINALSCORE
};

// Main window
extern SDL_Window* mainWindow;

// Renderer, used to draw the geometry
extern SDL_Renderer* mainRenderer;

// Font used in game
extern TTF_Font* mainFont;

// Unordered map with colors
extern std::unordered_map<std::string, SDL_Color> gameColors;