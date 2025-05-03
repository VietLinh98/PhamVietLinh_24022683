#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <vector>
#include <SDL_image.h>
#include "Block.h"
using namespace std;
struct Game {
    SDL_Window* window;
    SDL_Renderer* renderer;
    bool running;
    vector<Block> stack;
    Block* currentBlock;
    SDL_Texture* background;
};
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BLOCK_HEIGHT = 30;
const int INIT_BLOCK_WIDTH = 200;
void initGame(Game* game);
void runGame(Game* game);
void handleEvents(Game* game);
void updateGame(Game* game);
void renderGame(Game* game);
void placeBlock(Game* game);
void cleanGame(Game* game);
void loadBackground(Game* game, const char* filePath);
SDL_Color randomColor();

#endif
