#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "display.h"

extern int decalage;
extern char statue[20];
extern SDL_Texture *imgMechant; //surface du mechant
extern SDL_Rect tableau_mechant[20][4]; 
extern int nb_mechant;

void afficher_mechant(){
	if(statue[nb_mechant] == 'V'){ //SI LE MECHANT EST VIVANT
		imgMechant = create_texture("../img/goomba.png"); //on définit l'image du mechant
	}else if(statue[nb_mechant] == 'M'){
		imgMechant = create_texture("../img/goomba_mort.png"); //on définit l'image du mechant
	}else if(statue[nb_mechant] == 'B'){//si c'est un champignon
		imgMechant = create_texture("../img/bowser.png");
	}else if(statue[nb_mechant] == '0'){
		imgMechant = create_texture("../img/void.png");
	}else if(statue[nb_mechant] == 'U'){
		imgMechant = create_texture("../img/bowserMort.png");
	}

	

	tableau_mechant[nb_mechant][3] = tableau_mechant[nb_mechant][1];
	tableau_mechant[nb_mechant][3].x -= decalage;

	// ALORS
	display_texture(imgMechant, NULL, &tableau_mechant[nb_mechant][3]);
}