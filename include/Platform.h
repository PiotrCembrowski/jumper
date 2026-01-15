#pragma once
#include <SDL.h>

class Platform {
public:
    Platform(float x, float y);
    void draw(SDL_Renderer* renderer, SDL_Texture* tex, float cameraY);
    SDL_Rect getRect() const { return rect; }
    float getY() const { return (float)rect.y; }

private:
    SDL_Rect rect;
};