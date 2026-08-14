#include "domain/collision.h"

int domain_contact_lateral(SDL_Rect player_pos, int decalage, SDL_Rect enemy_pos) {
    int px = player_pos.x + decalage;

    int touches_x = ((px + 39 >= enemy_pos.x) && (px + 39 <= enemy_pos.x + 2)) ||
                     ((px <= enemy_pos.x + 40) && (px >= enemy_pos.x + 38));
    int touches_y =
        (player_pos.y >= enemy_pos.y - 45) && (player_pos.y <= enemy_pos.y + 45);

    return touches_x && touches_y;
}

int domain_lands_on_top(SDL_Rect player_pos, int decalage, SDL_Rect enemy_pos) {
    int px = player_pos.x + decalage;

    int touches_x = (px >= enemy_pos.x - 49) && (px <= enemy_pos.x + 48);
    int touches_y = ((player_pos.y + 50) >= (enemy_pos.y - 5)) &&
                     ((player_pos.y + 50) <= (enemy_pos.y + 5));

    return touches_x && touches_y;
}
