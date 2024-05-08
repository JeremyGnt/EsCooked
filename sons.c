#include "sons.h"
#include "jeu.h"
#include "general.h"
#include "commandes.h"



ALLEGRO_SAMPLE *music_menu = NULL;
ALLEGRO_SAMPLE *music_game = NULL;
ALLEGRO_SAMPLE_INSTANCE *instanceMusiqueMenu;
ALLEGRO_SAMPLE_INSTANCE *instanceMusiquejeu;



int initialiserRessourcesAudio(Sons *son){

    if (!al_reserve_samples(5)) {
        fprintf(stderr, "Failed to reserve samples!\n");
        return -1;
    }

    son->musiqueMenu = al_load_sample("../Sons/rainy-day-in-town-with-birds-singing-194011.mp3");
    son->musiqueJeu = al_load_sample("../Sons/epic-music-loop-17027.mp3");

    son->instanceMusique = al_create_sample_instance(son->musiqueMenu);
    al_set_sample_instance_playmode(son->instanceMusique, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceMusique,0.5);
    al_play_sample_instance(son->instanceMusique);

}

void jouerMusiqueMenu(Sons *son){
    if(son->instanceMusique != NULL){
        al_play_sample_instance((son->instanceMusique));
    }
}

void arreterMusiqueMenu(Sons *son){
    if(son->instanceMusique != NULL){
        al_stop_sample_instance((son->instanceMusique));
    }
}

