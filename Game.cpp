#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
void initGame(Game* game) {
    game->window = nullptr;
    game->renderer = nullptr;
    game->running = false;
    game->currentBlock = nullptr;
    game->background = nullptr;

    srand(static_cast<unsigned>(time(0)));

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL Init Error: " << SDL_GetError() << endl;
        return;
    }

    game->window = SDL_CreateWindow("Building House", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                    SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!game->window) return;

    game->renderer = SDL_CreateRenderer(game->window, -1, SDL_RENDERER_ACCELERATED);
    if (!game->renderer) return;

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        cout << "Failed to initialize SDL_image: " << IMG_GetError() << endl;
        return;
    }

    loadBackground(game, "BackGround.png");

    int y = SCREEN_HEIGHT - BLOCK_HEIGHT;
    game->currentBlock = new Block;
    initBlock(game->currentBlock, 0, y, INIT_BLOCK_WIDTH, BLOCK_HEIGHT, randomColor());
    game->running = true;
}

void loadBackground(Game* game, const char* filePath) {
    SDL_Surface* bgSurface = IMG_Load(filePath);
    if (!bgSurface) {
        cout << "Error loading background: " << IMG_GetError() << endl;
        return;
    }
    game->background = SDL_CreateTextureFromSurface(game->renderer, bgSurface);
    SDL_FreeSurface(bgSurface);
}

SDL_Color randomColor() {
    return SDL_Color{static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), static_cast<Uint8>(rand() % 256), 255};
}

void runGame(Game* game) {
    while (game->running) {
        handleEvents(game);
        updateGame(game);
        renderGame(game);
        SDL_Delay(16);
    }
}

void handleEvents(Game* game) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) game->running = false;
        if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) placeBlock(game);
    }
}

void updateGame(Game* game) {
    if (game->currentBlock) {
        updateBlock(game->currentBlock, SCREEN_WIDTH);
    }
}

void renderGame(Game* game) {
    SDL_RenderClear(game->renderer);

    if (game->background) {
        SDL_RenderCopy(game->renderer, game->background, NULL, NULL);
    }

    for (const auto& b : game->stack) {
        renderBlock(&b, game->renderer);
    }

    if (game->currentBlock) {
        renderBlock(game->currentBlock, game->renderer);
    }

    SDL_RenderPresent(game->renderer);
}

void placeBlock(Game* game) {
    if (!game->currentBlock) return;

    stopBlock(game->currentBlock);
    SDL_Rect curr = getBlockRect(game->currentBlock);

    if (!game->stack.empty()) {
        SDL_Rect prev = getBlockRect(&game->stack.back());

        int delta = curr.x - prev.x;
        int overlap = prev.w - abs(delta);

    if (overlap <= 0) {
        cout << "Game Over!" << endl;
        delete game->currentBlock;
        game->currentBlock = nullptr;
        game->running = false;

        cleanGame(game);
        exit(0);
    }
        int newX = (delta >= 0) ? curr.x : prev.x;
        Block placed;
        initBlock(&placed, newX, curr.y, overlap, BLOCK_HEIGHT, randomColor());
        game->stack.push_back(placed);

        int newY = placed.rect.y - BLOCK_HEIGHT;
        game->currentBlock = new Block;
        initBlock(game->currentBlock, 0, newY, overlap, BLOCK_HEIGHT, randomColor());
    } else {
        game->stack.push_back(*game->currentBlock);
        int newY = SCREEN_HEIGHT - 2 * BLOCK_HEIGHT;
        delete game->currentBlock;
        game->currentBlock = new Block;
        initBlock(game->currentBlock, 0, newY, INIT_BLOCK_WIDTH, BLOCK_HEIGHT, randomColor());
    }
}

void cleanGame(Game* game) {
    if (game->background) SDL_DestroyTexture(game->background);
    if (game->currentBlock) delete game->currentBlock;
    SDL_DestroyRenderer(game->renderer);
    SDL_DestroyWindow(game->window);
    IMG_Quit();
    SDL_Quit();
}
