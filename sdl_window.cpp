#include <SDL2/SDL.h>
#include <iostream>

#define WINDOW_WIDTH 1080
#define WINDOW_HEIGHT 1920

bool running, fullscreen;

SDL_Renderer* renderer;
SDL_Window* window;

int framesCount, timerFPS, lastFrame, fps;

void update(){

}
void input(){

}
void draw(){

}

int main(){
    running = true;
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) std::cout << "Failed at SDL_Init()" << std::endl;
    
    if(SDL_CreateWindowAndRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, 0, &window, &renderer) < 0) std::cout << "Failed at SDL_CreateWindowAndRenderer()" << std::endl;

    SDL_ShowCursor(1);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2");

    while(running){
        update();
        input();
        draw();
    }
    return 0;
}