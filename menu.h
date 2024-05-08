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



int menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* menu, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm,
          ALLEGRO_BITMAP* mrbeast, int state, Sons *son);

void declarationMenu(ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* menu);

int initialiserRessourcesAudio();


#endif //ESCOOKED_MENU_H
