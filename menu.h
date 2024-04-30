#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H
/* * * * * * *
 *   MENU    *
 * * * * * * */

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

typedef struct {
    float x, y, longueur, hauteur, vitesse, collisionDetecter, score;
} Joueur;

typedef struct {
    float x, y, longueur, hauteur;
} Element;

#endif //ESCOOKED_MENU_H