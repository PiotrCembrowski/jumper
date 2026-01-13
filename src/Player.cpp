#include "Player.h"
#include "Config.h"

Player::Player(float startX, float startY) 
    : x(startX), y(startY), dx(0), dy(0), w(64), h(64), 
      isGrounded(false), isJumping(false), jumpCounter(0), frame(0), timer(0) {}

void Player::handleInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);

    if (isGrounded) {
        dx = 0; 
        if (state[SDL_SCANCODE_A]) dx = -PLAYER_SPEED;
        if (state[SDL_SCANCODE_D]) dx = PLAYER_SPEED;

        // START JUMP
        if (state[SDL_SCANCODE_W]) {
            dy = INITIAL_JUMP_FORCE;
            isGrounded = false;
            isJumping = true;
            jumpCounter = 0;
        }
    } else {
        // VARIABLE JUMP LOGIC (While in the air)
        if (isJumping) {
            // If still holding W and haven't reached max time, add upward force
            if (state[SDL_SCANCODE_W] && jumpCounter < MAX_JUMP_TIME) {
                dy += JUMP_HOLD_ADDITION;
                jumpCounter++;
            } else {
                // Stop boosting if W is released or time is up
                isJumping = false;
            }
        }
    }
}

void Player::update() {
    dy += GRAVITY;
    x += dx;
    y += dy;

    if (y + h > GROUND_Y) {
        y = GROUND_Y - h;
        dy = 0;
        dx = 0;
        isGrounded = true;
        isJumping = false; // Reset jump state when landing
        jumpCounter = 0;
    }

    timer++;
    if (timer > 8) {
        frame = (frame + 1) % 24;
        timer = 0;
    }
}

void Player::draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet) {
    SDL_Rect srcRect = { frame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
    SDL_Rect destRect = { (int)x, (int)y, w, h };
    SDL_RendererFlip flip = (dx < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, spriteSheet, &srcRect, &destRect, 0, NULL, flip);
}