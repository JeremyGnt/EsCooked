#include "sons.h"
#include "jeu.h"
#include "general.h"
#include "commandes.h"

int initialiserRessourcesAudio(Sons *son){

    if (!al_reserve_samples(5)) {
        fprintf(stderr, "Failed to reserve samples!\n");
        return -1;
    }

    son->musiqueMenu = al_load_sample("../Sons/rainy-day-in-town-with-birds-singing-194011.mp3");
    son->musiqueJeu = al_load_sample("../Sons/epic-music-loop-17027.mp3");

    son->instanceMusiqueMenu = al_create_sample_instance(son->musiqueMenu);
    al_set_sample_instance_playmode(son->instanceMusiqueMenu, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceMusiqueMenu,1);

    son->instanceMusiqueJeu = al_create_sample_instance(son->musiqueJeu);
    al_set_sample_instance_playmode(son->instanceMusiqueJeu, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceMusiqueJeu,1);

}

void jouerMusiqueMenu(Sons *son){
    if(son->instanceMusiqueMenu != NULL){
        al_play_sample_instance((son->instanceMusiqueMenu));
    }
}

void arreterMusiqueMenu(Sons *son){
    if(son->instanceMusiqueMenu != NULL){
        al_stop_sample_instance((son->instanceMusiqueMenu));
    }
}

void jouerMusiqueJeu(Sons *son){
    if(son->instanceMusiqueJeu != NULL){
        al_play_sample_instance((son->instanceMusiqueJeu));
    }
}

void arreterMusiqueJeu(Sons *son){
    if(son->instanceMusiqueJeu != NULL){
        al_stop_sample_instance((son->instanceMusiqueJeu));
    }
}

