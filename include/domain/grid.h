#ifndef DOMAIN_GRID_H
#define DOMAIN_GRID_H

#include <SDL.h>

/* Converts a pixel-space point (with an optional horizontal scroll offset
 * added first) into a level-grid cell, by dividing by the 50px tile size. */
SDL_Rect domain_to_grid_cell(SDL_Rect point, int offset);

#endif
