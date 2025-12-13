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
    while(running){
        update();
        input();
        draw();
    }
    return 0;
}