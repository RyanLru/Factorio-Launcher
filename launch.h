#ifndef LAUNCH_H
#define LAUNCH_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool checkModpacks(std::string& modpackName, std::string& modpackPath);
bool moveModstoFolder();
bool moveModsfromFolder(std::string modpackPath);
void Transfert(int selection);
bool checkSteam();
bool checkFactorio();
bool runFactorio();

#endif // !LAUNCH_H