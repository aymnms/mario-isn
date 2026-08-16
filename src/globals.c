// globals.c
#include "globals.h"
double x = 0;
int decoule, emp = 0;
// SDL_GetTicks()'s own return type: temps is only ever assigned from it,
// reset to 0, or compared against it -- matching the type avoids a signed/
// unsigned comparison mismatch instead of just silencing it with casts.
Uint32 temps = 0;
char lvl[LVL_ROWS][LVL_COLS];
SDL_Rect pos_cadre, pos_noir, pos_barre;
SDL_Texture *cadre, *noir, *barre;      // selon les vrais types
SDL_Texture *perso = NULL, *img = NULL; //les surfaces pour les images sauf pour celle des mechants
