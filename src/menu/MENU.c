/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxINIT_MENU.Cxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

int start_game()
void MENU()

xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>

#include "headers/MARIO_quit.h"
#include "headers/MARIO_musique.h"

//--Variable-generale--//
extern int run, run_game;
extern SDL_Event event;
//---------------------//

int repeat = 1, x, y;

int start_game(){
  playMus(2);
  repeat = 1;
  while (repeat){
    SDL_WaitEvent(&event);
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
    }
    if (event.type == SDL_QUIT){ //si la fenetre est fermé via la croix en haut à gauche
      return EXIT_SUCCESS; //on ferme le programme
    }
  }
  return 0;
}

void MENU(){
  start_game();
}