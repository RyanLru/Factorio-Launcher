/*
    Librairies for SDL with various function
*/

#include "librairies.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

// Function to create a screen with borderless
SDL_Window* createWindow(const char* title, int width, int height)
{
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if (window == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return NULL;
    }
    return window;
}

// Function to make background transparent to see the desktop backrgound
void setWindowTransparent(SDL_Window* window)
{
    SDL_SetWindowOpacity(window, 0.0);
}

// Function to add image
void addImage(SDL_Renderer* renderer, const char* path, int x, int y)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Error: %s\n", IMG_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Rect rect;
    rect.x = x;
    rect.y = y;
    rect.w = surface->w;
    rect.h = surface->h;

    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
