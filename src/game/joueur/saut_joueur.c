#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "MARIO_joueur.h"
#include "MARIO_conditions.h"
#include "domain/physics.h"
#include "globals.h"

extern SDL_Rect pos_perso;
extern int jump, chute;
extern int init_hauteur_saut, init_hauteur_chute;
extern int bool_saut, bool_saut_sur_mechant;

void statue_saut(void) {
    if (go('B') == 1 && go('H') == 0 &&
        jump == 0) { //si perso sur sol, qu'il n'a pas d'obstacle et ne saut pas | saut classique
        init_hauteur_saut = pos_perso.y;
        jump = 1;
        x = 0.1;
    } else {
        bool_saut = 0;
    }

    if (bool_saut_sur_mechant == 1 &&
        go('H') == 0) { //si perso saut sur mechant et si il n'y a pas d'obstacle | saut "spécial"
        init_hauteur_saut = pos_perso.y;
        jump = 1;
        chute = 0;
        x = 0.1;
    } else {
        bool_saut_sur_mechant = 0;
        bool_saut = 0;
    }
}

void saut(void) {

    if (jump == 1 && go('H') == 0) {
        x += 0.1;
        if (bool_saut_sur_mechant == 1 && x <= domain_jump_threshold(1)) {
            pos_perso.y = init_hauteur_saut - domain_on_enemy_jump_arc(x);
        } else if (bool_saut_sur_mechant == 0 && x <= domain_jump_threshold(0)) {
            pos_perso.y = init_hauteur_saut - domain_jump_arc(x);
        }
    }
    if (domain_jump_should_end(jump, bool_saut_sur_mechant, go('H'), x)) {
        jump = 0;
        chute = 0;
    }
}

//-----------------------------------------------GRAVITE----------------------------------------------------//

void gravite(void) { //gere la position en y du personnage

    //INITIALISATION DE LA CHUTE
    if (domain_chute_should_start(jump, chute, go('B'))) {
        chute = 1;
        if (bool_saut_sur_mechant == 1) {
            init_hauteur_chute = pos_perso.y + domain_on_enemy_jump_arc(x);
            x = 8;
        } else {
            init_hauteur_chute = pos_perso.y + domain_jump_arc(11);
            x = 11;
        }
    }

    if (bool_saut_sur_mechant == 1) {
        if (domain_chute_is_active(chute, go('B'), 1, x)) {
            x += 0.1;
            pos_perso.y = init_hauteur_chute - domain_on_enemy_jump_arc(x);
            if (go('B') == 1) {
                x -= 0.1;
                pos_perso.y = init_hauteur_chute - domain_on_enemy_jump_arc(x);
                while (go('B') != 1) {
                    pos_perso.y += 1;
                }
                bool_saut_sur_mechant = 0;
            }
        }
    } else {
        if (domain_chute_is_active(chute, go('B'), 0, x)) {
            x += 0.1;
            pos_perso.y = init_hauteur_chute - domain_jump_arc(x);
            if (go('B') == 1) {
                x -= 0.1;
                pos_perso.y = init_hauteur_chute - domain_jump_arc(x);
                while (go('B') != 1) {
                    pos_perso.y += 1;
                }
            }
        }
    }
    if (domain_chute_should_end(chute, go('B'))) {
        chute = 0;
        if (bool_saut_sur_mechant == 1) {
            bool_saut_sur_mechant = 0;
        }
    }
    if (pos_perso.y > 440) {
        game_over();
    }
}
