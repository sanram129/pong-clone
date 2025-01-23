// A simple class used to hold text.

#pragma once

#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "RenderTools.h"

class TextProperty
{
public:
	// Set properties of the text
	TextProperty(int xpos, int ypos, int size, std::string text, SDL_Color color);
	virtual ~TextProperty() = default;

	// Render the processed text to the screen
	bool renderText();

	// Change the color of the text
	void setColor(SDL_Color color);

	// Change the text
	void updateText(std::string newText);

private:
	int xpos, ypos, size;
	std::string text;
	SDL_Color color;
};

