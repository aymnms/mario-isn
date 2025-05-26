#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "display.h"
#include "MARIO_conditions.h"
#include "MARIO_quit.h"
#include "MARIO_game.h"
#include "MARIO_niveau.h"
#include "MARIO_musique.h"

extern SDL_Rect origine, pos_perso;
extern SDL_Texture *img, *perso;
extern SDL_Event event;
extern int decalage;
extern int coin, niveau, vie;
extern char statue[20];
extern SDL_Rect tableau_mechant[20][4]; 
extern int vic;

int conditions(){
    auto int rep = 0;
    if(pos_perso.y >=450){game_over();} //condition de défaite
    //if(vic == 1){victory();vic++;} //condition de Victoire
    if(coin >= 10){vie++; coin = 0;playSon(4);}
    return rep;
}

void game_over(){
    vie--;
    for(int i = 0; i<=19; i++)
    {
        statue[i] = '0';
    }
    for(int i = 0; i<=19; i++)
    {
        tableau_mechant[i][1].x = 0;
        tableau_mechant[i][1].y = 0;
    }
    
    if ( vie > 0){
        playMus(3);
        origine.x = 0;
        origine.y = 0;
        img = create_texture("../img/dommage.bmp");

        // ALORS
        update_texture(img, NULL, &origine);
        // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre

        SDL_Delay(3146);
        playMus(1);
        init_game();
    }
    else {
        playMus(4);
        origine.x = 0;
        origine.y = 0;
        img = create_texture("../img/game_over.bmp");

        // ALORS
        update_texture(img, NULL, &origine);
        // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre

        SDL_Delay(5000);
        SDL_WaitEvent(&event);
        quit_game();
        vie = 3;
        niveau = 1;
    }

}
   

int victory() {
    origine.x = 0;
    origine.y = 0;
    playMus(5);
    img = create_texture("../img/victory.bmp");
    for(int i = 0; i<=19; i++)
    {
        statue[i] = '0';
    }
    for(int i = 0; i<=19; i++)
    {
        tableau_mechant[i][1].x = 0;
        tableau_mechant[i][1].y = 0;
    }
        pos_perso.x = 280;
        pos_perso.y = 550;
        perso = create_texture("../img/mario_saut_droite.bmp");
        for ( pos_perso.y = 550; pos_perso.y >= 150; pos_perso.y -=2){
            clear_screen();
            // ALORS
            display_texture(img, NULL, &origine);
            display_texture(perso, NULL, &pos_perso);
            // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre
            // SDL_BlitSurface(perso, NULL, background, &pos_perso);
            present_screen();

            SDL_Delay(10);
        }
        for ( pos_perso.y = 150; pos_perso.y <= 200; pos_perso.y+=2){
            clear_screen();
            // ALORS
            display_texture(img, NULL, &origine);
            display_texture(perso, NULL, &pos_perso);
            // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre
            // SDL_BlitSurface(perso, NULL, background, &pos_perso);
            present_screen();

            SDL_Delay(8);
        }

    // ALORS
    clear_screen();
    display_texture(img, NULL, &origine);
    display_texture(perso, NULL, &pos_perso);
    // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre
    // SDL_BlitSurface(perso, NULL, background, &pos_perso);
    present_screen();

    SDL_Delay(5541);
    playMus(1);
    SDL_WaitEvent(&event);
    if (niveau == 6){quit(); return 0;}
    else{niveau++;return 1;}
}