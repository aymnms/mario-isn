#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include "MARIO_musique.h"


extern SDL_Rect origine;
extern SDL_Surface *img, *background;


void init_fenetre(){
    init_mus();
    origine.x = 0; //on définit l'origine de la fenetre
    origine.y = 0;
    img = SDL_LoadBMP("./img/menu.bmp");

    SDL_Init(SDL_INIT_VIDEO);

    // Crée la fenêtre
    SDL_Window *window = SDL_CreateWindow("Super Mario ISN",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 500, SDL_WINDOW_SHOWN);

    // Crée le renderer (obligatoire pour afficher quoi que ce soit en SDL2)
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Définit l’icône de la fenêtre
    SDL_Surface *icon = SDL_LoadBMP("./img/sdl_icone.bmp");
    if (icon != NULL) {
        SDL_SetWindowIcon(window, icon);
        SDL_FreeSurface(icon);
    }

    // Montre le curseur (activé par défaut)
    SDL_ShowCursor(SDL_ENABLE);

    // Charge une image (par exemple avec SDL_LoadBMP, mais mieux : SDL_image)
    SDL_Surface *img = SDL_LoadBMP("./img/background.bmp"); // ← à remplacer si besoin
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