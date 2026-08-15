#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "display.h"
#include "MARIO_conditions.h"
#include "MARIO_quit.h"
#include "MARIO_game.h"
#include "MARIO_niveau.h"
#include "MARIO_joueur.h"
#include "MARIO_musique.h"
#include "path.h"
#include "globals.h"

extern SDL_Rect origine, pos_perso;
extern SDL_Texture *img, *perso;
extern SDL_Texture *mario_saut_droite;
extern SDL_Event event;
extern int decalage;
extern int coin, niveau, vie;
extern char statue[MAX_MECHANTS];
extern SDL_Rect tableau_mechant[MAX_MECHANTS][4];
extern int vic;

// game_over()/victory() each load a fixed, finite scene image (there are
// only ever these 3), so they're loaded once and reused -- previously
// every death/victory did a fresh create_texture(), leaking a texture each
// time (never freed anywhere in the codebase). Lower frequency than the
// per-frame leaks fixed elsewhere, but real over a long play session with
// repeated deaths.
static SDL_Texture *img_dommage, *img_game_over_screen, *img_victory;
static int scene_skin_loaded = 0;

static void init_scene_skin(void) {
    if (scene_skin_loaded) {
        return;
    }
    img_dommage = create_texture(path_img("dommage.png"));
    img_game_over_screen = create_texture(path_img("game_over.png"));
    img_victory = create_texture(path_img("victory.png"));
    scene_skin_loaded = 1;
}

int conditions(void) {
    auto int rep = 0;
    if (pos_perso.y >= 450) {
        game_over();
    } //condition de défaite
    //if(vic == 1){victory();vic++;} //condition de Victoire
    if (coin >= 10) {
        vie++;
        coin = 0;
        playSon(4);
    }
    return rep;
}

void game_over(void) {
    vie--;
    for (int i = 0; i <= 19; i++) {
        statue[i] = '0';
    }
    for (int i = 0; i <= 19; i++) {
        tableau_mechant[i][1].x = 0;
        tableau_mechant[i][1].y = 0;
    }

    init_scene_skin();
    if (vie > 0) {
        playMus(3);
        origine.x = 0;
        origine.y = 0;
        img = img_dommage;

        // ALORS
        update_texture(img, NULL, &origine);
        // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre

        SDL_Delay(3146);
        playMus(1);
        init_game();
    } else {
        playMus(4);
        origine.x = 0;
        origine.y = 0;
        img = img_game_over_screen;

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

int victory(void) {
    origine.x = 0;
    origine.y = 0;
    playMus(5);
    init_scene_skin();
    img = img_victory;
    for (int i = 0; i <= 19; i++) {
        statue[i] = '0';
    }
    for (int i = 0; i <= 19; i++) {
        tableau_mechant[i][1].x = 0;
        tableau_mechant[i][1].y = 0;
    }
    pos_perso.x = 280;
    pos_perso.y = 550;
    init_perso_skin();
    perso = mario_saut_droite;
    for (pos_perso.y = 550; pos_perso.y >= 150; pos_perso.y -= 2) {
        clear_screen();
        // ALORS
        display_texture(img, NULL, &origine);
        display_texture(perso, NULL, &pos_perso);
        // SDL_BlitSurface(img, NULL, background, &origine); //on d�clare l'image comme fond de fenetre
        // SDL_BlitSurface(perso, NULL, background, &pos_perso);
        present_screen();

        SDL_Delay(10);
    }
    for (pos_perso.y = 150; pos_perso.y <= 200; pos_perso.y += 2) {
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
    if (niveau == 6) {
        quit();
        return 0;
    } else {
        niveau++;
        return 1;
    }
}