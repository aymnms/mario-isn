#pragma once

// Renvoie un chemin ABSOLU pour "img/xxx.png", "musique/xxx.mp3", "bin/xxx.lvl", etc.
// Résolution basée sur l'emplacement de l'exécutable (SDL_GetBasePath),
// gère aussi le bundle macOS (.app/Contents/Resources) et le layout de dev.
char* asset_path(const char *subpath);

// Raccourcis
char* path_img(const char *filename);
char* path_music(const char *filename);
char* path_bin(const char *filename);
