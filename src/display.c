#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

// a terme, on pourrait supprimer *src car on le met constamment à NULL
void display_texture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest) {
    if (dest != NULL) {
        SDL_QueryTexture(texture, NULL, NULL, &dest->w, &dest->h);
    }
    SDL_RenderCopy(renderer, texture, src, dest);
}

void update_texture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest) {
    clear_screen();
    display_texture(texture, src, dest);
    present_screen();
}

SDL_Texture *create_texture(char *surface_path) {
    SDL_Surface *img = IMG_Load(surface_path);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img);
    return texture;
}



// void cleanup_display() {
//     SDL_DestroyRenderer(renderer);
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }
