
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

    sub game = createSub(absc * 9, ord * 10, NEWGAME);
    sub newgame = createSub(absc * 9, ord * 16, GUIDE);
    sub options = createSub(absc * 9, ord * 22, OPTIONS);
    sub exit = createSub(absc * 9, ord * 28, EXIT);

    Menu[0] = game;
    Menu[1] = newgame;
    Menu[2] = options;
    Menu[3] = exit;

    //afficherImage(menu, 0, 0, 1);
    //afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
}


void transitionmenu(ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* perso, ALLEGRO_BITMAP* boxes){
    for(int i = 200; i >= 0; i = i- 10){
        afficherImage(fond, 0, 0, 0);
        afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
        afficherImage(perso, i, 0, 0);
    }
    afficherImage(boxes, 0, 0, 0);
}

void baseMenu( ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* perso, ALLEGRO_BITMAP* boxes){
    afficherImage(fond, 0, 0, 0);
    afficherImage(perso, 0, 0, 0);
    afficherImage(boxes, 0, 0, 0);
}

int menuf(ALLEGRO_EVENT* event, ALLEGRO_BITMAP* fond, ALLEGRO_BITMAP* fleche, ALLEGRO_BITMAP* perso1, ALLEGRO_BITMAP* perso2,
          ALLEGRO_BITMAP* boxes, ALLEGRO_BITMAP* pseudo, ALLEGRO_BITMAP* confirm, int state,Sons *son){
    switch(event->keyboard.keycode){
        case ALLEGRO_KEY_DOWN :{
            switch(state){
                case MENUPRINCIPAL:{
                    baseMenu(fond, perso1, boxes);
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
                    baseMenu(fond, perso1, boxes);
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
                            afficherImage(fond, 0, 0, 0);
                            afficherImage(pseudo, 0, 0, 0);
                            arreterMusiqueMenu(son);
                            jouerSonAccepter(son);
                            jouerMusiqueJeu(son);
                            break;
                        }
                        case 1:{
                            state = GUIDEMENU;
                            afficherImage(fond, 0, 0, 0);
                            afficherImage(perso2, 0, 0, 0);
                            arreterMusiqueMenu(son);
                            jouerSonAccepter(son);
                            break;
                        }
                        case 2:{
                            state = OPT;
                            afficherImage(fond, 0, 0, 0);
                            jouerSonAccepter(son);
                            break;
                        }
                        case 3:{
                            state = QUIT;
                            afficherImage(fond, 0, 0, 0);
                            afficherImage(perso1, 0, 0, 0);
                            afficherImage(confirm, 0, 0, 0);
                            jouerSonAccepter(son);
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
            if(state == QUIT || state == OPT || state == GUIDEMENU || state == NEW){
                state = MENUPRINCIPAL;
                transitionmenu(fleche, fond, perso1, boxes);
                arreterMusiqueJeu(son);
                jouerSonRetour(son);
                jouerMusiqueMenu(son);
            }
            break;
        }
    }
    return state;
}