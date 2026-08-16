#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "MARIO_quit.h"
#include "MARIO_musique.h"
#include "display.h"
#include "path.h"

extern int run, run_game;
extern SDL_Event event;

// Not extern anywhere: kept internal linkage on purpose. click_x/click_y
// used to be named `x`/`y` at external linkage, colliding with the
// unrelated global `double x` in globals.h (the jump-physics progress
// variable, used in saut_joueur.c) -- two different globals sharing one
// name, neither `static`. It happened to link and run without a visible
// crash so far (see AUDIT.md §9 for why), but was a real latent bug.
static int repeat = 1, click_x, click_y;

// MENU() now runs once per visit to the menu screen (main.c's loop returns
// here after every GAME() session), not just once at process startup, so
// the menu image is loaded once and redrawn on each entry instead of
// living in init_menu()'s one-time setup (see init_menu.c).
static SDL_Texture *menu_texture;
static int menu_skin_loaded = 0;

int start_game(void) {
    if (!menu_skin_loaded) {
        menu_texture = create_texture(path_img("menu.png"));
        menu_skin_loaded = 1;
    }
    update_texture(menu_texture, NULL, NULL);

    playMus(2);
    repeat = 1;
    while (repeat) {

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    quit(); // ferme vraiment l'appli (avant : ne faisait que
                            // sortir de cette boucle, laissant le process
                            // tourner -- voir PLAN.md J13)
                    repeat = 0;
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if (event.button.button == SDL_BUTTON_LEFT) { //si clique gauche
                        click_x = event.button.x;
                        click_y = event.button.y;
                        if (151 < click_x && click_x < 453 && 226 < click_y &&
                            click_y < 312) { //si clique dans "play" alors lance le jeu
                            repeat = 0;
                            playMus(1);

                            if (run_game != 1) {
                                run_game = 1;
                            }
                        } else if (151 < click_x && click_x < 453 && 332 < click_y &&
                                   click_y < 416) { //si clicque dans "quit" alors quit le jeu
                            quit();           //pour quitter le jeu
                            repeat = 0;       //arrete la boucle
                            return EXIT_SUCCESS;
                        }
                        break;
                    }
            }
        }
    }
    return 0;
}

void MENU(void) { start_game(); }