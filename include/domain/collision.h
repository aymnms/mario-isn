#ifndef DOMAIN_COLLISION_H
#define DOMAIN_COLLISION_H

#include <SDL.h>

/* True if the player's hitbox (offset by the horizontal scroll) touches the
 * enemy's hitbox from the side (left or right edge). */
int domain_contact_lateral(SDL_Rect player_pos, int decalage, SDL_Rect enemy_pos);

/* True if the player's feet land within the enemy's top surface (offset by
 * the horizontal scroll), i.e. the player is stomping the enemy. */
int domain_lands_on_top(SDL_Rect player_pos, int decalage, SDL_Rect enemy_pos);

#endif
