#ifndef DOMAIN_PHYSICS_H
#define DOMAIN_PHYSICS_H

/* Jump arc height at progress `i` (frames since jump start) for a normal
 * jump: parabola -i^2 + 22i, zero at i=0 and i=22, peak 121 at i=11. */
double domain_jump_arc(double i);

/* Jump arc height at progress `i` for a jump taken from bouncing on an
 * enemy: parabola -i^2 + 15i, zero at i=0 and i=15, peak 56.25 at i=7.5. */
double domain_on_enemy_jump_arc(double i);

/* The `i` progress value at which a jump's rising phase ends (mirrors the
 * arc's own duration: 11 for a normal jump, 7 for an enemy-bounce jump --
 * asymmetric on purpose, matches the original code exactly rather than the
 * arc's true root at 7.5). Used at the 3 saut_joueur.c call sites that
 * previously duplicated this threshold as a literal 11 or 7 depending on
 * bool_saut_sur_mechant. */
double domain_jump_threshold(int on_enemy);

/* True once a jump in progress (jump==1) should end: hit a ceiling
 * (blocked_above), or the rising phase ran its full duration for the kind
 * of jump this is (on_enemy picks the 7 vs 11 threshold above). Mirrors
 * saut()'s end-of-jump `if` in saut_joueur.c exactly. */
int domain_jump_should_end(int jump, int on_enemy, int blocked_above, double x);

/* True when standing still (jump==0, chute==0) with nothing underfoot
 * (blocked_below==0): gravity should start pulling the player down.
 * Mirrors gravite()'s chute-initialization `if` in saut_joueur.c. */
int domain_chute_should_start(int jump, int chute, int blocked_below);

/* True while a fall in progress (chute==1) is still clear of the ground
 * (blocked_below==0) and has run at least `domain_jump_threshold(on_enemy)`
 * progress -- i.e. it's safe to keep advancing the fall arc. Mirrors
 * gravite()'s two (mechant-bounce vs normal) falling-active `if`s. */
int domain_chute_is_active(int chute, int blocked_below, int on_enemy, double x);

/* True once a fall in progress (chute==1) has landed (blocked_below==1):
 * gravity should stop. Mirrors gravite()'s landing `if`. */
int domain_chute_should_end(int chute, int blocked_below);

#endif
