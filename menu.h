#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H
/* * * * * * *
 *   MENU    *
 * * * * * * */
#define WIDTH 1248
#define HEIGHT 702


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

/**********************
    *  CREATION DU MENU  *
    **********************/

enum{ EXIT, NEWGAME, CHARGEGAME, OPTIONS};
enum{ MENUPRINCIPAL, NEW, CHARGE, OPT, QUIT, JEU};

int pos = 0, state = MENUPRINCIPAL;

void menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* menu, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm,
           ALLEGRO_BITMAP* mrbeast, ImagesCuisine imagescuisine, ALLEGRO_BITMAP* fond, fichierTexteMap mapCuisine, sub Menu[4],bool fini
        , int window_width, int window_height);
void afficherImage(ALLEGRO_BITMAP* buh, int x, int y, int R);

#endif //ESCOOKED_MENU_H