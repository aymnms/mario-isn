#include "domain/movement.h"

int domain_next_direction(int current_direction, int obstacle_ahead) {
    return obstacle_ahead ? -current_direction : current_direction;
}

domain_scroll_action_t domain_scroll_right_action(int pos_x, int decalage) {
    if (pos_x >= 250 && decalage < 6700) {
        return DOMAIN_SCROLL_ACTION_SCROLL_WORLD;
    }
    if (pos_x < 500) {
        return DOMAIN_SCROLL_ACTION_MOVE_SPRITE;
    }
    return DOMAIN_SCROLL_ACTION_NONE;
}

domain_scroll_action_t domain_scroll_left_action(int pos_x, int decalage) {
    if (pos_x <= 50 && decalage > 0) {
        return DOMAIN_SCROLL_ACTION_SCROLL_WORLD;
    }
    if (pos_x > 0) {
        return DOMAIN_SCROLL_ACTION_MOVE_SPRITE;
    }
    return DOMAIN_SCROLL_ACTION_NONE;
}
