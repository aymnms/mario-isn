#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

extern SDL_Window *window;
extern SDL_Renderer *renderer;

void init_display();
void cleanup_display();

#endif