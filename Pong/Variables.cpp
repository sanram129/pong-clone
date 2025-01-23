#include "Variables.h"

TTF_Font* mainFont = NULL;
SDL_Renderer* mainRenderer = NULL;
SDL_Window* mainWindow = NULL;

std::unordered_map<std::string, SDL_Color> gameColors =
{
	// Assign color values to the umap
	{"White", { 255, 255, 255 }},
	{"Green", {0, 255, 48}},
	{"Dark_Grey", {32, 32, 32}},
	{"Light_Grey", { 176, 176, 176 }},
};