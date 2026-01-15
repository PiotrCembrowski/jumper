#pragma once
#include <SDL.h>
#include <vector>
#include "Platform.h"

class Player {
public:
    Player(float startX, float startY);
    void handleInput();
    void update(const std::vector<Platform>& platforms);
    void draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet, float cameraY);
    
    // The reset method
    void reset(float startX, float startY);
    
    float getY() const { return y; }

private:
    float x, y, dx, dy;
    int w, h;
    bool isGrounded, isJumping;
    int jumpCounter, frame, timer;
    
    // Changed from 'const' to 'int' to allow the object to be manageable
    int FRAME_WIDTH = 24;
    int FRAME_HEIGHT = 24;
};