#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h> // for rand()
#include "Player.h"
#include "Ground.h"
#include "Platform.h"
#include "Config.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Dino Jumper", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* mortTex = IMG_LoadTexture(renderer, "assets/img/mort.png");
    SDL_Texture* bgTex = IMG_LoadTexture(renderer, "assets/img/background/plx-1.png");
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "assets/img/background/ground.png");
    SDL_Texture* platTex = IMG_LoadTexture(renderer, "assets/img/background/plx-3.png");

    Player player(400, 400);
    Ground ground;
    std::vector<Platform> platforms;
    platforms.push_back(Platform(300, 300));

    float cameraY = 0;
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) running = false; }

        player.handleInput();
        player.update(platforms);

        // --- CAMERA LOGIC ---
        // If player goes above the middle of the screen, move camera up
        if (player.getY() < cameraY + SCREEN_HEIGHT / 2) {
            cameraY = player.getY() - SCREEN_HEIGHT / 2;
        }

        // --- GENERATE PLATFORMS ---
        if (platforms.back().getY() > cameraY) {
            // 1. Get the last platform's position
            float lastX = platforms.back().getRect().x;
            float lastY = platforms.back().getY();

            // 2. Randomize horizontal position, but keep it within reach of the last one
            // We try to stay within 200 pixels left or right of the previous platform
            float minX = std::max(0.0f, lastX - 200.0f);
            float maxX = std::min((float)SCREEN_WIDTH - 120, lastX + 200.0f);
            float newX = minX + (rand() % (int)(maxX - minX + 1));

            // 3. Randomize the height gap (between 100 and 140 pixels)
            // This ensures it is ALWAYS reachable with your jump force

            float newY = lastY - (100 + (rand() % 50));

            platforms.push_back(Platform(newX, newY));
        }

        // --- IMPROVED GAME OVER / RESET LOGIC ---

        bool fellOffBottom = (player.getY() > cameraY + SCREEN_HEIGHT);

        if (fellOffBottom ) {
            cameraY = 0;
            player.reset(400, 300);
            platforms.clear();
            platforms.push_back(Platform(300, 500));
            std::cout << "Mort out of bounds! Resetting..." << std::endl;
        }

        // 2. CHECK FOR GAME OVER
        // If Mort falls below the camera's view (bottom of screen)
        if (player.getY() > cameraY + SCREEN_HEIGHT) {
            // Reset Camera
            cameraY = 0;

            // Reset Player position (above the starting platform)
            player.reset(400, 400);

            // Reset Platforms (clear the old ones and add a starter)
            platforms.clear();
            platforms.push_back(Platform(300, 500)); // Starter platform
        }

        // 3. Generate new platforms if needed
        if (platforms.back().getY() > cameraY) {
            // ... (Your existing platform generation code) ...
        }

        // --- CLEANUP ---
        // Remove platforms that are far below the screen to save memory
        if (platforms.size() > 20) {
            platforms.erase(platforms.begin());
        }

        SDL_RenderClear(renderer);

        // Render everything with the cameraY offset
        SDL_RenderCopy(renderer, bgTex, NULL, NULL);
        ground.draw(renderer, groundTex, cameraY);
        for (auto& p : platforms) p.draw(renderer, platTex, cameraY);
        player.draw(renderer, mortTex, cameraY);

        SDL_RenderPresent(renderer);
    }

    return 0;
}