#pragma once
#include "UiElement.h"
#include "SDL.h"
#include "SDL_image.h"
#include <functional>
#include <vector>

class UiPanel : UiElement
{

public:
	UiPanel();
	using ButtonCallback = std::function<void()>;

	void OnCreate(SDL_Renderer* _renderer, Vec2 _screenCoord, const char* _backgroundImage, float _scale)
	{

		renderer = _renderer;
		screenCoords = _screenCoord;
		PanelImage = _backgroundImage;
		panelScale = _scale;
		PanelTexture = loadImage(PanelImage);
		hasIcon = false;
		SDL_QueryTexture(PanelTexture, nullptr, nullptr, &panelWidth, &panelHeight);
		panelHeight *= panelScale;
		panelWidth *= panelScale;
	}

	UiPanel& AddIcon(const char* _panelImage, float _scale)
	{
		IconTexture = loadImage(_panelImage);
		SDL_QueryTexture(PanelTexture, nullptr, nullptr, &iconWidth, &iconHeight);
		hasIcon = true;
		IconScale = _scale;
		iconWidth *= IconScale;
		iconHeight *= IconScale;
		return *this;
	}

	UiPanel& AddIconVec2(const char* _panelImage, float _scale, Vec2 _screenCoord)
	{
		IconTexture = loadImage(_panelImage);
		screenCoords = _screenCoord;
		SDL_QueryTexture(PanelTexture, nullptr, nullptr, &iconWidth, &iconHeight);
		hasIcon = true;
		IconScale = _scale;
		iconWidth *= IconScale;
		iconHeight *= IconScale;
		return *this;
	}

	void ClearIcons();

	UiPanel& AddButton(ButtonCallback func)
	{
		onClick = func;
		return *this;
	}

	void HandleEvent(const SDL_Event& event);

	void Render() override;

private:
	//Panel Properties
	const char* PanelImage;
	SDL_Texture* PanelTexture;
	float panelScale;
	int panelWidth, panelHeight;

	//Icon Properties 
	const char* IconImage;
	SDL_Texture* IconTexture;
	float IconScale;
	int iconWidth, iconHeight;
	bool hasIcon;

	//Button
	ButtonCallback onClick;

	//Functions
	SDL_Texture* loadImage(const char* textureFile);
};

