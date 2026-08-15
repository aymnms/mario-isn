#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h

#include "MARIO_mechant.h"
#include "domain/grid.h"
#include "domain/movement.h"
#include "globals.h"

//--------------------------Variable-générale--------------------------//
extern int direction_mechant[MAX_MECHANTS]; //le mechant commence par aller à droite
extern char statue[MAX_MECHANTS];
extern SDL_Rect tableau_mechant[MAX_MECHANTS][4];
extern int nb_mechant;
int boolSB = 0;
int taille = 150;

//---------------------------------------------------------------------//

SDL_Rect setRectMechant(SDL_Rect Point) { //on place le point sur la grille
    return domain_to_grid_cell(Point, 0);
}

void deplacement_mechant(void) {

    srand(time(NULL));
    if (statue[nb_mechant] == 'V') {
        // Reverse direction if blocked ahead -- or, for goombas specifically,
        // also if x==0 (an inactive/never-placed slot; see addMechant()).
        // Preserved as-is from the original `goM(...) != 1 && x != 0` guard.
        int obstacle_ahead =
            (goM(direction_mechant[nb_mechant]) == 1) || (tableau_mechant[nb_mechant][1].x == 0);
        direction_mechant[nb_mechant] =
            domain_next_direction(direction_mechant[nb_mechant], obstacle_ahead);
        tableau_mechant[nb_mechant][1].x += direction_mechant[nb_mechant]; //on déplace le méchant
        if (goM(666) != 1) {                    // si il y a un trou sous le mechant
            tableau_mechant[nb_mechant][1].y++; //le mechant tombe
        }

    } else if (statue[nb_mechant] == 'B') {
        int obstacle_ahead = goB(direction_mechant[nb_mechant]) == 1;
        direction_mechant[nb_mechant] =
            domain_next_direction(direction_mechant[nb_mechant], obstacle_ahead);

        tableau_mechant[nb_mechant][1].x += direction_mechant[nb_mechant]; //on déplace le méchant
        if (goB(666) != 1) {                    // si il y a un trou sous le mechant
            tableau_mechant[nb_mechant][1].y++; //le mechant tombe
        }
    }
}