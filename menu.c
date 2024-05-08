
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "stdio.h"
#include "menu.h"
#include "varmenu.h"
#include "sons.h"
#define NOIR al_map_rgb(0,0,0)


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
          ALLEGRO_BITMAP* mrbeast, int state,Sons son){
    jouerMusiqueMenu(&son);
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
                            arreterMusiqueMenu(&son);
                            jouerMusiqueJeu(&son);
                            break;
                        }
                        case 1:{
                            state = CHARGE;
                            afficherImage(mrbeast, 0, 0, 1);
                            arreterMusiqueMenu(&son);
                            jouerMusiqueJeu(&son);
                            break;
                        }
                        case 2:{
                            state = OPT;
                            afficherImage(mrbeast, 0, 0, 1);
                            arreterMusiqueMenu(&son);
                            break;
                        }
                        case 3:{
                            state = QUIT;
                            afficherImage(confirm, 0, 0, 1);
                            arreterMusiqueMenu(&son);
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
                arreterMusiqueJeu(&son);
                jouerMusiqueMenu(&son);
            }
            break;
        }
    }
    return state;
}