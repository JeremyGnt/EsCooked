#define WIDTH 1248
#define HEIGHT 702
#define NBMENU 20
#define SPACE 5
#define NOIR al_map_rgb(0,0,0)
#define BLANC al_map_rgb(255,255,255)
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "menu.h"


void afficherImage(ALLEGRO_BITMAP* kuh, int x, int y, int R) {
    if(R){
        al_clear_to_color(NOIR);
    }
    al_draw_bitmap(kuh, x, y, 0);
}

void display(){
    al_flip_display();
}

void destroy(ALLEGRO_BITMAP* buh){
    al_destroy_bitmap(buh);
}

int main() {
    // Initialisations / Installations
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());
    al_init_font_addon();
    al_init_ttf_addon();
    assert(al_init_image_addon());

    // Déclarations
    bool fini = false;
    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT event;
    //ALLEGRO_FONT* ape = al_load_ttf_font("C:\\Users\\Enzol\\Downloads\\font\\Apex-Black.ttf", 100, 0);

    //BITMAPS
    ALLEGRO_BITMAP* mrbeast = NULL;
    ALLEGRO_BITMAP* transparent = NULL;
    ALLEGRO_BITMAP* menu = NULL;
    ALLEGRO_BITMAP* fleche = NULL;
    ALLEGRO_BITMAP* R = NULL;
    ALLEGRO_BITMAP* pseudo = NULL;
    ALLEGRO_BITMAP* confirm = NULL;

    //icone
    ALLEGRO_BITMAP* icone = NULL;
    icone = al_load_bitmap("..\\PNGS\\temp\\icone.png");
    assert(icone != NULL);

    // Création des éléments
    fenetre = al_create_display(WIDTH, HEIGHT);
    assert(fenetre != NULL);
    al_set_window_title(fenetre, "word.exe");
    al_set_display_icon(fenetre, icone);
    timer = al_create_timer(1.0/200.0);

    queue = al_create_event_queue();
    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));


    al_set_window_position(fenetre, 0, 0);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_RESIZABLE);

    //assert(ape);

    //Images
    mrbeast = al_load_bitmap("..\\PNGS\\temp\\maxresdefault.jpg");
    assert(mrbeast != NULL);
    transparent = al_load_bitmap("..\\PNGS\\temp\\default.png");
    assert(transparent != NULL);
    menu = al_load_bitmap("..\\PNGS\\temp\\menu.png");
    assert(menu != NULL);
    fleche = al_load_bitmap("..\\PNGS\\temp\\fleche.png");
    assert(fleche != NULL);
    R = al_load_bitmap("..\\PNGS\\temp\\hardR.png");
    assert(R != NULL);
    pseudo = al_load_bitmap("..\\PNGS\\temp\\pseudomenu.png");
    assert(pseudo!=NULL);
    confirm = al_load_bitmap("..\\PNGS\\temp\\confirmation.png");
    assert(confirm != NULL);


    //init
    const char* charac = "a\0b\0c\0d\0e\0f\0g\0h\0i\0j\0k\0l\0m\0n\0o\0p\0q\0r\0s\0t\0u\0v\0w\0x\0y\0z\0";

    /**********************
     *  CREATION DU MENU  *
     **********************/

    enum{ EXIT, NEWGAME, CHARGEGAME, OPTIONS};
    enum{ MENUPRINCIPAL, NEW, CHARGE, OPT, QUIT, JEU};

    float abs = WIDTH / 62.4;
    float ord = HEIGHT / 35.1;

    sub Menu[4];

    sub game = createSub(abs * 9, ord * 10, CHARGEGAME);
    sub newgame = createSub(abs * 9, ord * 16, NEWGAME);
    sub options = createSub(abs * 9, ord * 22, OPTIONS);
    sub exit = createSub(abs * 9, ord * 28, EXIT);

    Menu[0] = game;
    Menu[1] = newgame;
    Menu[2] = options;
    Menu[3] = exit;

    int pos = 0, state = MENUPRINCIPAL;

    //TEXTE
    //char* texte = NULL;

    // Premier affichage
    afficherImage(menu, 0, 0, 1);
    afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);

    //Variables
    int a;
    float x, y;

    // Boucle d'événements
    al_start_timer(timer);
    while(!fini) {
        al_wait_for_event(queue, &event); // on pioche le prochain evenement dans la file
        switch(event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_CHAR: {
                switch(state){
                    case MENUPRINCIPAL:{
                        switch(event.keyboard.keycode){
                            case ALLEGRO_KEY_DOWN :{
                                afficherImage(menu, 0, 0, 1);
                                if(pos!=3){
                                    afficherImage(fleche, Menu[pos+1].posX, Menu[pos+1].posY, 0);
                                    pos = pos+1;
                                }
                                else{
                                    afficherImage(fleche, Menu[0].posX, Menu[0].posY, 0);
                                    pos = 0;
                                }
                                break;
                            }
                            case ALLEGRO_KEY_UP :{
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
                            case ALLEGRO_KEY_ENTER:{
                                switch(pos){
                                    case 0:{
                                        afficherImage(pseudo, 0, 0, 1);
                                        state = NEW;
                                        break;
                                    }
                                    case 1:{
                                        afficherImage(mrbeast, 0, 0, 1);
                                        state = CHARGE;
                                        break;
                                    }
                                    case 2:{
                                        afficherImage(mrbeast, 0, 0, 1);
                                        state = OPT;
                                        break;
                                    }
                                    case 3:{
                                        afficherImage(confirm, 0, 0, 1);
                                        state = QUIT;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    case NEW:{
                        switch (event.keyboard.keycode) {
                            case ALLEGRO_KEY_ESCAPE:{
                                state = MENUPRINCIPAL;
                                afficherImage(menu, 0, 0, 1);
                                afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
                                break;
                            }
                        }
                    }
                    case CHARGE:{
                        switch (event.keyboard.keycode) {
                            case ALLEGRO_KEY_ESCAPE:{
                                state = MENUPRINCIPAL;
                                afficherImage(menu, 0, 0, 1);
                                afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
                                break;
                            }
                        }
                    }
                    case OPT:{
                        switch (event.keyboard.keycode) {
                            case ALLEGRO_KEY_ESCAPE:{
                                state = MENUPRINCIPAL;
                                afficherImage(menu, 0, 0, 1);
                                afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
                                break;
                            }
                        }
                    }
                    case QUIT:{
                        switch (event.keyboard.keycode) {
                            case ALLEGRO_KEY_Y:{
                                fini = true;
                            }
                            case ALLEGRO_KEY_N:{
                                state = MENUPRINCIPAL;
                                afficherImage(menu, 0, 0, 1);
                                afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
                                break;
                            }
                        }
                    }
                }
            }
                /*
                if(buh){
                        char* current;
                        if(event.keyboard.keycode <= 26 && event.keyboard.keycode>=1){
                            a = event.keyboard.keycode;
                            current = &charac[(a-1)*2];
                        }
                        else{
                            a = 0;
                        }

                        float largeur = al_get_text_width(ape, current);
                        float hauteur = al_get_font_ascent(ape);
                        if(a){
                            al_draw_text(ape, BLANC, x, y, 0,current);
                            x = x + largeur + SPACE;
                        }
                        else{
                            switch(event.keyboard.keycode) {
                                case ALLEGRO_KEY_ESCAPE: {
                                    fini = true;
                                    break;
                                }
                                case ALLEGRO_KEY_SPACE: {
                                    x = x+largeur+SPACE;
                                    break;
                                }
                                case ALLEGRO_KEY_TAB: {
                                    al_draw_bitmap(mrbeast, 200, 800, 0);
                                    al_draw_text(ape, al_map_rgb(255, 255, 255),200, 600, 0, "MRBEAST");
                                    break;
                                }
                                case ALLEGRO_KEY_ENTER: {
                                    y = y+120;
                                    x = 0;
                                    break;
                                }
                                case ALLEGRO_KEY_BACKSPACE: {
                                    al_draw_filled_rectangle(x-largeur-SPACE , y, x, y+hauteur+15, NOIR);
                                    if(x>0){
                                        x = x - largeur - SPACE;
                                    }
                                    if(x<0){
                                        x = 0;
                                    }
                                    break;
                                }
                                case ALLEGRO_KEY_F4: {
                                    afficherImage(menu,0,0,1);
                                    x = 0;
                                    y = 0;
                                    break;
                                }
                            }
                        }
                        break;
                    }
                */
            case ALLEGRO_EVENT_TIMER: {
                display();
                break;
            }
            default: {
                al_flip_display();
            }
        }

    }

    // Libérations
    al_destroy_display(fenetre);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    //al_destroy_font(ape);
    destroy(mrbeast);
    destroy(icone);
    destroy(transparent);
    destroy(menu);
    destroy(R);
    destroy(pseudo);
    destroy(confirm);
    return 0;
}
