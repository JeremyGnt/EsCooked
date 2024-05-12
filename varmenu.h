#ifndef ESCOOKED_VARMENU_H
#define ESCOOKED_VARMENU_H

#endif //ESCOOKED_VARMENU_H

struct sousMenu{
    float posX, posY;
    int type;
};
typedef struct sousMenu sub;

sub createSub(float x, float y, int type){
    sub s;
    s.posX = x;
    s.posY = y;
    s.type = type;
    return s;
}



/**********************
    *  CREATION DU MENU  *
    **********************/

enum{ EXIT, NEWGAME, GUIDE, OPTIONS};
enum {
    MENUPRINCIPAL, NEW, GUIDEMENU, OPT, QUIT, JEU, OFF, PSEUDO1, PSEUDO2
};

int pos = 0;

float absc = WIDTH / 62.4;
float ord = HEIGHT / 35.1;

sub Menu[4];


