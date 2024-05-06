//
// Created by Enzol on 06/05/2024.
//
//
// Created by Enzol on 24/04/2024.
//
#define NOIR al_map_rgb(0,0,0)
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "fichierTexteMap.h"
#include "menu.h"

void afficherImage(ALLEGRO_BITMAP* buh, int x, int y, int R) {
    if(R){
        al_clear_to_color(NOIR);
    }
    al_draw_bitmap(buh, x, y, 0);
}

void menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* menu, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm,
           ALLEGRO_BITMAP* mrbeast, ImagesCuisine imagescuisine, ALLEGRO_BITMAP* fond, fichierTexteMap mapCuisine,
           sub Menu[4], bool fini, int window_width, int window_height){
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
                    al_draw_scaled_bitmap(fond, 0, 0, al_get_bitmap_width(fond), al_get_bitmap_height(fond), 0, 0, window_width, window_height, 0);
                    chargerImages(&imagescuisine);
                    chargerEtLireFichierTexte("../map1.txt", &mapCuisine);
                    break;
                }
                case QUIT :{
                    fini = true;
                    break;
                }
            }
            break;
        }
        case ALLEGRO_KEY_ESCAPE:{
            if(state == QUIT || state == OPT || state == CHARGE || state == NEW || state == JEU){
                state = MENUPRINCIPAL;
                afficherImage(menu, 0, 0, 1);
                afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
            }
            break;
        }
    }
}