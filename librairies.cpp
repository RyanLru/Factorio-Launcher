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
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_BORDERLESS);
    if (window == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return NULL;
    }
    return window;
}

// Function to make background transparent to see the desktop backrgound for rendering
void setWindowTransparent(SDL_Window* window)
{
    SDL_SetWindowOpacity(window, 0.0);
}

// Function to create a renderer
SDL_Renderer* createRenderer(SDL_Window* window)
{
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return NULL;
    }
    return renderer;
}

// Function to add image
void addImage(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h)
{
    // Function to load png image with SDL_Image
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Error: %s\n", IMG_GetError());
        return;
    }

    // Function to create a texture from the surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    // Function to render the texture
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Clean up
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}


