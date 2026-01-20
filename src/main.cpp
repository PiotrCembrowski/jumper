#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <stdlib.h> 
#include <algorithm>
#include <iostream>
#include "Player.h"
#include "Ground.h"
#include "Platform.h"
#include "Config.h"

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return 1;
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Dino Jumper", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Assets
    SDL_Texture* mortTex   = IMG_LoadTexture(renderer, "assets/img/mort.png");
    SDL_Texture* bgTex     = IMG_LoadTexture(renderer, "assets/img/background/plx-1.png");
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "assets/img/background/ground.png");
    SDL_Texture* platTex   = IMG_LoadTexture(renderer, "assets/img/background/plx-3.png");

    // Game State
    Player player(400, 400);
    Ground ground;
    std::vector<Platform> platforms;
    platforms.push_back(Platform(340, 500)); 

    float cameraY = 0;
    int score = 0;
    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) { 
            if (e.type == SDL_QUIT) running = false; 
        }

        // 1. Logic
        player.handleInput();
        player.update(platforms);

        // 2. Camera: Focus on the player as they climb
        if (player.getY() < cameraY + SCREEN_HEIGHT / 2) {
            cameraY = player.getY() - SCREEN_HEIGHT / 2;
        }

        // 3. Scoring: Height-based (Pixels climbed / 10)
        // Calculating score relative to starting position (Y=400)
        int currentHeight = (int)(400 - player.getY()) / 10;
        if (currentHeight > score) {
            score = currentHeight;
            std::cout << "Score: " << score << std::endl;
        }

        // 4. Platform Generation
        if (platforms.back().getY() > cameraY) {
            float lastX = platforms.back().getRect().x;
            float lastY = platforms.back().getY();

            float minX = std::max(0.0f, lastX - 200.0f);
            float maxX = std::min((float)SCREEN_WIDTH - PLATFORM_W, lastX + 200.0f);
            float newX = minX + (rand() % (int)(maxX - minX + 1));
            float newY = lastY - (100 + (rand() % 51));

            platforms.push_back(Platform(newX, newY));
        }

        // 5. Reset Logic (Bottom, Left, or Right death)
        if (player.getY() > cameraY + SCREEN_HEIGHT || player.getX() < -50 || player.getX() > SCREEN_WIDTH + 50) {
            std::cout << "Game Over! Final Score: " << score << std::endl;
            cameraY = 0;
            score = 0;
            player.reset(400, 300);
            platforms.clear();
            platforms.push_back(Platform(340, 500));
        }

        // 6. Memory Cleanup
        if (platforms.size() > 25) platforms.erase(platforms.begin());

        // 7. Rendering
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTex, NULL, NULL);
        ground.draw(renderer, groundTex, cameraY);
        for (auto& p : platforms) p.draw(renderer, platTex, cameraY);
        player.draw(renderer, mortTex, cameraY);
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(mortTex); SDL_DestroyTexture(bgTex);
    SDL_DestroyTexture(groundTex); SDL_DestroyTexture(platTex);
    SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window);
    IMG_Quit(); SDL_Quit();
    return 0;
}