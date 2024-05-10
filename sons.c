#include "sons.h"
#include "jeu.h"
#include "general.h"
#include "commandes.h"

void initialiserRessourcesAudio(Sons *son){

    if (!al_reserve_samples(5)) {
        fprintf(stderr, "Failed to reserve samples!\n");
    }

    son->mixer = al_get_default_mixer();
    son->musiqueMenu = al_load_sample("../Sons/walk-down-sesame-street-acoustic-gtr-loop-91bpm-143350.wav");
    son->musiqueJeu = al_load_sample("../Sons/busy-restaurant-dining-room-ambience-128466.wav");
    son->sonAccepter = al_load_sample("../Sons/interface-12-204786.wav");
    son->sonRetour = al_load_sample("../Sons/interface-10-204783.wav");

    son->instanceMusiqueMenu = al_create_sample_instance(son->musiqueMenu);
    al_set_sample_instance_playmode(son->instanceMusiqueMenu, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceMusiqueMenu,0.5);
    al_attach_sample_instance_to_mixer(son->instanceMusiqueMenu, son->mixer);

    son->instanceMusiqueJeu = al_create_sample_instance(son->musiqueJeu);
    al_set_sample_instance_playmode(son->instanceMusiqueJeu, ALLEGRO_PLAYMODE_LOOP);
    al_set_sample_instance_gain(son->instanceMusiqueJeu,0.5);
    al_attach_sample_instance_to_mixer(son->instanceMusiqueJeu, son->mixer);

    son->instanceSonAccepter = al_create_sample_instance(son->sonAccepter);
    al_set_sample_instance_playmode(son->instanceSonAccepter, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(son->instanceSonAccepter,0.5);
    al_attach_sample_instance_to_mixer(son->instanceSonAccepter, son->mixer);

    son->instanceSonRetour = al_create_sample_instance(son->sonRetour);
    al_set_sample_instance_playmode(son->instanceSonRetour, ALLEGRO_PLAYMODE_ONCE);
    al_set_sample_instance_gain(son->instanceSonRetour,0.5);
    al_attach_sample_instance_to_mixer(son->instanceSonRetour, son->mixer);

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

void jouerSonAccepter(Sons *son){
    if(son->instanceSonAccepter != NULL){
        al_play_sample_instance((son->instanceSonAccepter));
    }
}

void jouerSonRetour(Sons *son){
    if(son->instanceSonRetour != NULL){
        al_play_sample_instance((son->instanceSonRetour));
    }
}



