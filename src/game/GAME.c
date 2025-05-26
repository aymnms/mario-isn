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
extern SDL_Texture *perso, *img, *champi;
extern int nb_mechant;
extern int decalage;
extern SDL_Rect origine, pos_perso, pos_champi;
extern int decalage;
extern char statue[10];
extern SDL_Texture *imgMechant; //surface du mechant
extern SDL_Rect tableau_mechant[10][4]; 
extern int nb_mechant;
extern int repeat, x, y;
extern int coin, niveau, vie;
extern int jean;


SDL_Rect pos_barre, pos_noir, pos_cadre;
SDL_Texture *barre, *noir, *cadre;
int decoule, alfred = 0;

SDL_Rect pos_carre;
SDL_Texture *carre;
int fois = 0;

SDL_Texture *coinmeter, *coinnb;
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
    SDL_Texture *champi = create_texture("../img/champi.png");
    pos_champi.y= 0;
    for (int i = 0; i <= vie-1; i++){
        pos_champi.x = i*55;
        // ALORS
        display_texture(champi, NULL, &pos_champi);
    }
}

void coinAff(){
    switch (coin){

        case 0 :
        coinnb = create_texture("../img/zero.png");
        break;

        case 1 :
        coinnb = create_texture("../img/un.png");
        break;

        case 2 :
        coinnb = create_texture("../img/deux.png");
        break;

        case 3 :
        coinnb = create_texture("../img/trois.png");
        break;

        case 4 :
        coinnb = create_texture("../img/quatre.png");
        break;

        case 5 :
        coinnb = create_texture("../img/cinq.png");
        break;

        case 6 :
        coinnb = create_texture("../img/six.png");
        break;

        case 7 :
        coinnb = create_texture("../img/sept.png");
        break;

        case 8 :
        coinnb = create_texture("../img/huit.png");
        break;

        case 9 :
        coinnb = create_texture("../img/neuf.png");
        break;
    }

	// ALORS ALORS
    display_texture(coinnb, NULL, &pos_cadre);
    display_texture(coinmeter, NULL, &pos_coinmeter);
}

void refresh(){
    if(run_game == 1){
        origine.x = -decalage;

        // On nettoie l'écran
        clear_screen();

        niveauAfficher(decalage);

        //-----------------------Timer-----------------------//
        printf("timerr\n");
        // ALORS ALORS ALORS ALORS
        display_texture(barre, NULL, &pos_barre);
        display_texture(noir, NULL, &pos_noir);
        display_texture(cadre, NULL, &pos_cadre);
        display_texture(carre, NULL, &pos_carre);

        //-----------------------Mechant-----------------------//
        printf("afficher mechant\n");
        for(nb_mechant = 0; nb_mechant <= 19; nb_mechant++){
            afficher_mechant();
        }
        //-----------------------Perso-----------------------//
        printf("pos perso\n");
		// ALORS
        display_texture(perso, NULL, &pos_perso);

        //-----------------------vies-----------------------//
        printf("vie\n");
        systeme_vie();
        //-----------------------pièces-----------------------//
        printf("coin");

        coinAff();

        // Affiche tout ce qui a été display
        present_screen();
    }
}

// void init_coin(){
//     printf("init_coin\n");
//     pos_coinmeter.x = 0;
//     pos_coinmeter.y = 65;
//     coinmeter = SDL_LoadBMP("./img/coinx.png");
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

