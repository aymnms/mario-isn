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

extern double x;
extern int decoule, emp, temps;
extern char lvl[10][140];
extern SDL_Rect pos_cadre, pos_noir, pos_barre;
extern SDL_Texture *cadre, *noir, *barre;
extern SDL_Texture *perso, *img;
extern SDL_Texture *mario_idle_droite, *mario_saut_droite;
