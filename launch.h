#ifndef LAUNCH_H
#define LAUNCH_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool checkModpacks(std::string& modpackName, std::string& modpackPath);
bool moveModstoFolder();
bool moveModsfromFolder(std::string modpackPath);
void Transfert(int selection, bool QOL);
bool checkFactorio();
void launchFactorio();

#endif // !LAUNCH_H