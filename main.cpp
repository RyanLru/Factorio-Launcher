#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "librairies.h"
#include "launch.h"

int main(int argc, const char** argv) {
    // Initialisation SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Erreur SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Création de la fenêtre avec des bords arrondis
    SDL_Window* window = createWindow("Factorio Launcher", 960, 540);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    // Créer un renderer pour la fenêtre
    SDL_Renderer* renderer = createRenderer(window);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Chargement des images de boutons
    addImage(renderer, "Images/Background.png", 0, 0, 960, 540);
    addButton(renderer, "Images/Close.png", 910, 5, 35, 35);
    addButton(renderer, "Images/Minimize.png", 870, 3, 37, 37);
    addButton(renderer, "Images/K2SE.png", 20, 30, 506, 111);
    addButton(renderer, "Images/Exotic Industries.png", 20, 150, 338, 109);
    addButton(renderer, "Images/Pyanodons.png", 20, 270, 299, 108);
    addButton(renderer, "Images/Vanilla.png", 20, 390, 239, 116);

    // Coordonnées du logo de sélection
    int x = -64; // Valeur initiale en dehors de l'écran pour qu'il ne soit pas visible au début
    int y = -64;

    // Entier pour enregistrer la sélection
    int selection = 0;

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

            // Si le bouton Close est cliqué
            if (isButtonClicked(event, 910, 5, 35, 35)) {
                isRunning = false;
            }

            // Si le bouton Minimize est cliqué
            if (isButtonClicked(event, 870, 3, 37, 37)) {
                SDL_MinimizeWindow(window);
            }

            // Si on Clique sur K2SE : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 30, 506, 111)) {
                x = 530;
                y = 55;
                selection = 1;
            }

            // Si on Clique sur Exotic Industries : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 150, 338, 109)) {
                x = 530;
                y = 175;
                selection = 2;
            }

            // Si on Clique sur Pyanodon : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 270, 299, 108)) {
                x = 530;
                y = 295;
                selection = 3;
            }

            // Si on Clique sur Vanilla : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 390, 239, 116)) {
                x = 530;
                y = 415;
                selection = 4;
            }

            // Si on clique sur le bouton de lancement
            if (isButtonClicked(event, 635, 440, 310, 75)) {
                // Lancer le transfert
                Transfert(selection);

                // Fermer la fenêtre
                isRunning = false;
            }

        }

        // Rendu des éléments fixes (une seule fois)
        SDL_RenderClear(renderer);
        addImage(renderer, "Images/Background.png", 0, 0, 960, 540);
        addImage(renderer, "Images/Play.png", 635, 440, 310, 75);
        addButton(renderer, "Images/Close.png", 910, 5, 35, 35);
        addButton(renderer, "Images/Minimize.png", 870, 3, 37, 37);
        addButton(renderer, "Images/K2SE.png", 20, 30, 506, 111);
        addButton(renderer, "Images/Exotic Industries.png", 20, 150, 338, 109);
        addButton(renderer, "Images/Pyanodons.png", 20, 270, 299, 108);
        addButton(renderer, "Images/Vanilla.png", 20, 390, 239, 116);

        // Rendu des logos
        addImage(renderer, "Images/Logo.png", x, y, 64, 64);

        // Mettre à jour l'affichage
        SDL_RenderPresent(renderer);

        // Limiter la boucle à 60 FPS
        SDL_Delay(1000 / 60);
    }



    // Nettoyage
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
