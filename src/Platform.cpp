#include "Platform.h"

Platform::Platform(float x, float y) {
    rect = { (int)x, (int)y, 120, 30 }; // W and H from Config
}

void Platform::draw(SDL_Renderer* renderer, SDL_Texture* tex) {
    SDL_RenderCopy(renderer, tex, NULL, &rect);
}