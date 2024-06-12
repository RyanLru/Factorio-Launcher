#ifndef LIBRAIRIES_H
#define LIBRAIRIES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

SDL_Window* createWindow(const char* title, int width, int height);
void setWindowTransparent(SDL_Window* window);
void addImage(SDL_Renderer* renderer, const char* path, int x, int y);

#endif // !LIBRAIRIES_H