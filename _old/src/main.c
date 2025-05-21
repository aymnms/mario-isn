/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxMAIN.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int main(int argc, char *argv[])
void quit_game()
void quit()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h> //musique

#include "Headers/MARIO_menu.h"
#include "Headers/MARIO_game.h"
#include "Headers/MARIO_niveau.h"

//-------------------------------------------------Variable-générale-------------------------------------------------//
int run = 1, run_game = 1;
int niveau = 1;
int vie = 3;
int coin = 0;
int vic = 0;
//--------------------------------------------------Variable-mechant-------------------------------------------------//
SDL_Rect tableau_mechant[20][4]; //tous les points pour les mechants 
SDL_Surface *imgMechant;
char statue[20] ={'0','0','0','0','0','0','0','0','0','0'}; //mechant mort ou vivant
int direction_mechant[20]; //tout est dans le nom
int nb_mechant; //numéro du méchant à dont c'est le tour (voire game_runer.c)
//--------------------------------------------Variable-position-evennement-------------------------------------------//
SDL_Rect origine, pos_perso, pos_mechant; //point pour positionner les elements
SDL_Surface *background = NULL, *perso = NULL, *img = NULL; //les surfaces pour les images sauf pour celle des mechants
SDL_Event event; //stock les événements
//--------------------------------------------------Variable-saut----------------------------------------------------//
int bool_droite = 0, bool_gauche = 0, bool_saut = 0, bool_saut_sur_mechant = 0;
int decalage; //strawling
int jump, chute;
int init_hauteur_saut, init_hauteur_chute;
double x = 0;
//------------------------------------------------Variable-animation-------------------------------------------------//
int emp = 0;
int temps = 0;
char lvl[10][140];
//-------------------------------------------------------------------------------------------------------------------//

int main(int argc, char *argv[]){
    while(run){
    	init_menu(); //envoie sur "init_menu.c" par "init_menu.h"
        MENU(); //envoie sur "MENU.c" par "MENU.h"
    	if(run_game){
            //init_game();
            GAME();
        }
    }

    SDL_FreeSurface(img); // On libère la surface
    SDL_FreeSurface(perso); //On libère la surface
    SDL_Quit(); // libère la SDL de la mémoire
    return EXIT_SUCCESS;
}

void quit_game(){ //lorsque le joueur souhaite quitter le niveau du jeu -> redirection Menu
    run_game = 0;
}
void quit(){ //QUITTE TOTALEMENT LE PROGRAMME
    run = 0;
    run_game = 0;
}