#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "MARIO_musique.h"
#include "display.h"

extern SDL_Rect origine;

void init_fenetre(void) {
    init_mus();
    origine.x = 0; //on définit l'origine de la fenetre
    origine.y = 0;

    init_display();

    // Gestion erreur load image
    int flags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(flags) & flags)) {
        fprintf(stderr, "Erreur init SDL_image: %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Montre le curseur (activé par défaut)
    SDL_ShowCursor(SDL_ENABLE);
}

void init_menu(void) { //gère l'organisation de l'execution des fonctions
    init_fenetre();
}