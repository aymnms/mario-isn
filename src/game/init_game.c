#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "display.h"
#include "MARIO_niveau.h"
#include "MARIO_joueur.h"
#include "path.h"
#include "globals.h"

extern SDL_Texture *img, *background;
extern SDL_Rect pos_perso, origine;

extern int decalage;
extern int coin, niveau, vie;

extern int jump, chute; //saut
extern int bool_droite, bool_gauche, bool_saut;
extern int bool_saut_sur_mechant;

extern char statue[10];
extern int direction_mechant[10];
extern SDL_Rect tableau_mechant[10][4];

void init_niveau() {
    init_skin();
    origine.x = 0;
    origine.y = 0;
    decalage = 0;
    bool_droite = 0, bool_gauche = 0, bool_saut = 0, bool_saut_sur_mechant = 0;
    jump = 0;
    chute = 0;
    emp = 0;

    pos_perso.x = 50;  // coordonn�s en x
    pos_perso.y = 100; // coordonn�s en y

    init_perso_skin();
    perso = mario_idle_droite;
    display_texture(perso, NULL, &pos_perso);
}

// init_niveau()/init_timer() run on every respawn and every level change
// (via init_game()), not just once at program start. barre/noir/cadre are
// fixed HUD sprites, so their texture load is guarded to run only once --
// previously every respawn/level change re-created them via create_texture()
// without ever freeing the previous one (never done anywhere in the
// codebase), leaking a texture each time.
static int timer_skin_loaded = 0;

void init_timer() {
    pos_barre.x = 400;
    pos_barre.y = 0;
    pos_noir.x = 600;
    pos_noir.y = 0;
    pos_cadre.x = 400;
    pos_cadre.y = 0;
    decoule = 600;
    if (!timer_skin_loaded) {
        barre = create_texture(path_img("barre.png"));
        noir = create_texture(path_img("noir.png"));
        cadre = create_texture(path_img("cadre.png"));
        timer_skin_loaded = 1;
    }
}

void init_game() {
    niveauSelect(niveau);
    init_niveau();
    init_timer();
}