#ifndef DOMAIN_GRID_H
#define DOMAIN_GRID_H

#include <SDL.h>

/* Converts a pixel-space point (with an optional horizontal scroll offset
 * added first) into a level-grid cell, by dividing by the 50px tile size. */
SDL_Rect domain_to_grid_cell(SDL_Rect point, int offset);

/* Clamps a grid cell (e.g. from domain_to_grid_cell) into [0, rows) x
 * [0, cols): a pixel position past the edge of the level (the scroll/
 * position limits that bound player and enemy movement are looser than the
 * level grid's own dimensions, and can compute a cell just past its last
 * valid row/column) still needs a safe, in-bounds cell to index into the
 * level grid with. */
SDL_Rect domain_clamp_to_grid(SDL_Rect cell, int rows, int cols);

#endif
