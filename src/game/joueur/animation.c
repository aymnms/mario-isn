#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "MARIO_joueur.h"
#include "display.h"
#include "path.h"
#include "globals.h"

extern SDL_Texture *img;
extern int bool_droite, bool_gauche;
int test_bas;

// animation() runs up to 5x per rendered frame (once per physics substep),
// and some branches below re-assign perso 2-3 times in a single call. Mario
// only ever wears a fixed, finite set of sprites, so they're loaded once
// here and reused -- previously every assignment did a fresh
// create_texture(), leaking a GPU texture every time (never freed anywhere
// in the codebase), which is what caused the reported memory leak/lag.
SDL_Texture *mario_idle_droite, *mario_saut_droite;
static SDL_Texture *mario_idle_gauche, *mario_saut_gauche;
static SDL_Texture *mario_frame1_gauche, *mario_frame2_gauche, *mario_frame3_gauche;
static SDL_Texture *mario_frame1_droite, *mario_frame2_droite, *mario_frame3_droite;
static int perso_skin_loaded = 0;

void init_perso_skin() {
    if (perso_skin_loaded) {
        return;
    }
    mario_idle_droite = create_texture(path_img("mario_idle.png"));
    mario_idle_gauche = create_texture(path_img("mario_idle_gauche.png"));
    mario_saut_droite = create_texture(path_img("mario_saut_droite.png"));
    mario_saut_gauche = create_texture(path_img("mario_saut_gauche.png"));
    mario_frame1_gauche = create_texture(path_img("frame_1_gauche.png"));
    mario_frame2_gauche = create_texture(path_img("frame_2_gauche.png"));
    mario_frame3_gauche = create_texture(path_img("frame_3_gauche.png"));
    mario_frame1_droite = create_texture(path_img("frame_1_droite.png"));
    mario_frame2_droite = create_texture(path_img("frame_2_droite.png"));
    mario_frame3_droite = create_texture(path_img("frame_3_droite.png"));
    perso_skin_loaded = 1;
}

void animation() {
    init_perso_skin();
    test_bas = go('B');
    if (test_bas == 0) //si le perso ne touche pas le sol
    {
        if (bool_droite == 1 || bool_gauche == 1) {
            if (bool_droite == 1) {
                perso = mario_saut_droite;
            } else {
                perso = mario_saut_gauche;
            }
        } else if (emp == 0) {
            perso = mario_saut_droite;
        } else {
            perso = mario_saut_gauche;
        }
    } else if (bool_droite == 1 ||
               bool_gauche == 1) // si le perso touche le sol et qu'une touche est appuyée
    {

        if (bool_gauche == 1 /* && go('G') == 0*/) {

            printf("anim course gauche \n");

            if (temps == 0) {
                temps =
                    SDL_GetTicks(); // on donne à la variable temps le nombre de miiseconde deuis le début du programme
                perso = mario_frame1_gauche; //frame 1
            }

            if (temps + 100 <=
                SDL_GetTicks()) //si la var temps +100 msec est inferieure au nb de ms depuis lme début du programme
            {
                perso = mario_frame2_gauche; //frame 2
            }
            if (temps + 200 <= SDL_GetTicks()) {
                perso = mario_frame3_gauche; //frame 3
                temps = 0; //on remet la variable temps à 0 pour recommencer l'annimation
            }

        }

        else if (bool_droite == 1) {
            //anim de course
            printf("anim course droite \n");

            if (temps == 0) {
                temps =
                    SDL_GetTicks(); // on donne à la variable temps le nombre de miiseconde deuis le début du programme
                perso = mario_frame1_droite; //frame 1
            }

            if (temps + 100 <=
                SDL_GetTicks()) //si la var temps +100 msec est inferieure au nb de ms depuis lme début du programme
            {
                perso = mario_frame2_droite; //frame 2
            }
            if (temps + 200 <= SDL_GetTicks()) {
                perso = mario_frame3_droite; //frame 3
                temps = 0; //on remet la variable temps à 0 pour recommencer l'annimation
            }
        }
    } else if (bool_gauche == 0 &&
               bool_droite == 0) //si le perso touche le sol et qu'aucune touche n'est appuyée
    {
        if (emp == 0) {
            perso = mario_idle_droite;
        } else {
            perso = mario_idle_gauche;
        }
    }
}
