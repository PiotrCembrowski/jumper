#include "Ground.h"
#include "Config.h"

Ground::Ground() {
    x = 0;
    y = GROUND_Y;
    w = SCREEN_WIDTH;
    h = 64;
}

void Ground::draw(SDL_Renderer* renderer, SDL_Texture* texture, float cameraY) {
    // We apply the camera offset here
    SDL_Rect destRect = { x, (int)(y - cameraY), w, h };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}