#include <SDL2/sdl.h>
#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
SDL_Texture *texture_background = NULL;

void init_display() {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow("Super Mario ISN",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              600, 500, SDL_WINDOW_SHOWN);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
}

void present_screen() {
    SDL_RenderPresent(renderer);
}

void clear_screen() {
    SDL_RenderClear(renderer);
}

void display_texture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest) {
    SDL_RenderCopy(renderer, texture, src, dest);
}

// void cleanup_display() {
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }
