#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h> // Nowy nagłówek!
#include <iostream>

int main(int argc, char* argv[]) {
    // 1. Inicjalizacja SDL + SDL_image
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG); // Inicjalizacja wsparcia dla PNG i JPG

    SDL_Window* window = SDL_CreateWindow("Jumper Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    // 2. WCZYTYWANIE TEKSTURY TŁA
    // Załóżmy, że plik to assets/background.png
    SDL_Surface* tempSurface = IMG_Load("assets/background.png");
    if (!tempSurface) {
        std::cout << "Błąd wczytywania obrazu: " << IMG_GetError() << std::endl;
        return 1;
    }
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface); // Surface nie jest już potrzebny, mamy teksturę w pamięci GPU

    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
        }

        // --- RENDEROWANIE ---
        SDL_RenderClear(renderer);

        // Rysowanie tła na całym ekranie (NULL jako drugi i trzeci parametr)
        SDL_RenderCopy(renderer, backgroundTexture, NULL, NULL);

        SDL_RenderPresent(renderer);
    }

    // Sprzątanie
    SDL_DestroyTexture(backgroundTexture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}