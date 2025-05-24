#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL.h>



#include "MARIO_conditions.h"
#include "MARIO_mechant.h"
#include "MARIO_joueur.h"
#include "MARIO_game.h"
#include "MARIO_niveau.h"
#include "MARIO_musique.h"

extern char statue[20];
extern SDL_Rect tableau_mechant[20][4];  
extern int nb_mechant;
extern char statue[20];
extern int direction_mechant[20];
extern SDL_Rect pos_perso;
extern int decalage;
extern int bool_saut_sur_mechant;
int pv = 3;

void addBowser(int x, int y) {
    for(int i = 0; i<= 19;i++) {
        if (statue[i] == 'B'||statue[i] == '0') {
            statue[i] = 'B';
            tableau_mechant[i][1].x = x;
            tableau_mechant[i][1].y = y;
            
            direction_mechant[i] = 1;

            break;
        }
    }
}

// int goB(int direction){
//     int rep = 0;
//
//     auto SDL_Rect test1, test2, test3, test4;
//
//     //on définit 4 points pour positionner le mechant sur la grille du niveau
//
//     SDL_Rect BNO = tableau_mechant[nb_mechant][1];
//     BNO.x +=0;
//     BNO.y +=50;
//
//     SDL_Rect BNE = tableau_mechant[nb_mechant][1];
//     BNE.x += 100;
//     BNE.y += 50;
//
//     SDL_Rect BSE = tableau_mechant[nb_mechant][1];
//     BSE.x += 100;
//     BSE.y += 100;
//
//     SDL_Rect BSO = tableau_mechant[nb_mechant][1];
//     BSO.x += 0;
//     BSO.y += 100;
//
//     SDL_Rect BNNO = tableau_mechant[nb_mechant][1];
//     BNNO.x +=0;
//     BNNO.y +=0;
//
//     SDL_Rect BNNE = tableau_mechant[nb_mechant][1];
//     BNNE.x += 100;
//     BNNE.y += 0;
//
//     SDL_Rect BSSE = tableau_mechant[nb_mechant][1];
//     BSSE.x += 100;
//     BSSE.y += 150;
//
//     SDL_Rect BSSO = tableau_mechant[nb_mechant][1];
//     BSO.x +=0;
//     BSO.y += 150;
//
//     SDL_Rect BN = tableau_mechant[nb_mechant][1];
//     BN.x +=50;
//     BN.y +=0;
//
//     SDL_Rect BS = tableau_mechant[nb_mechant][1];
//     BS.x += 50;
//     BS.y += 150;
//     printf("goB(%d) : ", direction);
//
//
//
//
//     switch (direction){
//
//
//         case -1: //gauche
//             BNO.x--;BNNO.x--;BSSO.x--;BSO.x--;
//             test1 = setRectMechant(BNO);
//             test2 = setRectMechant(BNNO);
//             test3 = setRectMechant(BSO);
//             test4 = setRectMechant(BSSO);
//
//         break;
//
//         case 666: //bas (dans le cas où il y a un vide sous le méchant)
//             BSSO.y++;BSSE.y++;BS.y++;
//             test1 = setRectMechant(BSSO);
//             test2 = setRectMechant(BSSE);
//             test3 = setRectMechant(BS);
//         break;
//
//         case 1: //droite
//              BNE.x++;BNNE.x++;BSSE.x++;BSE.x++;
//             test1 = setRectMechant(BNE);
//             test2 = setRectMechant(BNNE);
//             test3 = setRectMechant(BSE);
//             test4 = setRectMechant(BSSE);
//
//         break;
//
//         case 999: //haut (pas utilisée dans le programme mais on pourrait imaginer son utilité en allant plus loin)
//
//             test1 = setRectMechant(BNNO);
//             test2 = setRectMechant(BNNE);
//             test3 = setRectMechant(BN);
//         break;
//     }
//     printf("test1 = %c\ntest2 = %c\ntest3 = %c\ntest4 = %c\n",lvl[test1.y][test1.x],lvl[test2.y][test2.x],lvl[test3.y][test3.x],lvl[test4.y][test4.x]);
//
//     if (lvl[test1.y][test1.x] == '1'|
//         lvl[test2.y][test2.x] == '1' |
//         lvl[test3.y][test3.x] == '1' |
//         lvl[test4.y][test4.x] == '1' )
//         {
//           rep = 1;
//     }
//     printf("%d\n", rep);
//
//
//     return rep;
// }
// void bowserMort()
// {
//     playSon(3);
//     statue[nb_mechant] = 'U';
//     tableau_mechant[nb_mechant][1].y = 500-120;
//     printf(" mechant %d mort\n", nb_mechant);
// }



// void contactB(){
//
//     if((pos_perso.x + decalage >= tableau_mechant[nb_mechant][1].x -49)&&
//             (pos_perso.x + decalage <= tableau_mechant[nb_mechant][1].x + 98)){
//
//                 // B. axe des y
//                 if(((pos_perso.y +50) >= (tableau_mechant[nb_mechant][1].y -5))&&
//                 ((pos_perso.y +50) <= (tableau_mechant[nb_mechant][1].y +5))){
//                     pv--;
//                     bool_saut_sur_mechant = 1;
//                     statue_saut();
//                     if(pv == 0){bowserMort();} //désactive le mechant
//
//
//         }
//         else if ((((pos_perso.x + decalage + 39) >= tableau_mechant[nb_mechant][1].x)&&
//             ((pos_perso.x + decalage + 39) <= (tableau_mechant[nb_mechant][1].x + 90)))|
//             (((pos_perso.x + decalage) >= tableau_mechant[nb_mechant][1].x)&&
//             ((pos_perso.x + decalage) <= (tableau_mechant[nb_mechant][1].x + 90))))
//         {
//             // B. axe des y
//             if ((pos_perso.y >= tableau_mechant[nb_mechant][1].y - 30)&&
//                 (pos_perso.y <=tableau_mechant[nb_mechant][1].y + 145)) {
//
//                     game_over(); //le personnage perd une vie
//
//             }
//         }
//     }
//
//
// }
