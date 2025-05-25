#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "MARIO_joueur.h"

extern SDL_Surface *perso, *img;
extern int emp;
extern int bool_droite, bool_gauche;
extern int temps;
int test_bas;

void animation() {
	test_bas = go('B');
	if (test_bas == 0) //si le perso ne touche pas le sol
		{  if (bool_droite == 1 || bool_gauche == 1)
			{
				if (bool_droite == 1)
				{ 
					perso = IMG_Load("../img/mario_saut_droite.bmp");
				}
				else
				{
					perso = IMG_Load("../img/mario_saut_gauche.bmp");
				}
			}
			else if (emp == 0)
			{
				perso = IMG_Load("../img/mario_saut_droite.bmp");
			}
			else
			{
				perso = IMG_Load("../img/mario_saut_gauche.bmp");
			}
		}
	else if (bool_droite == 1 || bool_gauche == 1) // si le perso touche le sol et qu'une touche est appuyée
	{
		
		if ( bool_gauche == 1 /* && go('G') == 0*/) {

			printf("anim course gauche \n");
		
			if (temps == 0){
				temps  = SDL_GetTicks(); // on donne à la variable temps le nombre de miiseconde deuis le début du programme
				perso = IMG_Load("../img/frame_1_gauche.bmp"); //frame 1
			}

			if(temps + 100 <= SDL_GetTicks())//si la var temps +100 msec est inferieure au nb de ms depuis lme début du programme
			{
				perso = IMG_Load("../img/frame_2_gauche.bmp"); //frame 2
			}
			if(temps + 200 <= SDL_GetTicks()){
				perso = IMG_Load("../img/frame_3_gauche.bmp"); //frame 3
				temps = 0; //on remet la variable temps à 0 pour recommencer l'annimation
			}


		}

		else if (bool_droite == 1)
		{
			//anim de course
			printf("anim course droite \n");
			

			if (temps == 0){
				temps  = SDL_GetTicks(); // on donne à la variable temps le nombre de miiseconde deuis le début du programme
				perso = IMG_Load("../img/frame_1_droite.bmp"); //frame 1
			}

			if(temps + 100 <= SDL_GetTicks())//si la var temps +100 msec est inferieure au nb de ms depuis lme début du programme
			{
				perso = IMG_Load("../img/frame_2_droite.bmp"); //frame 2
			}
			if(temps + 200 <= SDL_GetTicks()){
				perso = IMG_Load("../img/frame_3_droite.bmp"); //frame 3
				temps = 0; //on remet la variable temps à 0 pour recommencer l'annimation
			}



		}
	}
	else if ( bool_gauche == 0 && bool_droite == 0) //si le perso touche le sol et qu'aucune touche n'est appuyée
	{
		if ( emp == 0)
		{
			perso = IMG_Load("../img/mario_idle.bmp");
		}
		else
		{
			perso = IMG_Load("../img/mario_idle_gauche.bmp");
		}
	}
	SDL_SetColorKey(perso, SDL_TRUE, SDL_MapRGB(perso->format, 255, 255, 255));//transparence d'une couleur (blanc)
}