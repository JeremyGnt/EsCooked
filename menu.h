#ifndef ESCOOKED_MENU_H
#define ESCOOKED_MENU_H
/* * * * * * *
 *   MENU    *
 * * * * * * */
#define WIDTH 1248
#define HEIGHT 702
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "sons.h"



int menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* perso1, ALLEGRO_BITMAP* perso2,
          ALLEGRO_BITMAP* boxes, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm, int state,Sons *son);

void declarationMenu(ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* menu);

void transitionmenu(ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* perso, ALLEGRO_BITMAP* boxes);

#endif //ESCOOKED_MENU_H
