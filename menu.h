#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H
/* * * * * * *
 *   MENU    *
 * * * * * * */
#define WIDTH 1248
#define HEIGHT 702



int menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* menu, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm,
          ALLEGRO_BITMAP* mrbeast, ImagesCuisine imagescuisine, ALLEGRO_BITMAP* fond, fichierTexteMap mapCuisine
        , int window_width, int window_height);
void afficherImage(ALLEGRO_BITMAP* buh, int x, int y, int R);

void declarationMenu(ALLEGRO_BITMAP* fleche);

#endif //ESCOOKED_MENU_H