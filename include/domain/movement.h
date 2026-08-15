#ifndef DOMAIN_MOVEMENT_H
#define DOMAIN_MOVEMENT_H

/* Given an enemy's current horizontal direction (+1 or -1) and whether an
 * obstacle blocks that direction, returns the direction it should move in
 * next: unchanged if clear, flipped if blocked. Shared by goomba and Bowser
 * movement (deplacement_mechant.c), which differ only in how they detect
 * the obstacle, not in what to do about it. */
int domain_next_direction(int current_direction, int obstacle_ahead);

/* What droite()/gauche() (deplacement_joueur.c) should do given the
 * player's current x position and the world's horizontal scroll offset:
 * scroll the world (player stays put on screen, level moves), move the
 * player's own sprite, or neither (past a screen-edge deadzone). */
typedef enum {
    DOMAIN_SCROLL_ACTION_NONE,
    DOMAIN_SCROLL_ACTION_SCROLL_WORLD,
    DOMAIN_SCROLL_ACTION_MOVE_SPRITE
} domain_scroll_action_t;

domain_scroll_action_t domain_scroll_right_action(int pos_x, int decalage);
domain_scroll_action_t domain_scroll_left_action(int pos_x, int decalage);

#endif
