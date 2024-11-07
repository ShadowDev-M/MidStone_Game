#pragma once
#include "UiElement.h"
#include "SDL.h"
#include "MMATH.h"
#include <SDL_ttf.h>


using namespace MATH;

class UiText: public UiElement
{
public:
	UiText(SDL_Renderer* renderer, Vec2 _screenCoord, const char* _fontPath , SDL_Color _color, float _fontSize, float _width ,float _height ,const char* _message): 
		UiElement(renderer,_screenCoord) ,
		fontColor(_color), 
		message(_message),
		fontSize(_fontSize), 
		fontPath(_fontPath),
		width(_width),
		height(_height)
	{
		OpenFont();
		
	}

	UiText& ChangeMessage(const char* _message)
	{
		message = _message;
		return *this;
	}

	UiText& ChangeColor(SDL_Color _color)
	{
		fontColor = _color;
		return *this;
	}
	
	UiText& ChangeFont(const char* _fontPath)
	{
		fontPath = _fontPath;
		OpenFont();
		return *this;
	}
	
	UiText& ChangeSize(float _fontSize)
	{
		fontSize = _fontSize;
		OpenFont();
		return *this;
	}

	void Render();

protected:

private:

	SDL_Color fontColor;
	TTF_Font* font;
	const char* message;
	const char* fontPath;
	float fontSize = 1;
	float width;
	float height;

	void OpenFont()
	{
		if (!fontPath)
		{
			std::cout << "Font Path Not Found";
		 	return;
		}
		
		font = TTF_OpenFont(fontPath, fontSize);
	}

};

