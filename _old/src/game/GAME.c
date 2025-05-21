/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxGAME.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void timer()
void systeme_vie()
void refresh()
void mechant()
void joueur()
void GAME()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "Headers/MARIO_niveau.h"
#include "Headers/MARIO_conditions.h"
#include "Headers/MARIO_mechant.h"
#include "Headers/MARIO_joueur.h"
#include "headers/MARIO_menu.h"
#include "headers/MARIO_game.h"



//-----Variable-générale-----//
extern int run_game;
extern SDL_Surface *background, *perso, *img, *champi;
extern int nb_mechant;
extern int decalage;
extern SDL_Rect origine, pos_perso, pos_champi;
extern int decalage;
extern char statue[10];
extern SDL_Surface *imgMechant; //surface du mechant
extern SDL_Rect tableau_mechant[10][4]; 
extern int nb_mechant;
extern int repeat, x, y;
extern int coin, niveau, vie;
extern int jean;
//---------------------------//


//-----------Variable-timer-----------//
SDL_Rect pos_barre, pos_noir, pos_cadre;
SDL_Surface *barre, *noir, *cadre;
int decoule, alfred = 0;
//-----------Variable-timer-----------//
SDL_Rect pos_carre;
SDL_Surface *carre;
int fois = 0;
//------------------------------------//
SDL_Surface *coinmeter, *coinnb;
SDL_Rect pos_coinmeter, pos_coinnb;

void timer(){
    alfred++;
    if (alfred == 100){
        decoule--;
       pos_noir.x = decoule;
       alfred = 0;
    }       
    if ( decoule <= 400){
     game_over();
    }
}

void systeme_vie(){ // affiche les vies à l'écran
    champi = SDL_LoadBMP("././img/champi.bmp");
    if(champi == NULL){printf("not found\n");}
    SDL_SetColorKey(champi, SDL_SRCCOLORKEY, SDL_MapRGB(champi->format, 255, 255, 255));
    
    pos_champi.y= 0;
    for (int i = 0; i <= vie-1; i++){
        
        pos_champi.x = i*55;
        
        SDL_BlitSurface (champi, NULL, background, &pos_champi);

    }
}
void coinAff(){
    switch (coin){
    
        case 0 : 
        coinnb = SDL_LoadBMP("./img/zero.bmp");
        break;
    
        case 1 : 
        coinnb = SDL_LoadBMP("./img/un.bmp");
        break;
        
        case 2 : 
        coinnb = SDL_LoadBMP("./img/deux.bmp");
        break;
        
        case 3 : 
        coinnb = SDL_LoadBMP("./img/trois.bmp");
        break;
        
        case 4 : 
        coinnb = SDL_LoadBMP("./img/quatre.bmp");
        break;
        
        case 5 : 
        coinnb = SDL_LoadBMP("./img/cinq.bmp");
        break;
        
        case 6 : 
        coinnb = SDL_LoadBMP("./img/six.bmp");
        break;
        
        case 7 : 
        coinnb = SDL_LoadBMP("./img/sept.bmp");
        break;
        
        case 8 : 
        coinnb = SDL_LoadBMP("./img/huit.bmp");
        break;
        
        case 9 : 
        coinnb = SDL_LoadBMP("./img/neuf.bmp");
        break;
        
    }
    if(coinnb == NULL){printf("coinnb not found\n");}
    else{SDL_SetColorKey(coinnb, SDL_SRCCOLORKEY, SDL_MapRGB(coinnb->format, 0, 0, 0));}
    SDL_BlitSurface(coinnb, NULL, background, &pos_coinnb);
    SDL_BlitSurface(coinmeter, NULL, background, &pos_coinmeter);
}
void refresh(){
    if(run_game == 1){
        origine.x = -decalage;

        niveauAfficher(decalage);
        //-----------------------Timer-----------------------//
        printf("timerr\n");
        SDL_BlitSurface(barre, NULL, background, &pos_barre);
        SDL_BlitSurface(noir, NULL, background, &pos_noir);
        SDL_BlitSurface(cadre, NULL, background, &pos_cadre);
        SDL_BlitSurface(carre, NULL, background, &pos_carre);
        //-----------------------Mechant-----------------------// 
        printf("afficher mechant\n");
        for(nb_mechant = 0; nb_mechant <= 19; nb_mechant++){
            afficher_mechant();
        }
        //-----------------------Perso-----------------------//
        printf("pos perso\n");
        SDL_BlitSurface(perso, NULL, background, &pos_perso);
       
        //-----------------------vies-----------------------//
        printf("vie\n");
        systeme_vie();
        //-----------------------pièces-----------------------//
        printf("coin");

        coinAff();
         SDL_Flip(background); /* Mise � jour de l'�cran*/
        
        
    }
}
void init_coin(){
    printf("init_coin\n");
    pos_coinmeter.x = 0;
    pos_coinmeter.y = 65;
    coinmeter = SDL_LoadBMP("./img/coinx.bmp");
    if (coinmeter == NULL) {printf("coinx not found\n");}
    else{SDL_SetColorKey(coinmeter, SDL_SRCCOLORKEY, SDL_MapRGB(coinmeter->format, 0, 0, 0));}
    
    pos_coinnb.x = 70;
    pos_coinnb.y = 65;
}








void mechant(){
    for(nb_mechant = 0; nb_mechant <= 19; nb_mechant++){
        deplacement_mechant();
        contact(); //test contact si tue ou meurt
    }
}

void joueur(){
    deplacement_joueur();
    gravite();
}

void GAME(){
    auto int fps = 60;        
    auto int frameDelay = 1000/fps;
    auto Uint32 frameStart;
    auto int frameTime;
    auto int a =0;
    while(run_game){
        printf("init_game\n");
        init_game();
        init_coin();
        while (run_game){
            printf("GAME bcl");
    
            
    
            frameStart = SDL_GetTicks();
            for (int i = 1; i<=5; i++){
                printf("joueur\n");
                joueur();
                printf("mechant\n");
                mechant();
                printf("condition\n");
                conditions();
                printf("timer\n");
                timer();
                if (jean ==1){break;}
                
            }
            refresh();
            printf("test jean\n");
            if (jean == 1){printf ("victoire!\n");victory();jean = 0;break;}

            //timer
            frameTime = SDL_GetTicks() - frameStart;
            if(frameDelay > frameTime)
            {
                SDL_Delay(frameDelay - frameTime);
            }else{printf("laaaag\n");}    
        }
    }
}

