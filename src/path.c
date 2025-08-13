#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

#define PATH_MAX_LEN 4096
static char g_path_buf[PATH_MAX_LEN];

static int file_exists(const char *p) {
    FILE *f = fopen(p, "rb");
    if (f) { fclose(f); return 1; }
    return 0;
}

static void join2(char *dst, const char *a, const char *b) {
    snprintf(dst, PATH_MAX_LEN, "%s%s", a, b);
}

static void join3(char *dst, const char *a, const char *b, const char *c) {
    snprintf(dst, PATH_MAX_LEN, "%s%s%s", a, b, c);
}

char* asset_path(const char *subpath) {
    char *base = SDL_GetBasePath(); // heap-alloc par SDL
    if (!base) {
        snprintf(g_path_buf, PATH_MAX_LEN, "%s", subpath);
        return g_path_buf;
    }

    // 1) base + subpath
    join2(g_path_buf, base, subpath);
    if (file_exists(g_path_buf)) { SDL_free(base); return g_path_buf; }

    // 2) cas bundle macOS: .../Contents/MacOS/
    if (strstr(base, "/Contents/MacOS/")) {
        char buf2[PATH_MAX_LEN];

        // Resources dans le bundle
        join3(buf2, base, "../Resources/", subpath);
        if (file_exists(buf2)) { SDL_free(base); snprintf(g_path_buf, PATH_MAX_LEN, "%s", buf2); return g_path_buf; }

        // Layout de dev (depuis MacOS -> racine projet)
        join3(buf2, base, "../../../", subpath);
        if (file_exists(buf2)) { SDL_free(base); snprintf(g_path_buf, PATH_MAX_LEN, "%s", buf2); return g_path_buf; }
    } else {
        // 3) exécutable hors bundle : remonter d'1–2 niveaux
        char buf2[PATH_MAX_LEN];
        join3(buf2, base, "../", subpath);
        if (file_exists(buf2)) { SDL_free(base); snprintf(g_path_buf, PATH_MAX_LEN, "%s", buf2); return g_path_buf; }
        join3(buf2, base, "../../", subpath);
        if (file_exists(buf2)) { SDL_free(base); snprintf(g_path_buf, PATH_MAX_LEN, "%s", buf2); return g_path_buf; }
    }

    // 4) fallback : renvoyer tel quel (permet l'exécution depuis la racine projet)
    SDL_free(base);
    snprintf(g_path_buf, PATH_MAX_LEN, "%s", subpath);
    return g_path_buf;
}

static char* asset_path_cat(const char *prefix, const char *filename) {
    char sub[PATH_MAX_LEN];
    snprintf(sub, PATH_MAX_LEN, "%s%s", prefix, filename);
    return asset_path(sub);
}

char* path_img(const char *filename)   { return asset_path_cat("img/", filename); }
char* path_music(const char *filename) { return asset_path_cat("musique/", filename); }
char* path_bin(const char *filename)   { return asset_path_cat("bin/", filename); }