#ifndef ESCOOKED_SONS_H
#define ESCOOKED_SONS_H

#include "general.h"
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>



typedef struct{
    ALLEGRO_SAMPLE *musiqueMenu;
    ALLEGRO_SAMPLE *musiqueJeu;
    ALLEGRO_SAMPLE_INSTANCE *instanceMusiqueMenu;
    ALLEGRO_SAMPLE_INSTANCE *instanceMusiqueJeu;
    ALLEGRO_MIXER *mixer;
}Sons;


void initialiserRessourcesAudio(Sons *son);

void arreterMusiqueMenu(Sons *son);

void jouerMusiqueMenu(Sons *son);

void arreterMusiqueJeu(Sons *son);

void jouerMusiqueJeu(Sons *son);


#endif
