#include "TextProperty.h"

TextProperty::TextProperty(int xpos, int ypos, int size, std::string text, SDL_Color color)
{
	this->xpos = xpos;
	this->ypos = ypos;
	this->size = size;
	this->text = text;
	this->color = color;
}

bool TextProperty::renderText()
{
	// Close old font
	TTF_CloseFont(mainFont);

	// Open a font with the given size
	openFont(this->size);

	// Create a text surface that can be rendered
	SDL_Surface* textSurface = TTF_RenderText_Solid(mainFont, this->text.c_str(), this->color);

	// Create a texture for the image to be stored on
	SDL_Texture* tempText = NULL;

	if (textSurface == NULL)

	{
		std::cout << "Text rendering error: " << TTF_GetError() << std::endl;
		return false;
	}
	else
	{
		// Create a texture from the surface
		tempText = SDL_CreateTextureFromSurface(mainRenderer, textSurface);
		if (tempText == NULL)
		{
			std::cout << "Texture creation failed! Error: " << TTF_GetError() << std::endl;
			return false;
		}
		else
		{
			// Position is based on the centre of the text
			SDL_Rect dimensions = { this->xpos - textSurface->w / 2, this->ypos - textSurface->h / 2, textSurface->w, textSurface->h };

			// Actually render the surface
			SDL_RenderCopy(mainRenderer, tempText, NULL, &dimensions);

			// Destroy texture used
			SDL_DestroyTexture(tempText);
			tempText = NULL;

			// Destroy surface used
			SDL_FreeSurface(textSurface);
			textSurface = NULL;

			return true;
		}
	}
}

void TextProperty::setColor(SDL_Color color)
{
	this->color = color;
}

void TextProperty::updateText(std::string newText)
{
	this->text = newText;
}