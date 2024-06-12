#ifndef LIBRAIRIES_H
#define LIBRAIRIES_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <X11/Xlib.h>
#include <SDL2/SDL_syswm.h>


SDL_Window* createWindow(const char* title, int width, int height);
void setWindowTransparent(SDL_Window* window);
SDL_Renderer* createRenderer(SDL_Window* window);
void addImage(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h);


#endif // !LIBRAIRIES_H