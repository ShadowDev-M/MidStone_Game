#include "Item.h"
#include <cmath>

void Item::CheckInRange(SDL_Window* window) {
    // Get the window's size
    int windowWidth, windowHeight;
    SDL_GetWindowSize(window, &windowWidth, &windowHeight);

    // Calculate the center of the screen
    SDL_Point center = { windowWidth / 2, windowHeight / 2 };

    // Get the current mouse position
    int mouseX, mouseY;
    SDL_GetMouseState(&mouseX, &mouseY);

    // Calculate the distance between the mouse position and the center of the screen
    float distX = mouseX - center.x;
    float distY = mouseY - center.y;
    float MouseDistance = std::sqrt(distX * distX + distY * distY);

    // Check if the distance is within the radius (range)
    inRange = (MouseDistance <= range);
}