#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include "general.h"
#include "jeu.h"
#include "varmenu.h"


#define NBMENU 20
#define SPACE 5
#define NOIR al_map_rgb(0,0,0)
#define BLANC al_map_rgb(255,255,255)

void destroy(ALLEGRO_BITMAP *buh) {
    al_destroy_bitmap(buh);
}
void afficherImage(ALLEGRO_BITMAP* buh, int x, int y, int R) {
    if(R){
        al_clear_to_color(NOIR);
    }
    al_draw_bitmap(buh, x, y, 0);
}

void declarationMenu(ALLEGRO_BITMAP* fleche){

    sub game = createSub(absc * 9, ord * 10, CHARGEGAME);
    sub newgame = createSub(absc * 9, ord * 16, NEWGAME);
    sub options = createSub(absc * 9, ord * 22, OPTIONS);
    sub exit = createSub(absc * 9, ord * 28, EXIT);

    Menu[0] = game;
    Menu[1] = newgame;
    Menu[2] = options;
    Menu[3] = exit;

    afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
}
int main() {
    // Initialisations / Installations
    srand(time(NULL));
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    al_init_font_addon();
    al_init_ttf_addon();

    // Déclarations

    bool fini = false;
    GameResources *resources = initGameResources();
    if (!resources) {
        fprintf(stderr, "Failed to initialize game resources\n");
        return 1;
    }

    //BITMAPS
    ALLEGRO_BITMAP *mrbeast = NULL;
    ALLEGRO_BITMAP *transparent = NULL;
    ALLEGRO_BITMAP *menu = NULL;
    ALLEGRO_BITMAP *fleche = NULL;
    ALLEGRO_BITMAP *R = NULL;
    ALLEGRO_BITMAP *pseudo = NULL;
    ALLEGRO_BITMAP *confirm = NULL;

    //icone
    ALLEGRO_BITMAP *icone = NULL;
    icone = al_load_bitmap("..\\PNGS\\temp\\icone.png");
    assert(icone != NULL);


    al_set_window_position(resources->display, 0, 0);
    al_set_window_title(resources->display, "word.exe");
    al_set_display_icon(resources->display, icone);
    al_clear_to_color(al_map_rgb(0, 0, 0));


    al_set_window_position(resources->display, 0, 0);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_RESIZABLE);

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
    assert(pseudo != NULL);
    confirm = al_load_bitmap("..\\PNGS\\temp\\confirmation.png");
    assert(confirm != NULL);


    //init
    const char *charac = "a\0b\0c\0d\0e\0f\0g\0h\0i\0j\0k\0l\0m\0n\0o\0p\0q\0r\0s\0t\0u\0v\0w\0x\0y\0z\0";
    int window_width = al_get_display_width(resources->display);
    int window_height = al_get_display_height(resources->display);


    enum {
        MENUPRINCIPAL, NEW, CHARGE, OPT, QUIT, JEU, OFF
    };
    int state;
    declarationMenu(fleche);

    Joueur joueur1 = {
            .x = 424,
            .y = 361,
            .bitmap = al_load_bitmap("../images/perso 1.png"),
            .vitesse = 1.5
    };

    Joueur joueur2 = {
            .x = 824,
            .y = 361,
            .bitmap = al_load_bitmap("../images/perso 2.png"),
            .vitesse = 1.5
    };

    if (!joueur1.bitmap || !joueur2.bitmap) {
        fprintf(stderr, "Failed to load player bitmaps\n");
        destroyGameResources(resources);
        return -1;
    }




    // Boucle d'événements
    while (!fini) {
        ALLEGRO_EVENT event;
        al_wait_for_event(resources->event_queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }
            case ALLEGRO_EVENT_KEY_DOWN: {
                switch(event.keyboard.keycode){
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
                                jeu(&joueur1, &joueur2, resources);
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
                        if(state == QUIT || state == OPT || state == CHARGE || state == NEW || state == JEU){
                            state = MENUPRINCIPAL;
                            afficherImage(menu, 0, 0, 1);
                            afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);
                        }
                        break;
                    }
                }
            }
            case ALLEGRO_EVENT_TIMER: {
                al_flip_display();
                break;
            }
        }
    }


    // Libérations
    destroyGameResources(resources);
    destroy(mrbeast);
    destroy(icone);
    destroy(transparent);
    destroy(menu);
    destroy(R);
    destroy(pseudo);
    destroy(confirm);
    return 0;
}