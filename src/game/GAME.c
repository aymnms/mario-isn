#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "display.h"
#include "MARIO_niveau.h"
#include "MARIO_conditions.h"
#include "MARIO_mechant.h"
#include "MARIO_joueur.h"
#include "MARIO_menu.h"
#include "MARIO_game.h"
#include "path.h"
#include "globals.h"

extern int run_game;
extern SDL_Texture *img;
extern int decalage;
extern SDL_Rect origine, pos_perso;
extern SDL_Texture *imgMechant; //surface du mechant
extern int coin, niveau, vie;
extern int jean;

int alfred = 0;

SDL_Texture *coinmeter, *coinnb;
SDL_Rect pos_coinmeter, pos_coinnb, pos_champi;

// systeme_vie()/coinAff() run every rendered frame. Life icon and coin
// digits are a fixed, finite set of sprites, so they're loaded once and
// reused -- previously every frame did a fresh create_texture() (in
// systeme_vie() into a local variable that even shadowed the never-really-
// used `extern champi`, so the loaded texture wasn't reachable outside the
// call it leaked in), never freed anywhere in the codebase.
static SDL_Texture *img_champi;
static int champi_skin_loaded = 0;
static SDL_Texture *coin_digits[10];
static int coin_skin_loaded = 0;

void timer(void) {
    alfred++;
    if (alfred == 100) {
        decoule--;
        pos_noir.x = decoule;
        alfred = 0;
    }
    if (decoule <= 400) {
        game_over();
    }
}

void systeme_vie(void) { // affiche les vies à l'écran
    if (!champi_skin_loaded) {
        img_champi = create_texture(path_img("champi.png"));
        champi_skin_loaded = 1;
    }
    pos_champi.y = 0;
    for (int i = 0; i <= vie - 1; i++) {
        pos_champi.x = i * 55;
        // ALORS
        display_texture(img_champi, NULL, &pos_champi);
    }
}

void coinAff(void) {
    switch (coin) {

        case 0:
            coinnb = coin_digits[0];
            break;

        case 1:
            coinnb = coin_digits[1];
            break;

        case 2:
            coinnb = coin_digits[2];
            break;

        case 3:
            coinnb = coin_digits[3];
            break;

        case 4:
            coinnb = coin_digits[4];
            break;

        case 5:
            coinnb = coin_digits[5];
            break;

        case 6:
            coinnb = coin_digits[6];
            break;

        case 7:
            coinnb = coin_digits[7];
            break;

        case 8:
            coinnb = coin_digits[8];
            break;

        case 9:
            coinnb = coin_digits[9];
            break;
    }

    // ALORS ALORS
    display_texture(coinmeter, NULL, &pos_coinmeter);
    display_texture(coinnb, NULL, &pos_coinnb);
}

void refresh(void) {
    if (run_game == 1) {
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

        //-----------------------Mechant-----------------------//
        printf("afficher mechant\n");
        for (nb_mechant = 0; nb_mechant < MAX_MECHANTS; nb_mechant++) {
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

void init_coin(void) {
    printf("init_coin\n");
    pos_coinmeter.x = 0;
    pos_coinmeter.y = 65;
    pos_coinnb.x = 70;
    pos_coinnb.y = 65;

    if (!coin_skin_loaded) {
        coinmeter = create_texture(path_img("coinx.png"));
        if (coinmeter == NULL) {
            printf("coinx not found\n");
        }
        coin_digits[0] = create_texture(path_img("zero.png"));
        coin_digits[1] = create_texture(path_img("un.png"));
        coin_digits[2] = create_texture(path_img("deux.png"));
        coin_digits[3] = create_texture(path_img("trois.png"));
        coin_digits[4] = create_texture(path_img("quatre.png"));
        coin_digits[5] = create_texture(path_img("cinq.png"));
        coin_digits[6] = create_texture(path_img("six.png"));
        coin_digits[7] = create_texture(path_img("sept.png"));
        coin_digits[8] = create_texture(path_img("huit.png"));
        coin_digits[9] = create_texture(path_img("neuf.png"));
        coin_skin_loaded = 1;
    }
}

void mechant(void) {
    for (nb_mechant = 0; nb_mechant < MAX_MECHANTS; nb_mechant++) {
        deplacement_mechant();
        contact(); //test contact si tue ou meurt
    }
}

void joueur(void) {
    deplacement_joueur();
    gravite();
}

void GAME(void) {
    int fps = 60;
    int frameDelay = 1000 / fps;
    Uint32 frameStart;
    int frameTime;

    while (run_game) {
        printf("init_game\n");
        init_game();
        init_coin();
        while (run_game) {
            printf("GAME bcl");

            frameStart = SDL_GetTicks();
            for (int i = 1; i <= 5; i++) {
                printf("joueur\n");
                joueur();
                printf("mechant\n");
                mechant();
                printf("condition\n");
                conditions();
                printf("timer\n");
                timer();
                if (jean == 1) {
                    break;
                }
            }
            refresh();
            printf("test jean\n");
            if (jean == 1) {
                printf("victoire!\n");
                victory();
                jean = 0;
                break;
            }

            //timer
            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            } else {
                printf("laaaag\n");
            }
        }
    }
}
