#include <SDL2/SDL.h>
#include <iostream>

// Configuration Constants
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;
const char* WINDOW_TITLE = "SDL2 Game Engine v0.1";

int main(int argc, char* argv[]) {
    // 1. INITIALIZATION
    // Initialize SDL video subsystem. Returns < 0 on failure.
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // 2. CREATE WINDOW
    // We create the window centered on screen.
    SDL_Window* window = SDL_CreateWindow(
        WINDOW_TITLE,
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH, WINDOW_HEIGHT,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // 3. CREATE RENDERER
    // The renderer is the GPU context. We use hardware acceleration and VSync.
    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, 
        -1, // Initialize the first supported rendering driver
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    if (!renderer) {
        std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // 4. SETUP FOR DELTA TIME
    // SDL uses a high performance counter for precise timing
    Uint64 lastCount = SDL_GetPerformanceCounter();
    Uint64 performanceFrequency = SDL_GetPerformanceFrequency();
    float deltaTime = 0.0f;

    // 5. THE GAME LOOP
    bool isRunning = true;
    SDL_Event event;

    while (isRunning) {
        // --- A. CALCULATE DELTA TIME ---
        Uint64 currentCount = SDL_GetPerformanceCounter();
        // Calculate the difference and divide by frequency to get seconds
        deltaTime = (float)(currentCount - lastCount) / (float)performanceFrequency;
        lastCount = currentCount;

        // --- B. EVENT POLLING ---
        // SDL_PollEvent returns 0 when there are no more events to process
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
            else if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
            }
        }

        // --- C. UPDATE LOGIC ---
        // player.x += speed * deltaTime;

        // --- D. RENDER PHASE ---
        
        // 1. Clear the screen (Set draw color to black first)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // R, G, B, Alpha
        SDL_RenderClear(renderer);

        // 2. Draw Game Objects
        // Example: Drawing a red rectangle
        /*
        SDL_Rect rect = { 100, 100, 50, 50 }; // x, y, w, h
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderFillRect(renderer, &rect);
        */

        // 3. Swap Buffers (Show the frame)
        SDL_RenderPresent(renderer);
    }

    // 6. CLEANUP
    // In C/SDL2, you must manually destroy what you create to avoid memory leaks.
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}