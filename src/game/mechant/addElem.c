
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>


//--------------------------Variable-générale--------------------------//
extern SDL_Surface *background;
extern int decalage;
extern char statue[19];
extern SDL_Surface *imgMechant; //surface du mechant
extern SDL_Rect tableau_mechant[19][4]; 
extern int nb_mechant;
int up = 0;
//---------------------------------------------------------------------//
void addChamp(int x, int y)
{
	for(int i = 0; i<= 19;i++)
	{
		if(statue[i] == 'M'||statue[i] == '0')
		{
			statue[i] = 'C';
			tableau_mechant[i][1].x = x;
			tableau_mechant[i][1].y = y;
			printf("champ added %d", i);

			break;
		}
	}
}
void grow()
{
	up =1;
	printf("growwwwwww\n");
}