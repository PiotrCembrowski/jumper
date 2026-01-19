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
    void reset(float startX, float startY);

    float getX() const { return x; }
    float getY() const { return y; }

private:
    float x, y, dx, dy;
    int w, h;
    
    // Jump Sensitivity State
    bool isGrounded;
    bool isJumping;    // Are we currently boosting upward?
    int jumpCounter;  // How many frames have we been boosting?

    int frame, timer;
    const int FRAME_WIDTH = 24;
    const int FRAME_HEIGHT = 24;
};