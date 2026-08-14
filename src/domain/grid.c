#include "domain/grid.h"

SDL_Rect domain_to_grid_cell(SDL_Rect point, int offset) {
    SDL_Rect cell;

    cell.x = (point.x + offset) / 50;
    cell.y = point.y / 50;

    return cell;
}
