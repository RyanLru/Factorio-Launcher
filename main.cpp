#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "librairies.h"

// Ajoutez la définition de createRoundWindow ici (voir étape 1 pour le code complet)

int main(int argc, const char** argv) {
    // Initialisation SDL
    SDL_Init(SDL_INIT_VIDEO);

    // Création de la fenêtre avec des bords arrondis
    SDL_Window* window = createRoundWindow("Launcher", 960, 540);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    // Créer un renderer pour la fenêtre
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Gestion des événements SDL
    bool isRunning = true;
    SDL_Event event;
    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            } else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
        }

        // Ajout d'une image
        addImage(renderer, "Images/Background.png", 0, 0, 960, 540);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);
    }

    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
