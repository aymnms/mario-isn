#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "MARIO_musique.h"
#include "display.h"


extern SDL_Rect origine;
extern SDL_Surface *img, *background;


void init_fenetre(){
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

    // Définit l’icône de la fenêtre
    SDL_Surface *icon = IMG_Load("../img/sdl_icone.bmp");
    if (icon != NULL) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    // Montre le curseur (activé par défaut)
    SDL_ShowCursor(SDL_ENABLE);

    // Charge une image
    SDL_Surface *img = IMG_Load("../img/menu.bmp");
    SDL_Texture *background = SDL_CreateTextureFromSurface(renderer, img);
    SDL_FreeSurface(img); // plus besoin du SDL_Surface après création de la texture

    // Efface l’écran, dessine le fond, affiche
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, background, NULL, NULL); // Dessine toute l’image
    SDL_RenderPresent(renderer); // Met à jour l’écran
}

void init_menu(){ //gère l'organisation de l'execution des fonctions
    init_fenetre();
}