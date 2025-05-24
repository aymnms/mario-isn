#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "display.h"
#include "MARIO_niveau.h"


extern SDL_Surface *perso, *img, *background;
extern SDL_Rect pos_perso, origine;

extern int decalage;
extern int emp;
extern int coin, niveau, vie;

extern int jump, chute; //saut
extern int bool_droite, bool_gauche, bool_saut;
extern int bool_saut_sur_mechant;

extern SDL_Surface *imgMechant;
extern char statue[10];
extern int direction_mechant[10];
extern SDL_Rect tableau_mechant[10][4];

SDL_Rect pos_barre, pos_noir, pos_cadre, pos_champi;
SDL_Surface *barre, *noir, *cadre, *champi;
int decoule;


void init_niveau() {
    init_skin();
    origine.x = 0; origine.y = 0; decalage = 0;
    bool_droite = 0, bool_gauche = 0, bool_saut = 0, bool_saut_sur_mechant = 0;
    jump = 0; chute = 0;
    emp = 0;
    perso = IMG_Load("../img/mario_idle.bmp");

    SDL_SetColorKey(perso, SDL_TRUE, SDL_MapRGB(perso->format, 255, 255, 255));
    SDL_SetColorKey(perso, SDL_TRUE, SDL_MapRGB(perso->format, 255, 255, 255)); //transparence d'une couleur

    SDL_Texture *texture_perso = SDL_CreateTextureFromSurface(renderer, perso);
    SDL_FreeSurface(perso);


    pos_perso.x = 50; // coordonn�s en x
    pos_perso.y = 100;// coordonn�s en y

    SDL_RenderCopy(renderer, texture_perso, NULL, &pos_perso);
    SDL_ShowCursor(SDL_FALSE); //enleve le cusrseur dans la fenetre
}



void init_timer (){
    pos_barre.x = 400;
    pos_barre.y = 0;
    barre = IMG_Load ("../img/barre.bmp");
    pos_noir.x = 600;
    pos_noir.y = 0;
    noir = IMG_Load ("../img/noir.bmp");
    pos_cadre.x = 400;
    pos_cadre.y = 0;
    cadre = IMG_Load ("../img/cadre.bmp");
    decoule = 600;
    SDL_SetColorKey(cadre, SDL_TRUE, SDL_MapRGB(cadre->format, 255, 255, 255));//transparence d'une couleur
}



void init_game(){
    niveauSelect(niveau);
    init_niveau();
    init_timer();
}