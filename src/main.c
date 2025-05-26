#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "display.h"
#include "MARIO_menu.h"
#include "MARIO_game.h"
#include "MARIO_niveau.h"


int run = 1, run_game = 1;
int niveau = 1;
int vie = 3;
int coin = 0;
int vic = 0;

SDL_Rect tableau_mechant[20][4]; //tous les points pour les mechants
SDL_Texture *imgMechant;
char statue[20] ={'0','0','0','0','0','0','0','0','0','0'}; //mechant mort ou vivant
int direction_mechant[20]; //tout est dans le nom
int nb_mechant; //numéro du méchant à dont c'est le tour (voire game_runer.c)

SDL_Rect origine, pos_perso, pos_mechant; //point pour positionner les elements
SDL_Texture *perso = NULL, *img = NULL; //les surfaces pour les images sauf pour celle des mechants
SDL_Event event; //stock les événements

int bool_droite = 0, bool_gauche = 0, bool_saut = 0, bool_saut_sur_mechant = 0;
int decalage; //strawling
int jump, chute;
int init_hauteur_saut, init_hauteur_chute;
double x = 0;

int emp = 0;
int temps = 0;
char lvl[10][140];


int main(int argc, char *argv[]){
    printf("Hello World\n");
    // while(run){
    	init_menu(); //envoie sur "init_menu.c" par "init_menu.h"
        MENU(); //envoie sur "MENU.c" par "MENU.h"
    	if(run_game){
            // init_game();
            GAME();
        }
    // }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void quit_game(){ //lorsque le joueur souhaite quitter le niveau du jeu -> redirection Menu
    run_game = 0;
}
void quit(){ //QUITTE TOTALEMENT LE PROGRAMME
    run = 0;
    run_game = 0;
}