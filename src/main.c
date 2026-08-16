#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>

#include "display.h"
#include "MARIO_menu.h"
#include "MARIO_game.h"
#include "MARIO_niveau.h"
#include "globals.h"

int run = 1, run_game = 1;
int niveau = 1;
int vie = 3;
int coin = 0;
int vic = 0;

SDL_Rect tableau_mechant[MAX_MECHANTS][4]; //tous les points pour les mechants
SDL_Texture *imgMechant;
char statue[MAX_MECHANTS] = {'0', '0', '0', '0', '0', '0', '0', '0', '0', '0'}; //mechant mort ou vivant
int direction_mechant[MAX_MECHANTS];                                            //tout est dans le nom
int nb_mechant; //numéro du méchant à dont c'est le tour (voire game_runer.c)

SDL_Rect origine, pos_perso, pos_mechant; //point pour positionner les elements
SDL_Event event;                          //stock les événements

int bool_droite = 0, bool_gauche = 0, bool_saut = 0, bool_saut_sur_mechant = 0;
int decalage; //strawling
int jump, chute;
int init_hauteur_saut, init_hauteur_chute;

int main(int argc, char *argv[]) {
    (void)argc; // required by SDL_main's expected signature, unused otherwise
    (void)argv;
    printf("Hello World\n");
    init_menu(); //envoie sur "init_menu.c" par "init_menu.h" -- une seule fois : crée
                 //la fenêtre/le renderer/l'audio, jamais à refaire à chaque retour au menu

    // CI's headless smoke/leak-regression tests need to reach real gameplay
    // without a mouse click to get past the menu. This env var is never set
    // during normal play; it skips straight to one GAME() session instead
    // of looping through the menu. See .github/workflows/build.yml.
    if (getenv("MARIO_ISN_AUTOPLAY")) {
        run_game = 1;
        GAME();
    } else {
        while (run) {
            MENU(); //envoie sur "MENU.c" par "MENU.h"
            if (run_game) {
                GAME();
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return EXIT_SUCCESS;
}

void quit_game(void) { //lorsque le joueur souhaite quitter le niveau du jeu -> redirection Menu
    run_game = 0;
    // A fresh return to the menu should mean a fresh game next time Play is
    // clicked. niveauSelect()/addMechant()/addBowser() only ever ADD
    // enemies into statue[]/tableau_mechant[], they never clear stale ones
    // from an interrupted session first, and init_game() never resets
    // `niveau` either. Without this, quitting mid-level and pressing Play
    // again resumed that same level (never level 1) with its enemies
    // duplicated -- the old ones were still marked alive in their slots
    // alongside the newly (re)loaded ones. This path was unreachable before
    // the menu-return-loop fix (see PLAN.md J13), so the gap was latent
    // until then.
    for (int i = 0; i < MAX_MECHANTS; i++) {
        statue[i] = '0';
        tableau_mechant[i][1].x = 0;
        tableau_mechant[i][1].y = 0;
    }
    vie = 3;
    niveau = 1;
    coin = 0;
}
void quit(void) { //QUITTE TOTALEMENT LE PROGRAMME
    run = 0;
    run_game = 0;
}