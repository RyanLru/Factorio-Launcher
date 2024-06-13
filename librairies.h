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
bool isButtonClicked(SDL_Event event, int x, int y, int w, int h);
void addButton(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h);
void writeText(SDL_Renderer* renderer, const char* text, int x, int y, int size);
void addIcon(SDL_Window* window, const char* path);


#endif // !LIBRAIRIES_H