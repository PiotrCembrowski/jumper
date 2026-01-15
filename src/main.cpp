#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Player.h"
#include "Ground.h"
#include "Platform.h"
#include "Config.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Dino Jumper", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Texture* mortTex = IMG_LoadTexture(renderer, "assets/img/mort.png");
    SDL_Texture* bgTex = IMG_LoadTexture(renderer, "assets/img/background/plx-1.png");
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "assets/img/background/ground.png");
    SDL_Texture* platTex = IMG_LoadTexture(renderer, "assets/img/background/plx-3.png"); // Use a small cloud or brick

    Player player(400, 300);
    Ground ground;
    
    // Create a few test platforms
    std::vector<Platform> platforms;
    platforms.push_back(Platform(300, 400));
    platforms.push_back(Platform(500, 300));
    platforms.push_back(Platform(200, 200));

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) { if (e.type == SDL_QUIT) running = false; }

        player.handleInput();
        player.update(platforms);

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, bgTex, NULL, NULL);
        ground.draw(renderer, groundTex);
        
        for (auto& p : platforms) p.draw(renderer, platTex);
        
        player.draw(renderer, mortTex);
        SDL_RenderPresent(renderer);
    }
    // ... Cleanup ...
    return 0;
}