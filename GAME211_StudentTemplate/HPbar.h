#pragma once
#include "UiPanel.h"
#include <SDL.h>

class HealthBar {
private:
    float maxHealth;
    float currentHealth;
    SDL_Color barColour;
    float maxWidth;

public:
    HealthBar(float maxHealth_, float maxWidth_, SDL_Color barColour_) //HealthBar constructor, initialize with player stats, and bar information
        : maxHealth(maxHealth_), maxWidth(maxWidth_), barColour(barColour_) {
        currentHealth = maxHealth_;
    }

    void UpdateHealth(float newHealth) { currentHealth = std::max(0.0f, std::min(newHealth, maxHealth)); } //

    void Render(SDL_Renderer* renderer, Vec2 position, float height) {
        // Background bar
        SDL_Rect backgroundRect = { (int)position.x, (int)position.y, (int)maxWidth, (int)height };
        SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // Dark gray
        SDL_RenderFillRect(renderer, &backgroundRect);

        // Health bar
        float healthRatio = currentHealth / maxHealth;
        SDL_Rect healthRect = { (int)position.x, (int)position.y, (int)(maxWidth * healthRatio), (int)height }; //get length of hp bar based on healthratio
        SDL_SetRenderDrawColor(renderer, barColour.r, barColour.g, barColour.b, 255); //CHOOSE YOUR not character but COLOUR
        SDL_RenderFillRect(renderer, &healthRect);//creates rectangle
    }
};