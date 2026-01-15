#pragma once
#include <SDL.h>
#include <vector>     // Add this
#include "Platform.h" // Add this

class Player {
public:
    Player(float startX, float startY);
    void handleInput();
    // Update this line to match the .cpp file:
    void update(const std::vector<Platform>& platforms); 
    void draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet);

private:
    float x, y, dx, dy;
    int w, h;
    bool isGrounded;
    bool isJumping;
    int jumpCounter;
    int frame, timer;
    const int FRAME_WIDTH = 24;
    const int FRAME_HEIGHT = 24;
};