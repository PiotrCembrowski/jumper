#pragma once
#include <SDL.h>

class Platform {
public:
    Platform(float x, float y);
    void draw(SDL_Renderer* renderer, SDL_Texture* tex);
    SDL_Rect getRect() const { return rect; }

private:
    SDL_Rect rect;
};