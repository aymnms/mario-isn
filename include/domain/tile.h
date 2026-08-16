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

/* True if any of the four sampled tile characters is a plain solid block
 * ('1'). Used by goB() (bowser.c), which samples 4 corners instead of go()/
 * goM()'s 2 -- unlike domain_classify_tile(), which pairs two corners and
 * lets a higher-priority kind (spike, coin...) at one corner mask a solid
 * block at the other, this checks each corner independently so a '1' at any
 * of the 4 points is never hidden by a different tile kind at another. */
int domain_any_solid_tile(char t1, char t2, char t3, char t4);

#endif
