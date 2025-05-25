#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "display.h"
#include "MARIO_niveau.h"
#include "MARIO_conditions.h"
#include "MARIO_mechant.h"
#include "MARIO_joueur.h"
#include "MARIO_menu.h"
#include "MARIO_game.h"


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


SDL_Rect pos_barre, pos_noir, pos_cadre;
SDL_Surface *barre, *noir, *cadre;
int decoule, alfred = 0;

SDL_Rect pos_carre;
SDL_Surface *carre;
int fois = 0;

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
    champi = IMG_Load("../img/champi.bmp");
    if(champi == NULL){printf("not found\n");}
    SDL_SetColorKey(champi, SDL_TRUE, SDL_MapRGB(champi->format, 255, 255, 255));



    pos_champi.y= 0;
    for (int i = 0; i <= vie-1; i++){

        pos_champi.x = i*55;

        // ALORS
        SDL_BlitSurface (champi, NULL, background, &pos_champi);
        // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, champi);
        // SDL_FreeSurface(champi);
        // display_texture(texture, NULL, &pos_champi);
        // SDL_DestroyTexture (texture);
    }
}

void coinAff(){
    switch (coin){

        case 0 :
        coinnb = IMG_Load("../img/zero.bmp");
        break;

        case 1 :
        coinnb = IMG_Load("../img/un.bmp");
        break;

        case 2 :
        coinnb = IMG_Load("../img/deux.bmp");
        break;

        case 3 :
        coinnb = IMG_Load("../img/trois.bmp");
        break;

        case 4 :
        coinnb = IMG_Load("../img/quatre.bmp");
        break;

        case 5 :
        coinnb = IMG_Load("../img/cinq.bmp");
        break;

        case 6 :
        coinnb = IMG_Load("../img/six.bmp");
        break;

        case 7 :
        coinnb = IMG_Load("../img/sept.bmp");
        break;

        case 8 :
        coinnb = IMG_Load("../img/huit.bmp");
        break;

        case 9 :
        coinnb = IMG_Load("../img/neuf.bmp");
        break;

    }
    if(coinnb == NULL){printf("coinnb not found\n");}
    else{SDL_SetColorKey(coinnb, SDL_TRUE, SDL_MapRGB(coinnb->format, 0, 0, 0));}
	// ALORS ALORS
    SDL_BlitSurface(coinnb, NULL, background, &pos_coinnb);
    SDL_BlitSurface(coinmeter, NULL, background, &pos_coinmeter);
    // SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, coinnb);
    // SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, coinmeter);
    // SDL_FreeSurface(coinnb);
    // SDL_FreeSurface(coinmeter);
    // display_texture(texture, NULL, &pos_coinnb);
    // display_texture(texture2, NULL, &pos_coinmeter);
    // SDL_DestroyTexture (texture);
    // SDL_DestroyTexture (texture2);
}

void refresh(){
    if(run_game == 1){
        origine.x = -decalage;

        niveauAfficher(decalage);

        //-----------------------Timer-----------------------//
        printf("timerr\n");
        // ALORS ALORS ALORS ALORS
        SDL_BlitSurface(barre, NULL, background, &pos_barre);
        SDL_BlitSurface(noir, NULL, background, &pos_noir);
        SDL_BlitSurface(cadre, NULL, background, &pos_cadre);
        SDL_BlitSurface(carre, NULL, background, &pos_carre);
        // SDL_Texture *texture1 = SDL_CreateTextureFromSurface(renderer, barre);
        // SDL_Texture *texture2 = SDL_CreateTextureFromSurface(renderer, noir);
        // SDL_Texture *texture3 = SDL_CreateTextureFromSurface(renderer, cadre);
        // SDL_Texture *texture4 = SDL_CreateTextureFromSurface(renderer, carre);
        // SDL_FreeSurface(barre);
        // SDL_FreeSurface(noir);
        // SDL_FreeSurface(cadre);
        // SDL_FreeSurface(carre);
        // display_texture(texture1, NULL, &pos_barre);
        // display_texture(texture2, NULL, &pos_noir);
        // display_texture(texture3, NULL, &pos_cadre);
        // display_texture(texture4, NULL, &pos_carre);
        // SDL_DestroyTexture (texture1);
        // SDL_DestroyTexture (texture2);
        // SDL_DestroyTexture (texture3);
        // SDL_DestroyTexture (texture4);

        //-----------------------Mechant-----------------------//
        printf("afficher mechant\n");
        for(nb_mechant = 0; nb_mechant <= 19; nb_mechant++){
            afficher_mechant();
        }
        //-----------------------Perso-----------------------//
        printf("pos perso\n");
		// ALORS
        SDL_BlitSurface(perso, NULL, background, &pos_perso);
        // SDL_Texture *texture5 = SDL_CreateTextureFromSurface(renderer, perso);
        // SDL_FreeSurface(perso);
        // display_texture(texture5, NULL, &pos_perso);
        // SDL_DestroyTexture (texture5);


        //-----------------------vies-----------------------//
        printf("vie\n");
        systeme_vie();
        //-----------------------pièces-----------------------//
        printf("coin");

        coinAff();
        // SDL_Flip(background); /* Mise � jour de l'�cran*/
        SDL_RenderPresent(renderer);
    }
}

// void init_coin(){
//     printf("init_coin\n");
//     pos_coinmeter.x = 0;
//     pos_coinmeter.y = 65;
//     coinmeter = SDL_LoadBMP("./img/coinx.bmp");
//     if (coinmeter == NULL) {printf("coinx not found\n");}
//     else{SDL_SetColorKey(coinmeter, SDL_SRCCOLORKEY, SDL_MapRGB(coinmeter->format, 0, 0, 0));}
//
//     pos_coinnb.x = 70;
//     pos_coinnb.y = 65;
// }

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

