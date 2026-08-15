#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <time.h> //Ne pas oublier d'inclure le fichier time.h

#include "MARIO_mechant.h"
#include "domain/grid.h"
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
        if (goM(direction_mechant[nb_mechant]) != 1 &&
            tableau_mechant[nb_mechant][1].x != 0) { //si le mechant ne rencontre pas d'obstacle
                                                     //c'est normal qu'il n'y ai rien pour le moment
        } else {
            direction_mechant[nb_mechant] =
                -direction_mechant[nb_mechant]; //on change la direction du mechant
        }
        tableau_mechant[nb_mechant][1].x += direction_mechant[nb_mechant]; //on déplace le méchant
        if (goM(666) != 1) {                    // si il y a un trou sous le mechant
            tableau_mechant[nb_mechant][1].y++; //le mechant tombe
        }

    } else if (statue[nb_mechant] == 'B') {
        if (goB(direction_mechant[nb_mechant]) == 1) { //si le mechant ne rencontre pas d'obstacle
            direction_mechant[nb_mechant] =
                -direction_mechant[nb_mechant]; //on change la direction du mechant
        }

        //int po = rand()%2;
        tableau_mechant[nb_mechant][1].x += direction_mechant[nb_mechant]; //on déplace le méchant
        if (goB(666) != 1) {                    // si il y a un trou sous le mechant
            tableau_mechant[nb_mechant][1].y++; //le mechant tombe
        }

        /*else if(po == 1){boolSB = 1;}
		if (boolSB == 1)
		{
			
			//boolSB = 1;printf("%d,%d : c'est commeee l'oiseau...\n", tableau_mechant[nb_mechant][1].x, tableau_mechant[nb_mechant][1].y);
			//if(taille > 0){tableau_mechant[nb_mechant][1].y --; taille--;}
			else{taille = 150; boolSB = 0;}
		} */
    }
}