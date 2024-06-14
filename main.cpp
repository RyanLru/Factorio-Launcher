#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "librairies.h"
#include "launch.h"

/**
 * @brief Main entry point for the Factorio Launcher.
 * 
 * Initializes SDL, creates the main application window and renderer, 
 * loads images and buttons, and handles the main event loop.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Exit status.
 */
int main(int argc, const char** argv) {
    // Initialize SDL with video support
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "Error SDL_Init: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Create the main application window with rounded borders
    SDL_Window* window = createWindow("Factorio Launcher", 960, 540);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    // Create a renderer for the window
    SDL_Renderer* renderer = createRenderer(window);
    if (!renderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Add window icon
    addIcon(window, "Images/Logo.png");

    // Load button images
    addImage(renderer, "Images/Background.png", 0, 0, 960, 540);
    addButton(renderer, "Images/Close.png", 910, 5, 35, 35);
    addButton(renderer, "Images/Minimize.png", 870, 3, 37, 37);
    addButton(renderer, "Images/K2SE.png", 20, 30, 510, 110);
    addButton(renderer, "Images/Exotic Industries.png", 20, 150, 510, 110);
    addButton(renderer, "Images/Pyanodons.png", 20, 270, 510, 110);
    addButton(renderer, "Images/Vanilla.png", 20, 390, 510, 110);

    // Coordinates for the selection logo
    int x = -64; // Initial value off-screen to hide initially
    int y = -64;

    // Variable to store the selection
    int selection = 0;

    // Page system
    int page = 1;
    const int page_max = 4;

    bool QOL = true;

    // SDL event handling
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

            // Handle button clicks
            if (isButtonClicked(event, 910, 5, 35, 35)) {
                isRunning = false;
            }

            if (isButtonClicked(event, 870, 3, 37, 37)) {
                SDL_MinimizeWindow(window);
            }

            if (isButtonClicked(event, 20, 30, 510, 110)) {
                y = 55;
                selection = 1;
            }

            if (isButtonClicked(event, 20, 150, 510, 110)) {
                y = 175;
                selection = 2;
            }

            if (isButtonClicked(event, 20, 270, 510, 110)) {
                y = 295;
                selection = 3;
            }

            if (isButtonClicked(event, 20, 390, 510, 110)) {
                y = 415;
                selection = 4;
            }

            if (isButtonClicked(event, 20, 30, 510, 110)) {
                y = 55;
                selection = 5;
            }

            if (isButtonClicked(event, 635, 440, 310, 75)) {
                // Launch the transfer
                Transfer(selection, QOL);

                // Close the window
                isRunning = false;
            }

            // Handle page navigation
            if (isButtonClicked(event, 495, 505, 32, 32)) {
                if (page > 1) {
                    page--;
                } else {
                    page = page_max;
                }
            }

            if (isButtonClicked(event, 570, 505, 32, 32)) {
                if (page < page_max) {
                    page++;
                } else {
                    page = 1;
                }
            }

            // Handle play button hover effect
            if (event.type == SDL_MOUSEMOTION) {
                if (event.motion.x >= 635 && event.motion.x <= 945 && event.motion.y >= 440 && event.motion.y <= 515) {
                    PlayHover = true;
                } else {
                    PlayHover = false;
                }
            }

            // Handle QOL button click
            if (isButtonClicked(event, 715, 390, 155, 35)) {
                QOL = !QOL;
            }
        }

        // Render the static elements (only once)
        SDL_RenderClear(renderer);
        addImage(renderer, "Images/Background.png", 0, 0, 960, 540);
        addButton(renderer, "Images/Close.png", 910, 5, 35, 35);
        addButton(renderer, "Images/Minimize.png", 870, 3, 37, 37);
        if (PlayHover == false) {
            addButton(renderer, "Images/Play.png", 635, 440, 310, 75);
        } else {
            addButton(renderer, "Images/Play_hover.png", 635, 440, 310, 75);
        }

        if (page == 1) {
            addButton(renderer, "Images/K2SE.png", 20, 30, 510, 110);
            addButton(renderer, "Images/Exotic Industries.png", 20, 150, 510, 110);
            addButton(renderer, "Images/Pyanodons.png", 20, 270, 510, 110);
            addButton(renderer, "Images/Vanilla.png", 20, 390, 510, 110);
        }
        if (page == 2) {
            addButton(renderer, "Images/Angel-Bob.png", 20, 30, 510, 110);
        }
        // Render the selection logo
        addImage(renderer, "Images/Logo.png", 540, y, 64, 64);

        // Render the QOL checkbox
        if (QOL) {
            addButton(renderer, "Images/QOL_true.png", 715, 390, 155, 35);
        } else {
            addButton(renderer, "Images/QOL_false.png", 715, 390, 155, 35);
        }

        addImage(renderer, "Images/Arrow-left.png", 495, 505, 32, 32);
        addImage(renderer, "Images/Arrow-right.png", 570, 505, 32, 32);

        // Add text with the page number
        writeText(renderer, std::to_string(page).c_str(), 540, 510, 20);

        // Update the display
        SDL_RenderPresent(renderer);

        // Limit the loop to 60 FPS
        SDL_Delay(1000 / 60);
    }

    // Cleanup
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
