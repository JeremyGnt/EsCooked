#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H
/* * * * * * *
 *   MENU    *
 * * * * * * */
#define WIDTH 1248
#define HEIGHT 702

int menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* menu, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm,
          ALLEGRO_BITMAP* mrbeast, int state);

void declarationMenu(ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* menu);


#endif //ESCOOKED_MENU_H
