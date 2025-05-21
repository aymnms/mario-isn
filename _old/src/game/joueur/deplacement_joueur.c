/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxDEPLACEMENT_JOUEUR.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

SDL_Rect set_position(SDL_Rect Point)
void droite()
void gauche()
void deplacement()
void deplacement_joueur()
int go(char direction)

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "headers/MARIO_quit.h"
#include "headers/MARIO_joueur.h"
#include "Headers/MARIO_niveau.h"
#include "Headers/MARIO_conditions.h"
#include "Headers/MARIO_game.h"
#include "headers/MARIO_musique.h"



//-------------Variable-generale-------------//
extern int run_game, run;
extern SDL_Surface *img, *background, *perso;
extern SDL_Rect pos_perso, origine;
extern SDL_Event event;
extern int nb_mechant;
extern int decalage; //strawling
extern int emp;
extern int bool_droite, bool_gauche, bool_saut;
extern int temps;
extern int coin, niveau, vie;
extern int vic;
int jean = 0;
//-------------------------------------------//


SDL_Rect set_position(SDL_Rect Point){
    SDL_Rect resultat;

    resultat.x = (Point.x + decalage) / 50;
    resultat.y = Point.y / 50;

    return resultat;
}


void droite(){ //si le personnage peut se deplacer vers la droite
    if (go('D') == 0){if(pos_perso.x >= 250 && decalage < 6700){decalage++;}else if(pos_perso.x < 500){{pos_perso.x++;}}}
}

void gauche(){ //si le personnage peut se deplacer vers la gauche
    if(go('G') == 0){if((pos_perso.x <= 50)&&(decalage > 0)){decalage--;}else if (pos_perso.x>0){pos_perso.x--;}}
}

void deplacement(){

    SDL_PollEvent(&event);

    switch(event.type){
        
        default:
        break;

        case SDL_QUIT:
            quit();
        break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                    bool_droite = 1;
                    break;
                
                case SDLK_LEFT:
                    bool_gauche = 1;
                    break;
            
                case SDLK_SPACE:
                if(go('B')){bool_saut = 1;playSon(1);}
                    
                    break;

                case SDLK_ESCAPE:
                    quit_game();
                    break;
            }
        break;

        case SDL_KEYUP:
            switch(event.key.keysym.sym){
                case SDLK_RIGHT:
                    bool_droite = 0;
                    temps = 0;
                    emp = 0;
                    break;
                
                case SDLK_LEFT:
                    bool_gauche = 0;
                    temps = 0;
                    emp = 1;
                    break;
            
                case SDLK_SPACE:
                    bool_saut = 0;
                    break;
            }
        break;
    }
}



void deplacement_joueur(){
    deplacement();
    if(bool_droite == 1){droite();}
    if(bool_gauche == 1){gauche();}
    if(bool_saut == 1){statue_saut();}
    saut();
    animation();
}


int go(char direction){
    auto int rep = 0;
    auto SDL_Rect test1, test2;

    SDL_Rect position_perso_NO = pos_perso;
    position_perso_NO.x +=8;
    position_perso_NO.y +=2;

    SDL_Rect position_perso_NE = pos_perso;
    position_perso_NE.x += 40;
    position_perso_NE.y += 2;

    SDL_Rect position_perso_SE = pos_perso;
    position_perso_SE.x += 40;
    position_perso_SE.y += 50;

    SDL_Rect position_perso_SO = pos_perso;
    position_perso_SO.x +=8;
    position_perso_SO.y += 50;


    switch (direction){

        case 'G': //gauche    
            position_perso_NO.x--; position_perso_SO.x--; 
            test1 = set_position(position_perso_NO);
            test2 = set_position(position_perso_SO);
        break;

        case 'B': //bas
            position_perso_SE.y++; position_perso_SO.y++; 
            test1 = set_position(position_perso_SE);
            test2 = set_position(position_perso_SO);
        break;

        case 'D': //droite
            position_perso_NE.x++; position_perso_SE.x++; 
            test1 = set_position(position_perso_NE);
            test2 = set_position(position_perso_SE);
        break;

        case 'H': //haut
            position_perso_NO.y++; position_perso_NE.y++; 
            test1 = set_position(position_perso_NO);
            test2 = set_position(position_perso_NE);
            //if(lvl1[test1.y][test1.x] == 2|| lvl1[test2.y][test2.x] == 2)||(test1 == test2 &&))
        break;
    }
    

    if (lvl[test1.y][test1.x] != '0' | lvl[test2.y][test2.x] != '0') {
            rep = 1;
            if (lvl[test1.y][test1.x] == '9' | lvl[test2.y][test2.x] == '9'){
                printf("pic\n");
                game_over();
            }else if ((lvl[test1.y][test1.x] == '2' | lvl[test2.y][test2.x] == '2')&&(direction == 'H'))
            {   playSon(2);
                coin++;
                if(lvl[test1.y][test1.x] == '2'){lvl[test1.y][test1.x] = '1';}
                else{lvl[test2.y][test2.x] = '1';}
            }else if ((lvl[test1.y][test1.x] == 'O' | lvl[test2.y][test2.x] == 'O')&&(jean == 0)) {
                
                printf("viviO\n");
                jean = 1;
                vic = 1;
                vie++;
                 playSon(4);
                rep = 0;                
            }else if (lvl[test1.y][test1.x] == 'S' | lvl[test2.y][test2.x] == 'S') {
                if (vic == 0){vic = 1;}
                    else {vic = 0;}
                jean = 1;
                printf("viviS\n");
                rep = 0;
            }

    }
       

    return rep;
}
