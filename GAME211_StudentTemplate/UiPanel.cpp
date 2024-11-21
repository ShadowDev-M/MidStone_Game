#include "UiPanel.h"

UiPanel::UiPanel()
{

}

void UiPanel::HandleEvent(const SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        int x, y;
        SDL_GetMouseState(&x, &y);

        // Check if the mouse is within the button bounds
        if (x >= screenCoords.x && x <= screenCoords.x + panelWidth &&
            y >= screenCoords.y && y <= screenCoords.y + panelHeight) {
            // Call the callback function

            if (onClick) {
                onClick();
            }
        }
    }
}

void UiPanel::Render()
{

    SDL_Rect panelDest = { screenCoords.x, screenCoords.y, panelWidth , panelHeight };
    SDL_RenderCopy(renderer, PanelTexture, nullptr, &panelDest);

    if (hasIcon)
    {
        Vec2 iconCoord;
        iconCoord.x = screenCoords.x + (panelWidth - iconWidth) / 2;
        iconCoord.y = screenCoords.y + (panelHeight - iconHeight) / 2;


        SDL_Rect iconDest = { iconCoord.x, iconCoord.y, iconWidth, iconHeight };
        SDL_RenderCopy(renderer, IconTexture, nullptr, &iconDest);

    }

}
void UiPanel::ClearIcons() { // Reset the state that an icon exists, but not available (just thanos snap it tbh)
    hasIcon = false;
    IconTexture = nullptr;
    iconWidth = iconHeight = 0;
}

SDL_Texture* UiPanel::loadImage(const char* textureFile)
{


    // The final texture
    SDL_Texture* newTexture = nullptr;

    // Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(textureFile);
    if (!loadedSurface)
    {
        std::cout << "Unable to load image " << textureFile <<
            "! SDL_image Error: " << IMG_GetError() << std::endl;
    }
    else
    {
        // Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (!newTexture)
        {
            std::cout << "Unable to create texture " << textureFile <<
                "! SDL Error: " << SDL_GetError() << std::endl;
        }

        // Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    return newTexture;
}
