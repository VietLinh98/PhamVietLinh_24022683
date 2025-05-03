#include "Game.h"
#include "menu.h"
#include <SDL.h>
#include <iostream>
using namespace std;
int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow("Game Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Menu menu;
    if (!menu.init(renderer)) {
        cerr << "Failed to initialize menu!" << endl;
        return 1;
    }

    bool quit = false;
    bool startGame = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            menu.handleEvent(e, quit, startGame);
        }

        menu.render(renderer);

        if (startGame) {
            Game game;
            initGame(&game);
            if (game.running) {
                runGame(&game);
            }
            startGame = false;
        }
    }

    menu.cleanUp();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
