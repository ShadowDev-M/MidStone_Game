#pragma once
#include "UiElement.h"
#include "SDL.h"
#include "MMATH.h"
#include <SDL_ttf.h>
#include <string>


using namespace MATH;

class UiText : public UiElement
{
public:
	UiText();

	void OnCreate(SDL_Renderer* _renderer, Vec2 _screenCoord, const char* _fontPath , SDL_Color _color, float _fontSize, float _height ,float _width ,const char* _message)
	{
		renderer = _renderer;
		screenCoords = _screenCoord;
		fontColor=_color;
		message = _message;
		fontSize=_fontSize;
		fontPath = _fontPath;
		width=_width;
		height = _height;
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

	void Render() override;

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

		if (font == nullptr) {
			std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
			return;
		}
	}

};

