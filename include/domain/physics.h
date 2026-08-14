#ifndef DOMAIN_PHYSICS_H
#define DOMAIN_PHYSICS_H

/* Jump arc height at progress `i` (frames since jump start) for a normal
 * jump: parabola -i^2 + 22i, zero at i=0 and i=22, peak 121 at i=11. */
double domain_jump_arc(double i);

/* Jump arc height at progress `i` for a jump taken from bouncing on an
 * enemy: parabola -i^2 + 15i, zero at i=0 and i=15, peak 56.25 at i=7.5. */
double domain_on_enemy_jump_arc(double i);

#endif
