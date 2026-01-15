#pragma once
#include <SDL.h>

class Ground {
public:
    Ground();
    void draw(SDL_Renderer* renderer, SDL_Texture* texture, float cameraY);
private:
    int x, y, w, h;
};