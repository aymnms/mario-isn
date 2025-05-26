#include <stdlib.h>
#include <stdio.h>

#include "display.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "MARIO_niveau.h"
#include "MARIO_conditions.h"
#include "MARIO_mechant.h"

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
int l,c; //ligne et colonne
extern int coin, niveau, vie;
extern char statue[20];
extern SDL_Rect tableau_mechant[20][4]; 
extern int direction_mechant[20];
extern SDL_Texture *imgMechant; //surface du mechant
extern SDL_Rect pos_perso;
extern int decalage;

void init_skin() {
	printf ("initialisation skin\n");
	bloc = create_texture("../img/block.bmp");
	fond = create_texture("../img/fondNuage.bmp");
	cadeau = create_texture("../img/cadeau.bmp");
	eau = create_texture("../img/eau.bmp");
	pic = create_texture("../img/pic.bmp");
    drapeau = create_texture("../img/drapeau.bmp");
    hache = create_texture("../img/axe.bmp");
}

void addMechant(int x, int y) {
    auto int i;
    for(i = 0; i<= 19;i++) {
        if (statue[i] == 'M'||statue[i] == '0') {
            statue[i] = 'V';
            tableau_mechant[i][1].x = x;
            tableau_mechant[i][1].y = 499-y;
            printf("champ added %d", i);
            direction_mechant[i] = 1;
            break;
        }
        if (i == 19){printf("pas assez de place !!!");}
    }
}

void init_mechant(int ngh){
    printf("init_mechant\n");
    imgMechant = create_texture("../img/goomba.bmp"); //on définit l'image du mechant

    switch(ngh) {
        case 1:
            addMechant(300,200);
            addMechant(2985, 300);
            addMechant(2528, 236);
            break;

        case 2:
            addMechant(850,200);
            addMechant(950,200 );
            addMechant(1750,100 );
            addMechant(2000,100 );
            addMechant(2200,100);
            addMechant(2400,100 );
            addMechant(2600,100 );
            addMechant(3600,100 );
            addMechant(3650,400 );
            addMechant(4000,400 );
            break;

        case 3:
            addMechant(250,100);
            addMechant(1000,200);
            addMechant(1150,100);
            addMechant(2600,300);
            addMechant(2700,300);
            addMechant(3550,250);
            addMechant(4300,151);
            addMechant(4400,151);
            addMechant(4500,151);
            addMechant(4600,151);
            addMechant(4700,151);
            addMechant(4800,151);
            addMechant(4900,151);
            addMechant(5050,201);
            addMechant(5200,251);
            addMechant(5350,301);
            addMechant(5500,261);
            addMechant(5650,401);
            addMechant(5800,451);
            break;

        case 4:
            addMechant(700,150);
            addMechant(850,150);
            addMechant(2250,250);
            addMechant(2800,400);
            addMechant(5100,100);
            addBowser(6350,50);
            break;

        case 5:
            break;

        case 6:
            break;
    }
}

void playerrrr(int ngh) {
    switch(ngh)
    {
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

void niveauSelect(int nb)
{
	FILE* fichier = NULL;
	auto char num;
    auto int *nbM, xM, yM;

    fichier = fopen("../bin/niveau.lvl", "r");
    char caract;
    switch (nb)
    {
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


    if (fichier != NULL)
    {
        do //recherche du bon tableau
        {
            do //recherche des limittes d'un tableau
            {
                caract = fgetc(fichier); //caractère en cour
                printf("%c",caract);
            }while(caract != '#'); //on test la nature du caractère (début du tableau)
            caract = fgetc(fichier); //caractère en cour
            printf("%c",caract);
        }while(caract != num); //on test la nature du caractère (bon niveau)

        for(l = 0; l<10;l++) //pour chaque ligne
        {
            for(c = 0;c<140;c++) //pour chaque colonnes
            {
                caract = fgetc(fichier); //caractère en cour
                printf("%c",caract);
                if(caract == '\n'){caract = fgetc(fichier);} //on test la nature du caractère
                lvl[l][c] = caract;
            }
        }
        caract = fgetc(fichier); //caractère en cour
        printf("%c",caract);
        caract = fgetc(fichier); //caractère en cour
        printf("%c",caract);
        if(caract != '@'){printf("erreur  : dépacement \n");} //on test la nature du caractère (fin du tableau)
        printf("init mechant\n");
        init_mechant(nb);
        playerrrr(nb);


        fclose(fichier); // On ferme le fichier qui a été ouvert
    }else{printf("echec ouverture niveau.txt");} //dbg si échec du chargement
}

void niveauAfficher(int strawling)
{
	printf("afficher niveau \n");
	niveauOrigine.x = -strawling;
	niveauOrigine.y = 0;

	// ALORS
	display_texture(fond, NULL, &niveauOrigine);

	int l,c;


	for (l=0; l<10; l++)
	{

		for (c = 0; c<140; c++)
		{

			switch (lvl[l][c])
			{
				case '1':

					bobie.x = (c*largBlock) - strawling;
					bobie.y = l*hautBlock;
					// ALORS
					display_texture(bloc, NULL, &bobie);
					break;
				case '2':
					bobie.x = (c*largBlock) - strawling;
					bobie.y = l*hautBlock;
					// ALORS
					display_texture(cadeau, NULL, &bobie);
					break;
				case '5':

					bobie.x = (c*largBlock) - strawling;
					bobie.y = l*hautBlock;
					// ALORS
					display_texture(cadeau, NULL, &bobie);
					break;
				case '9':

					bobie.x = (c*largBlock) - strawling;
					bobie.y = l*hautBlock;
					// ALORS
					display_texture(pic, NULL, &bobie);
					break;
                case 'D':
                    bobie.x = (c*largBlock) - strawling;
                    bobie.y = 0;
					// ALORS
					display_texture(drapeau, NULL, &bobie);
                    bobie.x = (c*largBlock) - strawling;
                    bobie.y = l*hautBlock;
					// ALORS
					display_texture(bloc, NULL, &bobie);
                    break;
                case 'H':
                    bobie.x = (c*largBlock) - strawling;
                    bobie.y = 350;
					// ALORS
					display_texture(hache, NULL, &bobie);
                    bobie.x = (c*largBlock) - strawling;
                    bobie.y = l*hautBlock;
					// ALORS
					display_texture(bloc, NULL, &bobie);
                    break;
			}
		}
	}
}
