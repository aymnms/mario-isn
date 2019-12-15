/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxREFRESH_MECHANT.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void afficher_mechant()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>


//--------------------------Variable-générale--------------------------//
extern SDL_Surface *background;
extern int decalage;
extern char statue[20];
extern SDL_Surface *imgMechant; //surface du mechant
extern SDL_Rect tableau_mechant[20][4]; 
extern int nb_mechant;
//---------------------------------------------------------------------//


void afficher_mechant(){
	if(statue[nb_mechant] == 'V'){ //SI LE MECHANT EST VIVANT
		imgMechant = SDL_LoadBMP("./img/goomba.bmp"); //on définit l'image du mechant
		SDL_SetColorKey(imgMechant, SDL_SRCCOLORKEY, SDL_MapRGB(imgMechant->format, 255, 255, 255));//transparence d'une couleur
	}else if(statue[nb_mechant] == 'M'){
		imgMechant = SDL_LoadBMP("./img/goomba_mort.bmp"); //on définit l'image du mechant
		SDL_SetColorKey(imgMechant, SDL_SRCCOLORKEY, SDL_MapRGB(imgMechant->format, 255, 255, 255));//transparence d'une couleur
	}else if(statue[nb_mechant] == 'B'){//si c'est un champignon
		imgMechant = SDL_LoadBMP("./img/bowser.bmp");
		SDL_SetColorKey(imgMechant, SDL_SRCCOLORKEY, SDL_MapRGB(imgMechant->format, 0,0,0));//transparence d'une couleur
	}else if(statue[nb_mechant] == '0'){
		imgMechant = SDL_LoadBMP("./img/void.bmp");
	}else if(statue[nb_mechant] == 'U'){
		imgMechant = SDL_LoadBMP("./img/bowserMort.bmp");
		SDL_SetColorKey(imgMechant, SDL_SRCCOLORKEY, SDL_MapRGB(imgMechant->format, 0,0,0));//transparence d'une couleur
	}

	

	tableau_mechant[nb_mechant][3] = tableau_mechant[nb_mechant][1];
	tableau_mechant[nb_mechant][3].x -= decalage;
	SDL_BlitSurface(imgMechant, NULL, background, &tableau_mechant[nb_mechant][3]); //on demande l'affichage du mechant	
}