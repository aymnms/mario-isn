#include "domain/physics.h"

double domain_jump_arc(double i) {
    return -i * i + 22 * i;
}

double domain_on_enemy_jump_arc(double i) {
    return -i * i + 15 * i;
}
