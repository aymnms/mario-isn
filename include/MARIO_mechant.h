#pragma once

#include <SDL.h>

#include "globals.h"

// Shared mechant state (defined in main.c), needed by every file that reads
// or moves enemies/Bowser. Previously each of these files hand-typed its own
// `extern` copy of these 4 declarations (8 files for statue[]/
// tableau_mechant[][4] alone) instead of including a shared header -- the
// same scattering pattern that let statue[]/tableau_mechant[] silently drift
// to inconsistent array sizes across files before J5-3c caught it. A single
// declaration here means a future size/type change can't miss a copy.
extern char statue[MAX_MECHANTS];
extern SDL_Rect tableau_mechant[MAX_MECHANTS][4];
extern int direction_mechant[MAX_MECHANTS];
extern int nb_mechant;

void init_mechant(int ngh);

void afficher_mechant(void);

SDL_Rect setRectMechant(SDL_Rect Point);

void deplacement_mechant(void);

int goM(int direction);

void mechantMort(void);

void contact(void);

void addBowser(int pos_x, int pos_y);
int goB(int direction);
void contactB(void);