#ifndef DOMAIN_TILE_H
#define DOMAIN_TILE_H

/* What kind of thing the player's hitbox touched, classified from the two
 * level-grid tile characters go() (deplacement_joueur.c) checks (its
 * test1/test2 corners). Priority order matches the original if/else-if
 * chain exactly: a tile that happened to match more than one kind (never
 * happens with this level format, since each character is exclusive) would
 * resolve in this same order. '0' means empty/no tile. */
typedef enum {
    DOMAIN_TILE_NONE,            /* both corners are '0': no collision at all */
    DOMAIN_TILE_SPIKE,           /* '9': instant death */
    DOMAIN_TILE_COIN,            /* '2': collectible, only consumed on an upward hit */
    DOMAIN_TILE_VICTORY_OBJECT,  /* 'O': the mushroom/star-equivalent pickup */
    DOMAIN_TILE_FLAGPOLE,        /* 'S': end-of-level flag */
    DOMAIN_TILE_SOLID            /* anything else non-'0': plain blocking tile */
} domain_tile_kind_t;

domain_tile_kind_t domain_classify_tile(char tile1, char tile2);

#endif
