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

    // Ajout de l'icône de la fenêtre
    addIcon(window, "Images/Logo.png");

    // Chargement des images de boutons
    addImage(renderer, "Images/Background.png", 0, 0, 960, 540);
    addButton(renderer, "Images/Close.png", 910, 5, 35, 35);
    addButton(renderer, "Images/Minimize.png", 870, 3, 37, 37);
    addButton(renderer, "Images/K2SE.png", 20, 30, 510, 110);
    addButton(renderer, "Images/Exotic Industries.png", 20, 150, 510, 110);
    addButton(renderer, "Images/Pyanodons.png", 20, 270, 510, 110);
    addButton(renderer, "Images/Vanilla.png", 20, 390, 510, 110);

    // Coordonnées du logo de sélection
    int x = -64; // Valeur initiale en dehors de l'écran pour qu'il ne soit pas visible au début
    int y = -64;

    // Entier pour enregistrer la sélection
    int selection = 0;

    // Système de Pages
    int page = 1;
    int page_max = 4;

    bool QOL = true;

    // Gestion des événements SDL
    bool isRunning = true;
    bool PlayHover = false;
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
            if (isButtonClicked(event, 20, 30, 510, 110)) {
                y = 55;
                selection = 1;
            }

            // Si on Clique sur Exotic Industries : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 150, 510, 110)) {
                y = 175;
                selection = 2;
            }

            // Si on Clique sur Pyanodon : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 270, 510, 110)) {
                y = 295;
                selection = 3;
            }

            // Si on Clique sur Vanilla : Change le logo de place pour l'aligner avec le bouton
            if (isButtonClicked(event, 20, 390, 510, 110)) {
                y = 415;
                selection = 4;
            }

            // Si on clique sur le bouton de lancement
            if (isButtonClicked(event, 635, 440, 310, 75)) {
                // Lancer le transfert
                Transfert(selection, QOL);

                // Fermer la fenêtre
                isRunning = false;
            }

            

            /* Si on clique sur la flèche de gauche
            if (isButtonClicked(event, 470, 463, 39, 39)) {
                if(page > 1){
                    page--;
                }
                // Sinon on retourne à la dernière page
                else{
                    page = page_max;
                }
            }

            // Si on clique sur la flèche de droite
            if (isButtonClicked(event, 545, 463, 39, 39)) {
                if(page < page_max){
                    page++;
                }
                // Sinon on retourne à la première page
                else{
                    page = 1;
                }
            }
            */

           // Si On Passe notre souris sur le bouton play 
            if (event.type == SDL_MOUSEMOTION) {
                if (event.motion.x >= 635 && event.motion.x <= 945 && event.motion.y >= 440 && event.motion.y <= 515) {
                    PlayHover = true;
                }
                else{
                    PlayHover = false;
                }
            }

            // Si on clique sur le bouton QOL
            if (isButtonClicked(event, 715, 390, 155, 35)) {
                QOL = !QOL;
            }

        }

        // Rendu des éléments fixes (une seule fois)
        SDL_RenderClear(renderer);
        addImage(renderer, "Images/Background.png", 0, 0, 960, 540);
        addButton(renderer, "Images/Close.png", 910, 5, 35, 35);
        addButton(renderer, "Images/Minimize.png", 870, 3, 37, 37);
        if(PlayHover == false){
            addButton(renderer, "Images/Play.png", 635, 440, 310, 75);
        }
        else{
            addButton(renderer, "Images/Play_hover.png", 635, 440, 310, 75);
        }

        if(page == 1){

            addButton(renderer, "Images/K2SE.png", 20, 30, 510, 110);
            addButton(renderer, "Images/Exotic Industries.png", 20, 150, 510, 110);
            addButton(renderer, "Images/Pyanodons.png", 20, 270, 510, 110);
            addButton(renderer, "Images/Vanilla.png", 20, 390, 510, 110);
        }
        // Rendu des logos
        addImage(renderer, "Images/Logo.png", 540, y, 64, 64);

        // Rendu Coche QOL
        if(QOL){
            addButton(renderer, "Images/QOL_true.png", 715, 390, 155, 35);
        }
        else{
            addButton(renderer, "Images/QOL_false.png", 715, 390, 155, 35);
        }

        
        //addImage(renderer, "Images/Arrow-left.png", 470, 463, 39, 39);
        //addImage(renderer, "Images/Arrow-right.png", 545, 463, 39, 39);

        // Ajout d'un Texte avec le numéro de la page
        //writeText(renderer, std::to_string(page).c_str(), 520, 470, 20);

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
