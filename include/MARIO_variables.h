#include <SDL2/SDL.h>
//-------------------------------------------------Variable-générale-------------------------------------------------//
int run = 1, run_game = 1;
int niveau = 1;
int vie = 3;
int coin = 0;
//--------------------------------------------------Variable-mechant-------------------------------------------------//
SDL_Rect tableau_mechant[10][4]; //tous les points pour les mechants 
SDL_Surface *imgMechant;
char statue[10] ={'0','0','0','0','0','0','0','0','0','0'}; //mechant mort ou vivant
int direction_mechant[10]; //tout est dans le nom
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
char lvl[10][71];
//-------------------------------------------------------------------------------------------------------------------//
SDL_Surface *champi;
SDL_Rect pos_champi;