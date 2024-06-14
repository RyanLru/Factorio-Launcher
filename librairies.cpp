/*
    Libraries for SDL with various functions
*/

#include "librairies.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Creates a borderless SDL window.
 *
 * @param title The title of the window.
 * @param width The width of the window.
 * @param height The height of the window.
 * @return SDL_Window* Pointer to the created window.
 */
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

/**
 * @brief Makes the window background transparent.
 *
 * @param window Pointer to the SDL window.
 */
void setWindowTransparent(SDL_Window* window)
{
    SDL_SetWindowOpacity(window, 0.0);
}

/**
 * @brief Creates a renderer for the given window.
 *
 * @param window Pointer to the SDL window.
 * @return SDL_Renderer* Pointer to the created renderer.
 */
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

/**
 * @brief Adds an image to the renderer at the specified position and size.
 *
 * @param renderer Pointer to the SDL renderer.
 * @param path Path to the image file.
 * @param x X-coordinate of the image.
 * @param y Y-coordinate of the image.
 * @param w Width of the image.
 * @param h Height of the image.
 */
void addImage(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h)
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

    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * @brief Checks if a button is clicked based on the event and button position/size.
 *
 * @param event The SDL event.
 * @param x X-coordinate of the button.
 * @param y Y-coordinate of the button.
 * @param w Width of the button.
 * @param h Height of the button.
 * @return true if the button is clicked, false otherwise.
 */
bool isButtonClicked(SDL_Event event, int x, int y, int w, int h)
{
    if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        int xMouse, yMouse;
        SDL_GetMouseState(&xMouse, &yMouse);
        if (xMouse >= x && xMouse <= x + w && yMouse >= y && yMouse <= y + h)
        {
            return true;
        }
    }
    return false;
}

/**
 * @brief Adds a button image to the renderer at the specified position and size.
 *
 * @param renderer Pointer to the SDL renderer.
 * @param path Path to the image file.
 * @param x X-coordinate of the button.
 * @param y Y-coordinate of the button.
 * @param w Width of the button.
 * @param h Height of the button.
 */
void addButton(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h)
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
        return ;
    }

    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}

/**
 * @brief Writes text on the screen at the specified position and size.
 *
 * @param renderer Pointer to the SDL renderer.
 * @param text The text to be displayed.
 * @param x X-coordinate of the text.
 * @param y Y-coordinate of the text.
 * @param size Font size of the text.
 */
void writeText(SDL_Renderer* renderer, const char* text, int x, int y, int size)
{
    TTF_Init();

    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", size);
    if (font == NULL)
    {
        printf("Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
    {
        printf("Error: %s\n", TTF_GetError());
        return;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Rect rect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
}

/**
 * @brief Adds an icon to the SDL window.
 *
 * @param window Pointer to the SDL window.
 * @param path Path to the icon image file.
 */
void addIcon(SDL_Window* window, const char* path)
{
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Error: %s\n", IMG_GetError());
        return;
    }

    SDL_SetWindowIcon(window, surface);

    SDL_FreeSurface(surface);
}

/**
 * @brief Deletes common files between two directories.
 *
 * @param directory1 Path to the first directory.
 */
void deleteCommonFiles(const std::string& directory1) {
    const std::string directory2 = "/home/ryanl/Bureau/Projet/Factorio-Launcher/ModPacks/QOL";

    std::set<std::string> filesInDirectory2;

    for (const auto& entry : fs::directory_iterator(directory2)) {
        if (entry.is_regular_file() && entry.path().extension() == ".zip") {
            filesInDirectory2.insert(entry.path().filename().string());
        }
    }

    for (const auto& entry : fs::directory_iterator(directory1)) {
        if (entry.is_regular_file() && entry.path().extension() == ".zip") {
            if (filesInDirectory2.find(entry.path().filename().string()) != filesInDirectory2.end()) {
                fs::remove(entry.path());
                std::cout << "Deleted: " << entry.path().filename().string() << std::endl;
            }
        }
    }
}

/**
 * @brief Moves QOL mods to the mods directory.
 */
void moveQOLtoFolder() {
    const std::string modDirPath = "/home/ryanl/.factorio/mods";
    const std::string modpackPath = "/home/ryanl/Bureau/Projet/Factorio-Launcher/ModPacks/QOL";

    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Error: the mods directory does not exist or is not a directory." << std::endl;
        return;
    }

    if (!fs::exists(modpackPath) || !fs::is_directory(modpackPath)) {
        std::cerr << "Error: the modpack directory does not exist or is not a directory." << std::endl;
        return;
    }

    for (const auto& entry : fs::directory_iterator(modpackPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".zip") {
            fs::copy(entry.path(), modDirPath / entry.path().filename(), fs::copy_options::recursive);
        }
    }
}
