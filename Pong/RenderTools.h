/*
 * RenderTools.h
 * This file provides all of the functions used to assist in rendering.
 * This includes the rendering of fonts, the initialization and closure 
 * of SDL and the creation of a playing field. 
 */

#pragma once

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

#include "Variables.h"

// Function definitions
bool init();
bool openFont(int size);
void setRenderColor(SDL_Color color, int alpha);
void drawNet();
void closeSDL();