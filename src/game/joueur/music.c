#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_mixer.h>
#include "path.h"

Mix_Music *musiqueFond; //Création d'un pointeur de type Mix_Music
Mix_Music *musiqueMenu;
Mix_Chunk *sonSaut;
Mix_Chunk *sonBloc;
Mix_Chunk *sonEnemy;
Mix_Chunk *sonUp;
Mix_Music *musiqueGameOver;
Mix_Music *musiqueMiss;
Mix_Music *musiquevictory;

void init_mus(void) {
    Mix_AllocateChannels(32);
    // window = SDL_CreateWindow("Mario ISN 2.0",
    //                            SDL_WINDOWPOS_CENTERED,
    //                            SDL_WINDOWPOS_CENTERED,
    //                            800, 600,
    //                            SDL_WINDOW_SHOWN);
    //
    // SDL_SetWindowTitle(window, "SDL_Mixer");

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) {
        printf("%s", Mix_GetError());
    }

    musiqueFond = Mix_LoadMUS(path_music("gameTheme.mp3")); //Chargement de la musique
    musiqueMenu = Mix_LoadMUS(path_music("mainTheme.mp3"));
    sonSaut = Mix_LoadWAV(path_music("jumpSound.wav"));
    sonBloc = Mix_LoadWAV(path_music("coinSound.wav"));
    sonEnemy = Mix_LoadWAV(path_music("EnnemySound.wav"));
    musiqueGameOver = Mix_LoadMUS(path_music("gameOver.wav"));
    musiqueMiss = Mix_LoadMUS(path_music("miss.wav"));
    musiquevictory = Mix_LoadMUS(path_music("victory.wav"));
    sonUp = Mix_LoadWAV(path_music("up.wav"));

    // None of these were ever checked -- a missing/corrupt asset silently
    // left the pointer NULL, and every later Mix_PlayMusic()/
    // Mix_PlayChannel() call on it is a silent no-op (SDL_mixer checks for
    // NULL internally), so the failure would only ever surface as "why is
    // there no sound" with nothing in the logs to explain why.
    if (!musiqueFond || !musiqueMenu || !sonSaut || !sonBloc || !sonEnemy || !musiqueGameOver ||
        !musiqueMiss || !musiquevictory || !sonUp) {
        fprintf(stderr, "init_mus: echec de chargement d'un asset audio: %s\n", Mix_GetError());
    }
}

void playSon(const int son) {
    switch (son) {
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
        default:
            break;
    }
}

void playMus(int son) {
    Mix_HaltMusic(); //Arrête la musique
    switch (son) {
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
        default:
            break;
    }
}

void freeMusic(void) {
    // Previously only musiqueFond was freed here -- the other 4 Mix_Music
    // and 4 Mix_Chunk loaded in init_mus() were never released, leaking
    // them for the life of the process (harmless in practice since this
    // only runs once at exit and the OS reclaims it, but still incomplete).
    Mix_FreeMusic(musiqueFond);
    Mix_FreeMusic(musiqueMenu);
    Mix_FreeMusic(musiqueGameOver);
    Mix_FreeMusic(musiqueMiss);
    Mix_FreeMusic(musiquevictory);
    Mix_FreeChunk(sonSaut);
    Mix_FreeChunk(sonBloc);
    Mix_FreeChunk(sonEnemy);
    Mix_FreeChunk(sonUp);
    Mix_CloseAudio(); //Fermeture de l'API
}
