#pragma once
#include <MMath.h>
#include "SDL.h"

using namespace MATH;

class UiElement
{
public:
	UiElement(SDL_Renderer* _renderer, Vec2 _screenCoords): 
		renderer(_renderer),
		screenCoords(_screenCoords)
		//scale(_scale), 
		//texture(_texture)
	{
				
	}

private:

	Vec2 screenCoords;
	//float scale;
	SDL_Renderer* renderer;
	//SDL_Texture* texture;
	
	void Render(SDL_Texture* texture);


};

