#pragma once
#include <MMath.h>
#include "SDL.h"

using namespace MATH;

class  UiElement
{
public:
	
	virtual void Render() = 0;


protected:

	Vec2 screenCoords;
	//float scale;
	SDL_Renderer* renderer;
	//SDL_Texture* texture;
	
private:

	


};

