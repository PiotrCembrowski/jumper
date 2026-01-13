#include "Ground.h"
#include "Config.h"

Ground::Ground() {
    x = 0;
    y = GROUND_Y;
    w = SCREEN_WIDTH;
    h = 64; // Height of your ground image
}

void Ground::draw(SDL_Renderer* renderer, SDL_Texture* texture) {
    SDL_Rect destRect = { x, y, w, h };
    SDL_RenderCopy(renderer, texture, NULL, &destRect);
}