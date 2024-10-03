#include <SDL.h>
#include <stdio.h>

void readPixelsInGrayscale(SDL_Surface* surface) {
    // Lock the surface for direct pixel access
    if (SDL_MUSTLOCK(surface)) {
        if (SDL_LockSurface(surface) < 0) {
            printf("Unable to lock surface: %s\n", SDL_GetError());
            return;
        }
    }

    // Get surface pixel format
    Uint8 r, g, b;
    Uint32* pixels = (Uint32*)surface->pixels;

    for (int y = 0; y < surface->h; ++y) {
        for (int x = 0; x < surface->w; ++x) {
            Uint32 pixel = pixels[(y * surface->w) + x];

            // Get RGB values using the format of the surface
            SDL_GetRGB(pixel, surface->format, &r, &g, &b);

            // Convert to grayscale
            Uint8 grayscale = (Uint8)abs((0.299 * r + 0.587 * g + 0.114 * b)/255-1);

            printf("{%d, %d, %d}, ", x, y, grayscale);
        }
        printf("\n");
    }

    // Unlock the surface if locked
    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

int main() {
    // Initialize SDL and create a surface (example surface)
    SDL_Init(SDL_INIT_VIDEO);

    // Load a BMP image into a surface (example)
    SDL_Surface* image = SDL_LoadBMP("image.bmp");

    if (image == NULL) {
        printf("Unable to load image: %s\n", SDL_GetError());
        return 1;
    }

    // Read pixels in grayscale
    readPixelsInGrayscale(image);

    // Cleanup
    SDL_FreeSurface(image);
    SDL_Quit();

    return 0;
}