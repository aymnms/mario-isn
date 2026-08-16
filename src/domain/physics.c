#include "domain/physics.h"

double domain_jump_arc(double i) {
    return -i * i + 22 * i;
}

double domain_on_enemy_jump_arc(double i) {
    return -i * i + 15 * i;
}

double domain_jump_threshold(int on_enemy) {
    return on_enemy ? 7.0 : 11.0;
}

int domain_jump_should_end(int jump, int on_enemy, int blocked_above, double x) {
    if (jump != 1) {
        return 0;
    }
    if (blocked_above == 1) {
        return 1;
    }
    return x >= domain_jump_threshold(on_enemy);
}

int domain_chute_should_start(int jump, int chute, int blocked_below) {
    return jump == 0 && chute == 0 && blocked_below == 0;
}

int domain_chute_is_active(int chute, int blocked_below, int on_enemy, double x) {
    return chute == 1 && blocked_below == 0 && x >= domain_jump_threshold(on_enemy);
}

int domain_chute_should_end(int chute, int blocked_below) {
    return chute == 1 && blocked_below == 1;
}
