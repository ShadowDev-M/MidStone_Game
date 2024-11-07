#include "UiText.h"

void UiText::Render()
{
	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(font, "put your text here", fontColor);

	// convert it into a texture
	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Rect Message_rect; //create a rect
	Message_rect.x = screenCoords.x;  //controls the rect's x coordinate 
	Message_rect.y = screenCoords.y; // controls the rect's y coordinte
	Message_rect.w = width; // controls the width of the rect
	Message_rect.h = height; // controls the height of the rect

	// you put the renderer's name first, the Message,
	// the crop size (you can ignore this if you don't want
	// to dabble with cropping), and the rect which is the size
	// and coordinate of your texture
	SDL_RenderCopy(renderer, Message, NULL, &Message_rect);

	SDL_FreeSurface(surfaceMessage);
	SDL_DestroyTexture(Message);
}
