/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxINIT_MENU.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void init_fenetre()
void init_menu()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include "headers/MARIO_musique.h"

//--------Variable-generale--------//
extern SDL_Rect origine;
extern SDL_Surface *img, *background;
//---------------------------------//

void init_fenetre(){
    init_mus();
    origine.x = 0; //on définit l'origine de la fenetre
    origine.y = 0;
    img = SDL_LoadBMP("./img/menu.bmp");
    background = SDL_SetVideoMode(600, 500, 32, SDL_HWSURFACE| SDL_DOUBLEBUF); //on definit la taille, le nombre d'ips et le type de la fenetre "background" ET SDL_DOUBLEBUF POUR LA MUSIQUE

    SDL_Init(SDL_INIT_VIDEO); //charge le system d'affichage de  la SDL en m�moire
    SDL_WM_SetIcon(SDL_LoadBMP("./img/sdl_icone.bmp"), NULL);
    SDL_ShowCursor(SDL_ENABLE);
    SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre
    SDL_WM_SetCaption("Super Mario Bros", NULL); // nom de la fenetre, on garde NULL parcequ'on est sur Windows

    SDL_Flip(background); //Mise � jour de l'�cran
}

void init_menu(){ //gère l'organisation de l'execution des fonctions
    init_fenetre();
}