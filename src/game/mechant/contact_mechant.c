#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>

#include "MARIO_conditions.h"
#include "MARIO_mechant.h"
#include "MARIO_joueur.h"
#include "MARIO_game.h"
#include "MARIO_niveau.h"
#include "MARIO_musique.h"
#include "domain/collision.h"
#include "domain/tile.h"
#include "globals.h"

//--------------------------Variable-générale--------------------------//

extern SDL_Rect pos_perso;
extern int decalage;
extern char statue[MAX_MECHANTS];
extern SDL_Rect tableau_mechant[MAX_MECHANTS][4];
extern int nb_mechant;
extern int jump, chute, bool_saut_sur_mechant;
extern int init_hauteur_saut, init_hauteur_chute;
extern int vie;
//---------------------------------------------------------------------//

int goM(int direction) {
    // Zero-initialized: same reasoning as goB() in bowser.c -- the switch
    // below has no default case, so an unhandled `direction` would leave
    // these read uninitialized just below (caught by GCC at -O3,
    // -Wmaybe-uninitialized). lvl[0][0] is always a valid in-bounds cell.
    auto SDL_Rect test1 = {0}, test2 = {0};

    //on définit 4 points pour positionner le mechant sur la grille du niveau

    SDL_Rect position_mechant_NO = tableau_mechant[nb_mechant][1];
    position_mechant_NO.x += 2;
    position_mechant_NO.y += 2;

    SDL_Rect position_mechant_NE = tableau_mechant[nb_mechant][1];
    position_mechant_NE.x += 47;
    position_mechant_NE.y += 2;

    SDL_Rect position_mechant_SE = tableau_mechant[nb_mechant][1];
    position_mechant_SE.x += 47;
    position_mechant_SE.y += 50;

    SDL_Rect position_mechant_SO = tableau_mechant[nb_mechant][1];
    position_mechant_SO.x += 8;
    position_mechant_SO.y += 50;

    switch (direction) {

        case -1: //gauche
            position_mechant_NO.x--;
            position_mechant_SO.x--;
            test1 = setRectMechant(position_mechant_NO);
            test2 = setRectMechant(position_mechant_SO);
            break;

        case 666: //bas (dans le cas où il y a un vide sous le méchant)
            position_mechant_SE.y++;
            position_mechant_SO.y++;
            test1 = setRectMechant(position_mechant_SE);
            test2 = setRectMechant(position_mechant_SO);
            break;

        case 1: //droite
            position_mechant_NE.x++;
            position_mechant_SE.x++;
            test1 = setRectMechant(position_mechant_NE);
            test2 = setRectMechant(position_mechant_SE);
            break;

        case 999: //haut (pas utilisée dans le programme mais on pourrait imaginer son utilité en allant plus loin)
            position_mechant_NO.y++;
            position_mechant_NE.y++;
            test1 = setRectMechant(position_mechant_NO);
            test2 = setRectMechant(position_mechant_NE);
            break;
    }

    // Reuses the pure classification already extracted from go() (J5-3e) --
    // goM() only ever needs "is this tile blocking at all", never which
    // kind, so this is a strict subset of what domain_classify_tile()
    // already computes. Also fixes a redundant disjunct the previous
    // inline check had here (`(A||B) || (A&&B)` is just `(A||B)`, the
    // second half could never add a case the first didn't already cover;
    // see AUDIT.md §10).
    return domain_classify_tile(lvl[test1.y][test1.x], lvl[test2.y][test2.x]) != DOMAIN_TILE_NONE;
}

void mechantMort(void) { //detruit le perso
    playSon(3);
    statue[nb_mechant] = 'M';
    printf(" mechant %d mort\n", nb_mechant);
}

void contact_lateral(void) { //si le mechant et le personnage se touchent verticalement

    if (statue[nb_mechant] != 'M') {
        if (domain_contact_lateral(pos_perso, decalage, tableau_mechant[nb_mechant][1])) {
            game_over(); //le personnage perd une vie
        }
    }
}

void contact_vertical(void) { //si le personnage est au dessus du méchant

    if (statue[nb_mechant] != 'M' && chute == 1) {
        if (domain_lands_on_top(pos_perso, decalage, tableau_mechant[nb_mechant][1])) {
            if (statue[nb_mechant] == 'V') {
                bool_saut_sur_mechant = 1;
                statue_saut();
                mechantMort(); //désactive le mechant
            } else {
                game_over();
            }
        }
    }
}

void contact(void) {
    if (statue[nb_mechant] == 'V') {
        contact_lateral(); //si touche perso latérallement
        contact_vertical();
    } else if (statue[nb_mechant] == 'B') {
        contactB();
    }
}