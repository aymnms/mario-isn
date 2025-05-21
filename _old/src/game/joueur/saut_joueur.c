/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxSAUT_JOUEUR.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

double fonction(double i)
double fonction2(double i)
void statue_saut()
void saut()
void gravite()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "headers/MARIO_joueur.h"
#include "Headers/MARIO_conditions.h"


//-------------Variable-generale---------------//
extern SDL_Rect pos_perso;
extern int jump, chute;
extern int init_hauteur_saut, init_hauteur_chute;
extern int bool_saut, bool_saut_sur_mechant;
extern double x;
//---------------------------------------------//



//--------------------------------------------------SAUT----------------------------------------------------//

double fonction(double i){
    double auto solution = -i*i+22*i;
    return solution;
}

double fonction2(double i){
    double auto solution = -i*i+15*i;
    return solution;
}

void statue_saut(){
    if(go('B') == 1 && go('H') == 0 && jump == 0){ //si perso sur sol, qu'il n'a pas d'obstacle et ne saut pas | saut classique
        init_hauteur_saut = pos_perso.y;
        jump = 1;
        x = 0.1;
    }else{bool_saut = 0;}

    if(bool_saut_sur_mechant == 1 && go('H') == 0){ //si perso saut sur mechant et si il n'y a pas d'obstacle | saut "spécial"
        init_hauteur_saut = pos_perso.y;
        jump = 1;
        chute = 0;
        x = 0.1;
    }else{
        bool_saut_sur_mechant = 0;
        bool_saut = 0;
    }
}

void saut(){ 
    
    if(jump == 1 && go('H') == 0){
        x+=0.1;
        if(bool_saut_sur_mechant == 1 && x <= 7){
            pos_perso.y = init_hauteur_saut - fonction2(x);
        }else if(bool_saut_sur_mechant == 0 && x <= 11){
            pos_perso.y = init_hauteur_saut - fonction(x);
        }
    }
    if(bool_saut_sur_mechant == 0 && jump == 1 && go('H') == 0 && x >= 11 || jump == 1 && go('H') == 1
        || bool_saut_sur_mechant == 1 && jump == 1 && go('H') == 0 && x >= 7){
        jump = 0; chute = 0;
    }
}

//-----------------------------------------------GRAVITE----------------------------------------------------//

void gravite(){ //gere la position en y du personnage

        //INITIALISATION DE LA CHUTE
        if(jump == 0 && chute == 0 && go('B') == 0){
            chute = 1;
            if(bool_saut_sur_mechant == 1){
               init_hauteur_chute = pos_perso.y + fonction2(x);
               x = 8;
            }else{
               init_hauteur_chute = pos_perso.y + fonction(11);
               x = 11;
            }   
        }

        if(bool_saut_sur_mechant == 1){
            if(chute == 1 && go('B') == 0 && x >= 7){
                x+=0.1;
                pos_perso.y = init_hauteur_chute - fonction2(x);
                if(go('B') == 1){
                    x-=0.1;
                    pos_perso.y = init_hauteur_chute - fonction2(x);
                    while(go('B') != 1){
                        pos_perso.y += 1;
                    }
                    bool_saut_sur_mechant = 0;
                }
            }
        }else{
            if(chute == 1 && go('B') == 0 && x >= 11){
                x+=0.1;
                pos_perso.y = init_hauteur_chute - fonction(x);
                if(go('B') == 1){
                    x-=0.1;
                    pos_perso.y = init_hauteur_chute - fonction(x);
                    while(go('B') != 1){
                        pos_perso.y += 1;
                    }
                }
            }  
        }
        if(chute == 1 && go('B') == 1){
            chute = 0;
            if(bool_saut_sur_mechant == 1){bool_saut_sur_mechant =0;}
        }
        if (pos_perso.y > 440){game_over();}
}

//----------------------------------------------------------------------------------------------------------//