#include "menu.h"
#include <iostream>
using namespace std;
SDL_Texture* Menu::loadTexture(const string& path, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(path.c_str());
    if (!surface) {
        cerr << "Failed to load image: " << path << ", " << IMG_GetError() << endl;
        return nullptr;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

bool Menu::init(SDL_Renderer* renderer) {
    backgroundTexture = loadTexture("menu_bg.png", renderer);
    startButton = loadTexture("Start.png", renderer);
    exitButton = loadTexture("Exit.png", renderer);

    if (!backgroundTexture || !startButton || !exitButton) {
        cerr << "Failed to load menu textures!" << endl;
        return false;
    }

    startRect = { 300, 150, 200, 150 };
    exitRect = { 300, 350, 200, 150 };

    return true;
}

void Menu::handleEvent(SDL_Event& e, bool& quit, bool& startGame) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;

        if (x > startRect.x && x < startRect.x + startRect.w &&
            y > startRect.y && y < startRect.y + startRect.h) {
            startGame = true;
        }
        if (x > exitRect.x && x < exitRect.x + exitRect.w &&
            y > exitRect.y && y < exitRect.y + exitRect.h) {
            quit = true;
        }
    }
}

void Menu::render(SDL_Renderer* renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, backgroundTexture, nullptr, nullptr);
    SDL_RenderCopy(renderer, startButton, nullptr, &startRect);
    SDL_RenderCopy(renderer, exitButton, nullptr, &exitRect);
    SDL_RenderPresent(renderer);
}

void Menu::cleanUp() {
    SDL_DestroyTexture(backgroundTexture);
    SDL_DestroyTexture(startButton);
    SDL_DestroyTexture(exitButton);
}
