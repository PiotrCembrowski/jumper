#include <SDL.h>
#include <vector>
#include "Platform.h"
#include "Player.h"
#include "Config.h"

Player::Player(float startX, float startY) 
    : x(startX), y(startY), dx(0), dy(0), w(64), h(64), 
      isGrounded(false), isJumping(false), jumpCounter(0), frame(0), timer(0) {}

void Player::handleInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (isGrounded) {
        // Horizontal logic
        if (state[SDL_SCANCODE_A]) dx -= ACCEL;
        else if (state[SDL_SCANCODE_D]) dx += ACCEL;
        else dx *= FRICTION;

        // Start Jump
        if (state[SDL_SCANCODE_W]) {
            dy = INITIAL_JUMP_FORCE; // Start with a small hop
            isGrounded = false;
            isJumping = true;      // Enable boosting
            jumpCounter = 0;       // Reset timer
        }
    } else {
        // --- VARIABLE JUMP LOGIC ---
        if (isJumping) {
            // If button is STILL held and we haven't reached max boost time
            if (state[SDL_SCANCODE_W] && jumpCounter < MAX_JUMP_TIME) {
                dy += JUMP_HOLD_ADDITION; // Add more upward force
                jumpCounter++;
            } else {
                // If button is released or time is up, stop boosting
                isJumping = false;
            }
        }
    }

    // Clamp horizontal speed
    if (dx > MAX_SPEED) dx = MAX_SPEED;
    if (dx < -MAX_SPEED) dx = -MAX_SPEED;
}

// ... update() and draw() remain the same ...

void Player::update(const std::vector<Platform>& platforms) {
    dy += GRAVITY;
    x += dx;
    y += dy;

    // --- SCREEN BOUNDARY CHECK ---
    if (x < 0) {
        x = 0;
        dx = 0; // Stop velocity if hitting a wall
    }
    if (x + w > SCREEN_WIDTH) {
        x = SCREEN_WIDTH - w;
        dx = 0;
    }

    // --- GROUND COLLISION ---
    if (y + h > GROUND_Y) {
        y = GROUND_Y - h;
        dy = 0;
        isGrounded = true;
        isJumping = false;
    }

    // --- PLATFORM COLLISION ---
    for (const auto& plat : platforms) {
        SDL_Rect platRect = plat.getRect();
        if (dy > 0 && x + w/2 > platRect.x && x + w/2 < platRect.x + platRect.w &&
            y + h > platRect.y && y + h < platRect.y + 10) {
            y = platRect.y - h;
            dy = 0;
            isGrounded = true;
            isJumping = false;
        }
    }
}

void Player::reset(float startX, float startY) {
    x = startX;
    y = startY;
    dx = 0;
    dy = 0;
    isGrounded = false;
    isJumping = false;
    jumpCounter = 0;
    frame = 0;
    timer = 0;
}

// 4. MUST HAVE Player:: here
void Player::draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet, float cameraY) {
    SDL_Rect srcRect = { frame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
    // We subtract cameraY here!
    SDL_Rect destRect = { (int)x, (int)(y - cameraY), w, h }; 
    
    SDL_RendererFlip flip = (dx < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, spriteSheet, &srcRect, &destRect, 0, NULL, flip);
}