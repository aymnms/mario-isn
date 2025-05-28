#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>

#include "MARIO_quit.h"
#include "MARIO_musique.h"

extern int run, run_game;
extern SDL_Event event;

int repeat = 1, x, y;

int start_game(){
  playMus(2);
  repeat = 1;
  while (repeat){

    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_QUIT:
          repeat = 0;
          break;

        case SDL_MOUSEBUTTONDOWN:
          if(event.button.button == SDL_BUTTON_LEFT){ //si clique gauche
            x = event.button.x;
            y = event.button.y;
            if( 151 < x && x < 453 && 226 < y && y < 312 ){ //si clique dans "play" alors lance le jeu
              repeat = 0;playMus(1);

              if(run_game != 1){run_game = 1;}
            }else if( 151 < x && x < 453 && 332 < y && y < 416){ //si clicque dans "quit" alors quit le jeu
              quit(); //pour quitter le jeu
              repeat = 0; //arrete la boucle
              return EXIT_SUCCESS;
            }
            break;
          }
      }
    }
  }
  return 0;
}

void MENU(){
  start_game();
}