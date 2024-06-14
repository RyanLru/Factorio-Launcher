/*
    Librairies for SDL with various function
*/

#include "librairies.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <set>
#include <filesystem>

namespace fs = std::filesystem;

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

// Function to dectection if button is clicked
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

// Function to add button
void addButton(SDL_Renderer* renderer, const char* path, int x, int y, int w, int h)
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
        return ;
    }

    // Function to render the texture
    SDL_Rect rect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Clean up
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

    return;
}

// Fonction pour écrire un texte sur l'écran
void writeText(SDL_Renderer* renderer, const char* text, int x, int y, int size)
{
    // Initialisation de SDL_ttf
    TTF_Init();

    // Charger la police
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/TTF/DejaVuSans-Bold.ttf", size);
    if (font == NULL)
    {
        printf("Error: %s\n", TTF_GetError());
        return;
    }

    // Créer une surface de texte
    SDL_Color color = { 255, 255, 255 };
    SDL_Surface* surface = TTF_RenderText_Solid(font, text, color);
    if (surface == NULL)
    {
        printf("Error: %s\n", TTF_GetError());
        return;
    }

    // Créer une texture de texte
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL)
    {
        printf("Error: %s\n", SDL_GetError());
        return;
    }

    // Créer un rectangle pour le texte
    SDL_Rect rect = { x, y, surface->w, surface->h };

    // Afficher le texte
    SDL_RenderCopy(renderer, texture, NULL, &rect);

    // Nettoyer
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
    TTF_CloseFont(font);
    TTF_Quit();
}

// Function to add icon to the window
void addIcon(SDL_Window* window, const char* path)
{
    // Function to load png image with SDL_Image
    SDL_Surface* surface = IMG_Load(path);
    if (surface == NULL)
    {
        printf("Error: %s\n", IMG_GetError());
        return;
    }

    // Function to set the icon
    SDL_SetWindowIcon(window, surface);

    // Clean up
    SDL_FreeSurface(surface);
}

void supprimerFichiersCommuns(const std::string& dossier1) {
    // Chemin vers le dossier de référence
    const std::string dossier2 = "/home/ryanl/Bureau/Projet/Factorio-Launcher/ModPacks/QOL";

    // 1. Stocker les noms des fichiers dans le dossier de référence dans un set
    std::set<std::string> fichiersDossier2;

    // Parcours du dossier de référence
    for (const auto& entry : fs::directory_iterator(dossier2)) {
        if (entry.is_regular_file() && entry.path().extension() == ".zip") {
            fichiersDossier2.insert(entry.path().filename().string());
        }
    }

    // 2. Parcourir le premier dossier et supprimer les fichiers communs
    for (const auto& entry : fs::directory_iterator(dossier1)) {
        if (entry.is_regular_file() && entry.path().extension() == ".zip") {
            // Vérifier si le fichier est également dans le dossier de référence
            if (fichiersDossier2.find(entry.path().filename().string()) != fichiersDossier2.end()) {
                // Supprimer le fichier du premier dossier
                fs::remove(entry.path());
                std::cout << "Supprimé: " << entry.path().filename().string() << std::endl;
            }
        }
    }
}

// Fonction pour déplacer les QOL vers le dossier des mods
void moveQOLtoFolder() {
    // Chemin du répertoire des mods
    const std::string modDirPath = "/home/ryanl/.factorio/mods";

    // Chemin du répertoire du modpack
    const std::string modpackPath = "/home/ryanl/Bureau/Projet/Factorio-Launcher/ModPacks/QOL";

    // Vérifier si le répertoire des mods existe
    if (!fs::exists(modDirPath) || !fs::is_directory(modDirPath)) {
        std::cerr << "Erreur: le répertoire des mods n'existe pas ou n'est pas un répertoire." << std::endl;
        return;
    }

    // Vérifier si le répertoire du modpack existe
    if (!fs::exists(modpackPath) || !fs::is_directory(modpackPath)) {
        std::cerr << "Erreur: le répertoire du modpack n'existe pas ou n'est pas un répertoire." << std::endl;
        return;
    }

    // On Duplique les mods du répertoire du modpack vers le répertoire des mods
    for (const auto& entry : fs::directory_iterator(modpackPath)) {
        // On Vérifie si le fichier est un fichier zip
        if (entry.is_regular_file() && entry.path().extension() == ".zip") {
            fs::copy(entry.path(), modDirPath / entry.path().filename(), fs::copy_options::recursive);
        }
    }
}




