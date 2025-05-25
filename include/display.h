#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void init_display();
// void cleanup_display();
void display_texture(SDL_Texture *texture, SDL_Rect *src, SDL_Rect *dest);
void clear_screen();
void present_screen();

#endif