#include "Player.h"
#include "Config.h"
#include "Platform.h"
#include <vector>

// 1. MUST HAVE Player:: here
Player::Player(float startX, float startY) 
    : x(startX), y(startY), dx(0), dy(0), w(64), h(64), 
      isGrounded(false), isJumping(false), jumpCounter(0), frame(0), timer(0) {}

// 2. MUST HAVE Player:: here
void Player::handleInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (isGrounded) {
        dx = 0; 
        if (state[SDL_SCANCODE_A]) dx = -PLAYER_SPEED;
        if (state[SDL_SCANCODE_D]) dx = PLAYER_SPEED;
        if (state[SDL_SCANCODE_W]) {
            dy = INITIAL_JUMP_FORCE;
            isGrounded = false;
            isJumping = true;
            jumpCounter = 0;
        }
    } else {
        if (isJumping) {
            if (state[SDL_SCANCODE_W] && jumpCounter < MAX_JUMP_TIME) {
                dy += JUMP_HOLD_ADDITION;
                jumpCounter++;
            } else {
                isJumping = false;
            }
        }
    }
}

// 3. MUST HAVE Player:: here (and match the new signature with vector)
void Player::update(const std::vector<Platform>& platforms) {
    dy += GRAVITY;
    x += dx;
    y += dy;

    if (y + h > GROUND_Y) {
        y = GROUND_Y - h;
        dy = 0;
        dx = 0;
        isGrounded = true;
        isJumping = false;
    }

    for (const auto& plat : platforms) {
        SDL_Rect platRect = plat.getRect();
        if (dy > 0 && 
            x + w/2 > platRect.x && x + w/2 < platRect.x + platRect.w &&
            y + h > platRect.y && y + h < platRect.y + 10) 
        {
            y = platRect.y - h;
            dy = 0;
            dx = 0;
            isGrounded = true;
            isJumping = false;
        }
    }

    timer++;
    if (timer > 8) {
        frame = (frame + 1) % 24;
        timer = 0;
    }
}

// 4. MUST HAVE Player:: here
void Player::draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet) {
    SDL_Rect srcRect = { frame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
    SDL_Rect destRect = { (int)x, (int)y, w, h };
    SDL_RendererFlip flip = (dx < 0) ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
    SDL_RenderCopyEx(renderer, spriteSheet, &srcRect, &destRect, 0, NULL, flip);
}