#pragma once
#include <SDL.h>

class Player {
public:
    Player(float startX, float startY);
    void handleInput();
    void update();
    void draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet);

private:
    float x, y, dy;
    int w, h;
    int frame, timer;
    const int FRAME_WIDTH = 24;
    const int FRAME_HEIGHT = 24;
};