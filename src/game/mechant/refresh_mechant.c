#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "display.h"
#include "path.h"
#include "globals.h"

extern int decalage;
extern char statue[MAX_MECHANTS];
extern SDL_Texture *imgMechant; //surface du mechant
extern SDL_Rect tableau_mechant[MAX_MECHANTS][4];
extern int nb_mechant;

// afficher_mechant() runs up to 20x per frame (once per enemy slot). Each
// enemy state has a fixed, finite set of sprites, so they're loaded once
// here and reused -- previously every call did a fresh create_texture(),
// leaking a GPU texture every time (never freed anywhere in the codebase),
// which is what caused the reported memory leak/lag.
static SDL_Texture *img_goomba, *img_goomba_mort, *img_bowser, *img_void, *img_bowser_mort;
static int mechant_skin_loaded = 0;

static void init_mechant_skin(void) {
    if (mechant_skin_loaded) {
        return;
    }
    img_goomba = create_texture(path_img("goomba.png"));
    img_goomba_mort = create_texture(path_img("goomba_mort.png"));
    img_bowser = create_texture(path_img("bowser.png"));
    img_void = create_texture(path_img("void.png"));
    img_bowser_mort = create_texture(path_img("bowserMort.png"));
    mechant_skin_loaded = 1;
}

void afficher_mechant(void) {
    init_mechant_skin();

    if (statue[nb_mechant] == 'V') {           //SI LE MECHANT EST VIVANT
        imgMechant = img_goomba;               //on définit l'image du mechant
    } else if (statue[nb_mechant] == 'M') {
        imgMechant = img_goomba_mort;          //on définit l'image du mechant
    } else if (statue[nb_mechant] == 'B') {    //si c'est un champignon
        imgMechant = img_bowser;
    } else if (statue[nb_mechant] == '0') {
        imgMechant = img_void;
    } else if (statue[nb_mechant] == 'U') {
        imgMechant = img_bowser_mort;
    }

    tableau_mechant[nb_mechant][3] = tableau_mechant[nb_mechant][1];
    tableau_mechant[nb_mechant][3].x -= decalage;

    // ALORS
    display_texture(imgMechant, NULL, &tableau_mechant[nb_mechant][3]);
}