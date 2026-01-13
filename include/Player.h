#pragma once
#include <SDL.h>

class Player {
public:
    Player(float startX, float startY);
    void handleInput();
    void update();
    void draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet);

private:
    float x, y;
    float dx, dy;
    int w, h;
    
    bool isGrounded;
    bool isJumping;    // New: Tracks if we are currently in a "boosting" phase
    int jumpCounter;  // New: Tracks how many frames W has been held

    int frame, timer;
    const int FRAME_WIDTH = 24;
    const int FRAME_HEIGHT = 24;
};