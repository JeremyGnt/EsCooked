
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "stdio.h"
#include "menu.h"
#include "varmenu.h"
#define NOIR al_map_rgb(0,0,0)


ALLEGRO_SAMPLE *music_menu = NULL;
ALLEGRO_SAMPLE *music_game = NULL;
ALLEGRO_SAMPLE_ID music_id;

void jouerMusique(ALLEGRO_SAMPLE *music, ALLEGRO_PLAYMODE playmode) {
    al_stop_sample(&music_id);
    al_play_sample(music, 1.0, 0.0, 1.0, playmode, &music_id);
}

int initialiserRessourcesAudio(){
    if (!al_install_audio()) {
        fprintf(stderr, "Failed to initialize audio!\n");
        return -1;
    }

    if (!al_init_acodec_addon()) {
        fprintf(stderr, "Failed to initialize audio codecs!\n");
        return -1;
    }

    if (!al_reserve_samples(10)) {
        fprintf(stderr, "Failed to reserve samples!\n");
        return -1;
    }

    ALLEGRO_SAMPLE *music_menu = al_load_sample("../Sons/rainy-day-in-town-with-birds-singing-194011.mp3");
    if (!music_menu) {
        fprintf(stderr, "Failed to load music for menu.\n");
        al_destroy_sample(music_menu);
    }

    ALLEGRO_SAMPLE *music_game = al_load_sample("../Sons/epic-music-loop-17027.mp3");
    if (!music_game) {
        fprintf(stderr, "Failed to load music for game.\n");
        al_destroy_sample(music_game);
    }
}

void afficherImage(ALLEGRO_BITMAP* buh, int x, int y, int R) {
    if(R){
        al_clear_to_color(NOIR);
    }
    al_draw_bitmap(buh, x, y, 0);
}

void declarationMenu(ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* menu){

    sub game = createSub(absc * 9, ord * 10, CHARGEGAME);
    sub newgame = createSub(absc * 9, ord * 16, NEWGAME);
    sub options = createSub(absc * 9, ord * 22, OPTIONS);
    sub exit = createSub(absc * 9, ord * 28, EXIT);

    Menu[0] = game;
    Menu[1] = newgame;
    Menu[2] = options;
    Menu[3] = exit;

    afficherImage(menu, 0, 0, 1);
    afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
}

int menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* menu, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm,
          ALLEGRO_BITMAP* mrbeast, int state){
    switch(event->keyboard.keycode){
        case ALLEGRO_KEY_DOWN :{
            switch(state){
                case MENUPRINCIPAL:{
                    afficherImage(menu, 0, 0, 1);
                    if(pos!=3){
                        afficherImage(fleche, Menu[pos+1].posX, Menu[pos+1].posY, 0);
                        pos = pos+1;
                    }
                    else{
                        afficherImage(fleche, Menu[0].posX, Menu[0].posY, 0);
                        pos = 0;
                    }
                }
            }
            break;
        }
        case ALLEGRO_KEY_UP :{
            switch(state){
                case MENUPRINCIPAL:{
                    afficherImage(menu, 0, 0, 1);
                    if(pos!=0){
                        afficherImage(fleche, Menu[pos-1].posX, Menu[pos-1].posY, 0);
                        pos = pos-1;
                    }
                    else{
                        afficherImage(fleche, Menu[3].posX, Menu[3].posY, 0);
                        pos = 3;
                    }
                    break;
                }
            }
            break;
        }
        case ALLEGRO_KEY_ENTER:{
            switch(state){
                case MENUPRINCIPAL:{
                    switch(pos){
                        case 0:{
                            state = NEW;
                            afficherImage(pseudo, 0, 0, 1);
                            /*
                            jouerMusique(music_game, ALLEGRO_PLAYMODE_LOOP);
                             */
                            break;
                        }
                        case 1:{
                            state = CHARGE;
                            afficherImage(mrbeast, 0, 0, 1);
                            break;
                        }
                        case 2:{
                            state = OPT;
                            afficherImage(mrbeast, 0, 0, 1);
                            break;
                        }
                        case 3:{
                            state = QUIT;
                            afficherImage(confirm, 0, 0, 1);
                            break;
                        }
                    }
                    break;
                }
                case NEW : {
                    state = JEU;
                    break;
                }
                case QUIT :{
                    state = OFF;
                    break;
                }
            }
            break;
        }
        case ALLEGRO_KEY_ESCAPE:{
            if(state == QUIT || state == OPT || state == CHARGE || state == NEW){
                state = MENUPRINCIPAL;
                afficherImage(menu, 0, 0, 1);
                afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
                /*
                jouerMusique(music_menu, ALLEGRO_PLAYMODE_LOOP);
                 */
            }
            break;
        }
    }
    return state;
}