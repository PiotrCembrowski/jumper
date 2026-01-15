#include "Platform.h"
#include "Config.h"

Platform::Platform(float x, float y) {
    rect = { (int)x, (int)y, PLATFORM_W, PLATFORM_H };
}

void Platform::draw(SDL_Renderer* renderer, SDL_Texture* tex, float cameraY) {
    SDL_Rect drawRect = { rect.x, (int)(rect.y - cameraY), rect.w, rect.h };
    SDL_RenderCopy(renderer, tex, NULL, &drawRect);
}