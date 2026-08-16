#include "domain/tile.h"

domain_tile_kind_t domain_classify_tile(char tile1, char tile2) {
    if (tile1 == '9' || tile2 == '9') {
        return DOMAIN_TILE_SPIKE;
    }
    if (tile1 == '2' || tile2 == '2') {
        return DOMAIN_TILE_COIN;
    }
    if (tile1 == 'O' || tile2 == 'O') {
        return DOMAIN_TILE_VICTORY_OBJECT;
    }
    if (tile1 == 'S' || tile2 == 'S') {
        return DOMAIN_TILE_FLAGPOLE;
    }
    if (tile1 != '0' || tile2 != '0') {
        return DOMAIN_TILE_SOLID;
    }
    return DOMAIN_TILE_NONE;
}

int domain_any_solid_tile(char t1, char t2, char t3, char t4) {
    return t1 == '1' || t2 == '1' || t3 == '1' || t4 == '1';
}
