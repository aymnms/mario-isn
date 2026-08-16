#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#include "display.h"
#include "MARIO_niveau.h"
#include "MARIO_conditions.h"
#include "MARIO_mechant.h"
#include "domain/level.h"
#include "path.h"
#include "globals.h"

int hautBlock = 50;
int largBlock = 50;
SDL_Texture *bloc;
SDL_Texture *fond;
SDL_Texture *cadeau;
SDL_Texture *eau;
SDL_Texture *pic;
SDL_Texture *drapeau;
SDL_Texture *hache;

SDL_Rect bobie;
SDL_Rect niveauOrigine;
extern int coin, niveau, vie;
extern char statue[MAX_MECHANTS];
extern SDL_Rect tableau_mechant[MAX_MECHANTS][4];
extern int direction_mechant[MAX_MECHANTS];
extern SDL_Rect pos_perso;
extern int decalage;

// init_skin() runs on every respawn and every level change (via
// init_niveau()), not just once at program start. These are fixed tile
// sprites, so the load is guarded to run only once -- previously every
// respawn/level change re-created them via create_texture() without ever
// freeing the previous one (never done anywhere in the codebase), leaking
// a texture each time.
static int level_skin_loaded = 0;

void init_skin(void) {
    if (level_skin_loaded) {
        return;
    }
    printf("initialisation skin\n");
    bloc = create_texture(path_img("block.png"));
    fond = create_texture(path_img("fondNuage.png"));
    cadeau = create_texture(path_img("cadeau.png"));
    eau = create_texture(path_img("eau.png"));
    pic = create_texture(path_img("pic.png"));
    drapeau = create_texture(path_img("drapeau.png"));
    hache = create_texture(path_img("axe.png"));
    level_skin_loaded = 1;
}

void addMechant(int pos_x, int pos_y) {
    auto int i;
    for (i = 0; i <= 19; i++) {
        if (statue[i] == 'M' || statue[i] == '0') {
            statue[i] = 'V';
            tableau_mechant[i][1].x = pos_x;
            tableau_mechant[i][1].y = 499 - pos_y;
            printf("champ added %d", i);
            direction_mechant[i] = 1;
            break;
        }
        if (i == 19) {
            printf("pas assez de place !!!");
        }
    }
}

void init_mechant(int ngh) {
    printf("init_mechant\n");

    switch (ngh) {
        case 1:
            addMechant(300, 200);
            addMechant(2985, 300);
            addMechant(2528, 236);
            break;

        case 2:
            addMechant(850, 200);
            addMechant(950, 200);
            addMechant(1750, 100);
            addMechant(2000, 100);
            addMechant(2200, 100);
            addMechant(2400, 100);
            addMechant(2600, 100);
            addMechant(3600, 100);
            addMechant(3650, 400);
            addMechant(4000, 400);
            break;

        case 3:
            addMechant(250, 100);
            addMechant(1000, 200);
            addMechant(1150, 100);
            addMechant(2600, 300);
            addMechant(2700, 300);
            addMechant(3550, 250);
            addMechant(4300, 151);
            addMechant(4400, 151);
            addMechant(4500, 151);
            addMechant(4600, 151);
            addMechant(4700, 151);
            addMechant(4800, 151);
            addMechant(4900, 151);
            addMechant(5050, 201);
            addMechant(5200, 251);
            addMechant(5350, 301);
            addMechant(5500, 261);
            addMechant(5650, 401);
            addMechant(5800, 451);
            break;

        case 4:
            addMechant(700, 150);
            addMechant(850, 150);
            addMechant(2250, 250);
            addMechant(2800, 400);
            addMechant(5100, 100);
            addBowser(6350, 50);
            break;

        case 5:
            break;

        case 6:
            break;
    }
}

void playerrrr(int ngh) {
    switch (ngh) {
        case 1:
            pos_perso.x = 150;
            pos_perso.y = 399;
            break;
        case 2:
            pos_perso.x = 150;
            pos_perso.y = 399;
            break;
        case 3:
            pos_perso.x = 150;
            pos_perso.y = 200;
            break;
        case 4:
            pos_perso.x = 150;
            pos_perso.y = 399;

            break;
        case 5:
            pos_perso.x = 150;
            pos_perso.y = 399;

            break;
        case 6:
            pos_perso.x = 150;
            pos_perso.y = 399;
            break;
    }
}

//4-> tuyeau
//5 -> eau
//9 -> pic

void niveauSelect(int nb) {
    // Zero-initialized: the switch below has no default case, so an
    // unhandled `nb` would leave this read uninitialized in the do-while
    // just below it (caught by GCC at -O3, -Wmaybe-uninitialized). '\0'
    // never appears as a level marker digit in niveau.lvl, so this can
    // only ever fail the file search cleanly instead of comparing against
    // garbage.
    auto char num = '\0';

    switch (nb) {
        case 1:
            num = '1';
            break;
        case 2:
            num = '2';
            break;
        case 3:
            num = '3';
            break;
        case 4:
            num = '4';
            break;
        case 5:
            num = '5';
            break;
        case 6:
            num = '6';
            break;
    }

    FILE *fichier = fopen(path_bin("niveau.lvl"), "r");
    if (fichier == NULL) {
        printf("echec ouverture niveau.txt");
        return;
    }

    if (fseek(fichier, 0, SEEK_END) != 0) {
        fprintf(stderr, "niveau.lvl: erreur de lecture\n");
        fclose(fichier);
        return;
    }
    long file_size = ftell(fichier);
    if (file_size < 0 || fseek(fichier, 0, SEEK_SET) != 0) {
        fprintf(stderr, "niveau.lvl: erreur de lecture\n");
        fclose(fichier);
        return;
    }

    char *data = malloc((size_t)file_size);
    if (data == NULL) {
        fprintf(stderr, "niveau.lvl: erreur d'allocation memoire\n");
        fclose(fichier);
        return;
    }

    size_t read_count = fread(data, 1, (size_t)file_size, fichier);
    fclose(fichier);

    // Parses the level block from the in-memory buffer -- see
    // domain/level.h. `lvl` is a genuinely contiguous 2D array in C, so
    // &lvl[0][0] is safe to fill row-major from a flat char*.
    domain_level_parse_result_t result =
        domain_parse_level(data, (int)read_count, num, LVL_ROWS, LVL_COLS, &lvl[0][0]);

    // Echoes exactly the prefix of the file the original fgetc()-driven
    // reader printed character by character as it went, since nothing else
    // wrote to stdout in between those printf("%c", ...) calls.
    fwrite(data, 1, (size_t)result.end_offset, stdout);
    free(data);

    if (result.status == DOMAIN_LEVEL_MARKER_NOT_FOUND) {
        fprintf(stderr, "niveau.lvl: marqueur du niveau %d introuvable (fin de fichier)\n", nb);
        return;
    }
    if (result.status == DOMAIN_LEVEL_UNEXPECTED_END) {
        fprintf(stderr, "niveau.lvl: fin de fichier inattendue en lisant le niveau %d\n", nb);
        return;
    }
    if (!result.trailer_valid) {
        printf("erreur  : dépacement \n");
    } //on test la nature du caractère (fin du tableau)

    printf("init mechant\n");
    init_mechant(nb);
    playerrrr(nb);
}

void niveauAfficher(int strawling) {
    printf("afficher niveau \n");
    niveauOrigine.x = -strawling;
    niveauOrigine.y = 0;

    // ALORS
    display_texture(fond, NULL, &niveauOrigine);

    int row, col;

    for (row = 0; row < LVL_ROWS; row++) {

        for (col = 0; col < LVL_COLS; col++) {

            switch (lvl[row][col]) {
                case '1':

                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = row * hautBlock;
                    // ALORS
                    display_texture(bloc, NULL, &bobie);
                    break;
                case '2':
                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = row * hautBlock;
                    // ALORS
                    display_texture(cadeau, NULL, &bobie);
                    break;
                case '5':

                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = row * hautBlock;
                    // ALORS
                    display_texture(cadeau, NULL, &bobie);
                    break;
                case '9':

                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = row * hautBlock;
                    // ALORS
                    display_texture(pic, NULL, &bobie);
                    break;
                case 'D':
                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = 0;
                    // ALORS
                    display_texture(drapeau, NULL, &bobie);
                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = row * hautBlock;
                    // ALORS
                    display_texture(bloc, NULL, &bobie);
                    break;
                case 'H':
                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = 350;
                    // ALORS
                    display_texture(hache, NULL, &bobie);
                    bobie.x = (col * largBlock) - strawling;
                    bobie.y = row * hautBlock;
                    // ALORS
                    display_texture(bloc, NULL, &bobie);
                    break;
            }
        }
    }
}
