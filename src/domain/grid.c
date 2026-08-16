#include "domain/grid.h"

SDL_Rect domain_to_grid_cell(SDL_Rect point, int offset) {
    SDL_Rect cell;

    cell.x = (point.x + offset) / 50;
    cell.y = point.y / 50;

    return cell;
}

SDL_Rect domain_clamp_to_grid(SDL_Rect cell, int rows, int cols) {
    if (cell.x < 0) {
        cell.x = 0;
    } else if (cell.x >= cols) {
        cell.x = cols - 1;
    }

    if (cell.y < 0) {
        cell.y = 0;
    } else if (cell.y >= rows) {
        cell.y = rows - 1;
    }

    return cell;
}
