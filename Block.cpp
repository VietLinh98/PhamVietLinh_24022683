#include "Block.h"

void initBlock(Block* block, int x, int y, int w, int h, SDL_Color color) {
    block->rect = { x, y, w, h };
    block->color = color;
    block->speed = 10;
    block->moving = true;
}

void updateBlock(Block* block, int screenWidth) {
    if (block->moving) {
        block->rect.x += block->speed;
        if (block->rect.x <= 0 || block->rect.x + block->rect.w >= screenWidth) {
            block->speed = -block->speed;
        }
    }
}

void renderBlock(const Block* block, SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, block->color.r, block->color.g, block->color.b, block->color.a);
    SDL_RenderFillRect(renderer, &block->rect);
}

void stopBlock(Block* block) {
    block->moving = false;
}

SDL_Rect getBlockRect(const Block* block) {
    return block->rect;
}

bool isBlockMoving(const Block* block) {
    return block->moving;
}
