#ifndef BLOCK_H
#define BLOCK_H

#include <SDL.h>

struct Block {
    SDL_Rect rect;
    SDL_Color color;
    int speed;
    bool moving;
};
void initBlock(Block* block, int x, int y, int w, int h, SDL_Color color);
void updateBlock(Block* block, int screenWidth);
void renderBlock(const Block* block, SDL_Renderer* renderer);
void stopBlock(Block* block);
SDL_Rect getBlockRect(const Block* block);
bool isBlockMoving(const Block* block);

#endif
