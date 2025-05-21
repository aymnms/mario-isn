#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h> //musique

Mix_Music *musiqueFond; //Création d'un pointeur de type Mix_Music
   Mix_Music *musiqueMenu;
   Mix_Chunk *sonSaut;
   Mix_Chunk *sonBloc;
   Mix_Chunk *sonEnemy;
   Mix_Chunk *sonUp;
   Mix_Music *musiqueGameOver;
   Mix_Music *musiqueMiss;
   Mix_Music *musiquevictory;

void init_mus()
{
   
   Mix_AllocateChannels(32);
   SDL_WM_SetCaption("SDL_Mixer", NULL);
   if(Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1){printf("%s",Mix_GetError);}
   
   
   musiqueFond = Mix_LoadMUS("./musique/gameTheme.mp3"); //Chargement de la musique
   musiqueMenu = Mix_LoadMUS("./musique/mainTheme.mp3");
   sonSaut = Mix_LoadWAV("./musique/jumpSound.wav");
   sonBloc = Mix_LoadWAV("./musique/coinSound.wav");
   sonEnemy = Mix_LoadWAV("./musique/EnnemySound.wav");
   musiqueGameOver= Mix_LoadMUS("./musique/gameOver.wav");
   musiqueMiss= Mix_LoadMUS("./musique/miss.wav");
   musiquevictory= Mix_LoadMUS("./musique/victory.wav");
   sonUp= Mix_LoadWAV("./musique/up.wav");
}






void playSon(int son){
   switch(son)
   {
      case 1:
      Mix_PlayChannel(1, sonSaut, 0);
      break;
      case 2:
      Mix_PlayChannel(2, sonBloc, 0);
      break;
      case 3:
      Mix_PlayChannel(3, sonEnemy, 0);
      break;
      case 4:
      Mix_PlayChannel(3, sonUp, 0);
      break;
   }
   
}
void playMus(int son){
   Mix_HaltMusic(); //Arrête la musique
   switch(son)
   {
      case 1:
      printf("musique fond\n");
      Mix_PlayMusic(musiqueFond, -1);
      break;
      case 2:
      printf("musique menu\n");
      Mix_PlayMusic(musiqueMenu, -1);
      break;
      case 3:
      printf("musique miss\n");
      Mix_PlayMusic(musiqueMiss, 0);
      break;
      case 4:
      printf("musique gameOver\n");
      Mix_PlayMusic(musiqueGameOver, 0);
      break;
      case 5:
      printf("musique victory\n");
      Mix_PlayMusic(musiquevictory, 0);
      break;
      
   }
   
}

void freeMusic()
{
   Mix_FreeMusic(musiqueFond); //Libération de la musique
   Mix_CloseAudio(); //Fermeture de l'API
}