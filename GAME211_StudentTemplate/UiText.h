#pragma once
#include "UiElement.h"
#include "SDL.h"
#include "MMATH.h"
#include <SDL_ttf.h>


using namespace MATH;

class UiText: public UiElement
{
public:
	UiText(SDL_Renderer* renderer, Vec2 _screenCoord, TTF_Font* font ): UiElement(renderer,_screenCoord)
	{

	}


private:


};

