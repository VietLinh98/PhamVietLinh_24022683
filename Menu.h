#ifndef MENU_H
#define MENU_H

#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;
class Menu {
public:
    bool init(SDL_Renderer* renderer);
    void handleEvent(SDL_Event& e, bool& quit, bool& startGame);
    void render(SDL_Renderer* renderer);
    void cleanUp();

private:
    SDL_Texture* backgroundTexture;
    SDL_Texture* startButton;
    SDL_Texture* exitButton;

    SDL_Rect startRect;
    SDL_Rect exitRect;

    SDL_Texture* loadTexture(const string& path, SDL_Renderer* renderer);
};

#endif // MENU_H
