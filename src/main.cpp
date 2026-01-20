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

    // Game State Initialization
    // Start Mort on the ground (GROUND_Y - player_height)
    float startX = 400.0f;
    float startY = GROUND_Y - 64.0f; 
    Player player(startX, startY);
    Ground ground;
    
    std::vector<Platform> platforms;
    // First platform at 1/3 screen height above ground
    float firstPlatY = GROUND_Y - (SCREEN_HEIGHT / 3.0f);
    platforms.push_back(Platform(340, firstPlatY)); 

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

        // 3. Scoring: Height-based (relative to starting ground)
        int currentHeight = (int)(startY - player.getY()) / 10;
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
            
            // Gap between 100 and 150 pixels for reachability
            float newY = lastY - (100 + (rand() % 51));

            platforms.push_back(Platform(newX, newY));
        }

        // 5. Reset Logic (Bottom, Left, or Right death)
        bool fellOffBottom = (player.getY() > cameraY + SCREEN_HEIGHT);
        bool offLeft       = (player.getX() < -50);
        bool offRight      = (player.getX() > SCREEN_WIDTH + 50);

        if (fellOffBottom || offLeft || offRight) {
            std::cout << "Game Over! Final Score: " << score << std::endl;
            
            cameraY = 0;
            score = 0;
            player.reset(startX, startY);
            
            platforms.clear();
            platforms.push_back(Platform(340, GROUND_Y - (SCREEN_HEIGHT / 3.0f)));
        }

        // 6. Memory Cleanup
        if (platforms.size() > 25) platforms.erase(platforms.begin());

        // 7. Rendering
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTex, NULL, NULL);
        
        // Render ground only if it's visible within the camera view
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