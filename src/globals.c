// globals.c
#include "globals.h"
double x = 0;
int decoule, emp = 0, temps = 0;
char lvl[10][140];           // ou le bon type réel
SDL_Rect pos_cadre, pos_noir, pos_barre;
SDL_Texture *cadre, *noir, *barre; // selon les vrais types
SDL_Texture *perso = NULL, *img = NULL; //les surfaces pour les images sauf pour celle des mechants
