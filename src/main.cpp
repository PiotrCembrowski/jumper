#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "Ground.h"
#include "Config.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window* window = SDL_CreateWindow("Dino Jumper", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Load Textures
// Change these lines in main.cpp:
    SDL_Texture* mortTex = IMG_LoadTexture(renderer, "assets/img/mort.png");
    SDL_Texture* bgTex = IMG_LoadTexture(renderer, "assets/img/background/plx-1.png"); // Using plx-1 as example
    SDL_Texture* groundTex = IMG_LoadTexture(renderer, "assets/img/background/ground.png");

    Player player(400, 100); // Start player higher up
    Ground ground;

    bool running = true;
    SDL_Event e;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) running = false;
        }

        player.handleInput();
        player.update();

        SDL_RenderClear(renderer);

        // Render order: Background -> Ground -> Player
        SDL_RenderCopy(renderer, bgTex, NULL, NULL);
        ground.draw(renderer, groundTex);
        player.draw(renderer, mortTex);

        SDL_RenderPresent(renderer);
    }

    // Cleanup
    SDL_DestroyTexture(mortTex);
    SDL_DestroyTexture(bgTex);
    SDL_DestroyTexture(groundTex);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    return 0;
}