// globals.h
#pragma once
#include <SDL.h>

// Real size of statue[]/tableau_mechant[][4]/direction_mechant[] (defined in
// main.c). Previously some files re-declared these `extern` at a smaller
// size ([10] instead of the real [20]) -- conflicting extern declarations
// of an array are undefined behavior per the C standard, even though it
// happened not to crash here (the actual storage was always the full [20]
// regardless of what a given file's extern claimed).
#define MAX_MECHANTS 20

// Real dimensions of lvl[][] (defined in globals.c). Player/enemy scroll and
// position limits (domain/movement.c) are looser than these -- at max
// scroll, collision checks can compute a grid column just past LVL_COLS-1 --
// so any code indexing lvl[][] from a computed cell must clamp against
// these first (see domain_clamp_to_grid()), not just trust the caller's
// scroll/position bounds to have kept it in range.
#define LVL_ROWS 10
#define LVL_COLS 140

extern double x;
extern int decoule, emp;
extern Uint32 temps;
extern char lvl[LVL_ROWS][LVL_COLS];
extern SDL_Rect pos_cadre, pos_noir, pos_barre;
extern SDL_Texture *cadre, *noir, *barre;
extern SDL_Texture *perso, *img;
extern SDL_Texture *mario_idle_droite, *mario_saut_droite;
