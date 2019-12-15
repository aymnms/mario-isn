#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "Headers/main.h"
#include "Headers/GAME.h"
#include "headers/mechant.h"

extern SDL_Surface *background;
extern int coin, vie;

SDL_Surface *coinmeter, *coinnb;
SDL_Rect pos_coinmeter, pos_coinnb;

void init_coin(){
pos_coinmeter.x = 0;
pos_coinmeter.y = 80;
coinmeter = SDL_LoadBMP("./img/coinx.bmp");
SDL_SetColorKey(coinmeter, SDL_SRCCOLORKEY, SDL_MapRGB(coinmeter->format, 0, 0, 0));

pos_coinnb.x = 70;
pos_coinnb.y = 80;
}

void coin(){
switch (coin){

	case '0' : 
	coinnb = SDL_LoadBMP("./img/zero.bmp");
	break;

	case '1' : 
	coinnb = SDL_LoadBMP("./img/un.bmp");
	break;
	
	case '2' : 
	coinnb = SDL_LoadBMP("./img/deux.bmp");
	break;
	
	case '3' : 
	coinnb = SDL_LoadBMP("./img/trois.bmp");
	break;
	
	case '4' : 
	coinnb = SDL_LoadBMP("./img/quatre.bmp");
	break;
	
	case '5' : 
	coinnb = SDL_LoadBMP("./img/cinq.bmp");
	break;
	
	case '6' : 
	coinnb = SDL_LoadBMP("./img/six.bmp");
	break;
	
	case '7' : 
	coinnb = SDL_LoadBMP("./img/sept.bmp");
	break;
	
	case '8' : 
	coinnb = SDL_LoadBMP("./img/huit.bmp");
	break;
	
	case '9' : 
	coinnb = SDL_LoadBMP("./img/neuf.bmp");
	break;
	
}

if (coin == 10)
{
	vie++;
}

SDL_SetColorKey(coinnb, SDL_SRCCOLORKEY, SDL_MapRGB(coinnb->format, 0, 0, 0));
}
