#include "Player.h"
#include "Config.h"

Player::Player(float startX, float startY) : x(startX), y(startY), dy(0), w(64), h(64), frame(0), timer(0) {}

void Player::handleInput() {
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_LEFT]) x -= PLAYER_SPEED;
    if (state[SDL_SCANCODE_RIGHT]) x += PLAYER_SPEED;
}

void Player::update() {
    dy += GRAVITY;
    y += dy;

    // Floor collision
    if (y + h > SCREEN_HEIGHT) {
        y = SCREEN_HEIGHT - h;
        dy = JUMP_FORCE;
    }

    // Animation
    timer++;
    if (timer > 8) {
        frame = (frame + 1) % 24;
        timer = 0;
    }
}

void Player::draw(SDL_Renderer* renderer, SDL_Texture* spriteSheet) {
    SDL_Rect srcRect = { frame * FRAME_WIDTH, 0, FRAME_WIDTH, FRAME_HEIGHT };
    SDL_Rect destRect = { (int)x, (int)y, w, h };
    SDL_RenderCopy(renderer, spriteSheet, &srcRect, &destRect);
}