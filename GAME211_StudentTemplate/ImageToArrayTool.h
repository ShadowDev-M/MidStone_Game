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
    Uint8* pixels = (Uint8*)surface->pixels; // Cast to Uint8* for 24-bit access    

    for (int y = 0; y < surface->h; ++y) {
        for (int x = 0; x < surface->w; ++x) {

            Uint8* pixel = &pixels[(y * surface->pitch) + (x * 3)];            // Get RGB values using the format of the surface
            SDL_GetRGB(*pixel, surface->format, &r, &g, &b);
          //  printf("{colour %d, colour %d, colour %d}, ", r, g, b);

            // Convert to grayscale
            Uint8 grayscale = (Uint8)abs((0.299 * r + 0.587 * g + 0.114 * b));

            printf("{%d, %d, %d}, ", x, y, abs(r-255)/255);
        }
        printf("\n");
    }

    // Unlock the surface if locked
    if (SDL_MUSTLOCK(surface)) {
        SDL_UnlockSurface(surface);
    }
}

