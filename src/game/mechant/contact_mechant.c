/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxCONTACT_MECHANT.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int goM(int direction)
void mechantMort()
void contact_lateral()
void contact_vertical()
void contact()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "headers/MARIO_conditions.h"
#include "headers/MARIO_mechant.h"
#include "headers/MARIO_joueur.h"
#include "headers/MARIO_game.h"
#include "Headers/MARIO_niveau.h"
#include "headers/MARIO_musique.h"


//--------------------------Variable-générale--------------------------//

extern SDL_Rect pos_perso;
extern int decalage;
extern char statue[20];
extern SDL_Rect tableau_mechant[20][4];  
extern int nb_mechant;
extern int jump, chute, bool_saut_sur_mechant;
extern int init_hauteur_saut, init_hauteur_chute;
extern double x;
extern int vie;
//---------------------------------------------------------------------//

int goM(int direction){    
    int rep = 0;

    auto SDL_Rect test1, test2;

    //on définit 4 points pour positionner le mechant sur la grille du niveau

    SDL_Rect position_mechant_NO = tableau_mechant[nb_mechant][1];
    position_mechant_NO.x +=2;
    position_mechant_NO.y +=2;

    SDL_Rect position_mechant_NE = tableau_mechant[nb_mechant][1];
    position_mechant_NE.x += 47;
    position_mechant_NE.y += 2;

    SDL_Rect position_mechant_SE = tableau_mechant[nb_mechant][1];
    position_mechant_SE.x += 47;
    position_mechant_SE.y += 50;

    SDL_Rect position_mechant_SO = tableau_mechant[nb_mechant][1];
    position_mechant_SO.x +=8;
    position_mechant_SO.y += 50;


    switch (direction){

        case -1: //gauche    
            position_mechant_NO.x--; position_mechant_SO.x--; 
            test1 = setRectMechant(position_mechant_NO);
            test2 = setRectMechant(position_mechant_SO);
        break;

        case 666: //bas (dans le cas où il y a un vide sous le méchant)
            position_mechant_SE.y++; position_mechant_SO.y++; 
            test1 = setRectMechant(position_mechant_SE);
            test2 = setRectMechant(position_mechant_SO);
        break;

        case 1: //droite
            position_mechant_NE.x++; position_mechant_SE.x++; 
            test1 = setRectMechant(position_mechant_NE);
            test2 = setRectMechant(position_mechant_SE);
        break;

        case 999: //haut (pas utilisée dans le programme mais on pourrait imaginer son utilité en allant plus loin)
            position_mechant_NO.y++; position_mechant_NE.y++; 
            test1 = setRectMechant(position_mechant_NO);
            test2 = setRectMechant(position_mechant_NE);
        break;
    }

    if ((lvl[test1.y][test1.x] != '0' ||
        lvl[test2.y][test2.x] != '0') || 
        lvl[test1.y][test1.x] != '0' && lvl[test2.y][test2.x] != '0'){
          rep = 1;
    }

    return rep;
}

void mechantMort(){	//detruit le perso	
    playSon(3);
	statue[nb_mechant] = 'M';
	printf(" mechant %d mort\n", nb_mechant);
}

void contact_lateral(){ //si le mechant et le personnage se touchent verticalement
    
    if (statue[nb_mechant] != 'M'){ 
        // I. déterminer si loe personnage est touché
        // A. axe des x
        // (coordonnés à partir du perso)
        if ((((pos_perso.x + decalage + 39) >= tableau_mechant[nb_mechant][1].x)&&(pos_perso.x + decalage + 39) <= tableau_mechant[nb_mechant][1].x+2)||
            ((pos_perso.x + decalage) <= (tableau_mechant[nb_mechant][1].x + 40)&&(pos_perso.x + decalage) >= (tableau_mechant[nb_mechant][1].x + 38)))
        {
            // B. axe des y
            if ((pos_perso.y >= tableau_mechant[nb_mechant][1].y - 45)&&
                (pos_perso.y <=tableau_mechant[nb_mechant][1].y + 45)) {
                    game_over(); //le personnage perd une vie
                    
                }
        }
    }
}

void contact_vertical(){ //si le personnage est au dessus du méchant
    
    if (statue[nb_mechant] != 'M' && chute == 1){ 
        // II. déterminer si le personnage touche la haut du méchant
        // A. axe des x
        if((pos_perso.x + decalage >= tableau_mechant[nb_mechant][1].x -49)&&
            (pos_perso.x + decalage <= tableau_mechant[nb_mechant][1].x + 48)){
                
                // B. axe des y
                if(((pos_perso.y +50) >= (tableau_mechant[nb_mechant][1].y -5))&&
                ((pos_perso.y +50) <= (tableau_mechant[nb_mechant][1].y +5))){
                    if (statue[nb_mechant] == 'V')
                    {
                        bool_saut_sur_mechant = 1;
                    statue_saut();
                    mechantMort(); //désactive le mechant
                }else{
                    game_over();
                }
        }
    }
}}


void contact(){
    if (statue[nb_mechant] == 'V'){
    contact_lateral();  //si touche perso latérallement
    contact_vertical();}else if(statue[nb_mechant] == 'B'){contactB();}
}