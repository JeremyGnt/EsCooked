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
#include "math.h"
#include "menu.h"
#include "fichierTexteMap.h"

void afficherImage(ALLEGRO_BITMAP* buh, int x, int y, int R) {
    if(R){
        al_clear_to_color(NOIR);
    }
    al_draw_bitmap(buh, x, y, 0);
}

void display(){
    al_flip_display();
}

void destroy(ALLEGRO_BITMAP* buh){
    al_destroy_bitmap(buh);
}

int main() {
    // Initialisations / Installations
    srand(time(NULL));
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(display);
    al_init_font_addon();
    al_init_ttf_addon();

    // Déclarations
    enum {BAS, HAUT, GAUCHE, DROITE, FBAS, FHAUT, FGAUCHE, FDROITE, ESPACE, NB_TOUCHES_GEREES};
    enum {ASSIETTE, TOMATE, STEAK, PAIN, BEACON, OIGNON};

    bool fini = false;
    float angle = 0;
    int toucheEnfoncer[NB_TOUCHES_GEREES] = {0};

    ALLEGRO_DISPLAY* fenetre = NULL;
    ALLEGRO_EVENT_QUEUE* queue = NULL;
    ALLEGRO_TIMER* timer = NULL;
    ALLEGRO_EVENT event;

    //BITMAPS
    ALLEGRO_BITMAP* mrbeast = NULL;
    ALLEGRO_BITMAP* transparent = NULL;
    ALLEGRO_BITMAP* menu = NULL;
    ALLEGRO_BITMAP* fleche = NULL;
    ALLEGRO_BITMAP* R = NULL;
    ALLEGRO_BITMAP* pseudo = NULL;
    ALLEGRO_BITMAP* confirm = NULL;
    ALLEGRO_BITMAP *Personnage1 = NULL;
    ALLEGRO_BITMAP *Personnage2 = NULL;
    ALLEGRO_BITMAP *Assiette = NULL;
    ALLEGRO_BITMAP* fond = NULL;

    //icone
    ALLEGRO_BITMAP* icone = NULL;
    icone = al_load_bitmap("..\\PNGS\\temp\\icone.png");
    assert(icone != NULL);

    // Création des éléments
    Joueur joueur1;
    Joueur joueur2;
    Element assiette;
    fichierTexteMap mapCuisine = {0};
    ImagesCuisine imagescuisine;

    joueur1.longueur = 60;
    joueur1.hauteur = 60;
    joueur1.x = WIDTH / 2;
    joueur1.y = HEIGHT / 2;
    joueur1.vitesse = 1;

    joueur2.longueur = 60;
    joueur2.hauteur = 60;
    joueur2.x = 0;
    joueur2.y = 0;
    joueur2.vitesse = 1.5;

    assiette.longueur = 40;
    assiette.hauteur = 40;
    assiette.x = WIDTH / 2;
    assiette.y = HEIGHT / 3;

    fenetre = al_create_display(WIDTH, HEIGHT);
    assert(fenetre != NULL);
    al_set_window_position(fenetre, 0, 0);
    al_set_window_title(fenetre, "word.exe");
    al_set_display_icon(fenetre, icone);
    timer = al_create_timer(1.0/200.0);
    queue = al_create_event_queue();
    al_clear_to_color(BLANCO);

    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    al_set_window_position(fenetre, 0, 0);
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
    assert(pseudo!=NULL);
    confirm = al_load_bitmap("..\\PNGS\\temp\\confirmation.png");
    assert(confirm != NULL);
    Personnage1 = al_load_bitmap("..\\images\\perso 1.png");
    assert(Personnage1 != NULL);
    Personnage2 = al_load_bitmap("..\\images\\perso 2.png");
    assert(Personnage2 != NULL);
    Assiette = al_load_bitmap("..\\PNGS\\temp\\assiette.png");
    assert(Assiette != NULL);
    fond = al_load_bitmap("..\\images\\fond.jpg");
    assert(fond != NULL);

    //init
    const char* charac = "a\0b\0c\0d\0e\0f\0g\0h\0i\0j\0k\0l\0m\0n\0o\0p\0q\0r\0s\0t\0u\0v\0w\0x\0y\0z\0";
    int window_width = al_get_display_width(fenetre);
    int window_height = al_get_display_height(fenetre);
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

    // Premier affichage
    afficherImage(menu, 0, 0, 1);
    afficherImage(fleche, Menu[pos].posX, Menu[pos].posY, 0);

    // Boucle d'événements
    al_start_timer(timer);
    while(!fini) {
        al_wait_for_event(queue, &event);
        switch(event.type) {
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
                case ALLEGRO_EVENT_TIMER: {
                    display();
                    break;
                }
            }
        }
        switch(state) {
            case JEU: {
                afficher_map(mapCuisine, &imagescuisine);
                if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_Z: {
                            toucheEnfoncer[HAUT] = true;
                            break;
                        }
                        case ALLEGRO_KEY_S: {
                            toucheEnfoncer[BAS] = true;
                            break;
                        }
                        case ALLEGRO_KEY_Q: {
                            toucheEnfoncer[GAUCHE] = true;
                            break;
                        }
                        case ALLEGRO_KEY_D: {
                            toucheEnfoncer[DROITE] = true;
                            break;
                        }
                    }
                } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
                    switch (event.keyboard.keycode) {
                        case ALLEGRO_KEY_Z: {
                            toucheEnfoncer[HAUT] = false;
                            break;
                        }
                        case ALLEGRO_KEY_S: {
                            toucheEnfoncer[BAS] = false;
                            break;
                        }
                        case ALLEGRO_KEY_Q: {
                            toucheEnfoncer[GAUCHE] = false;
                            break;
                        }
                        case ALLEGRO_KEY_D: {
                            toucheEnfoncer[DROITE] = false;
                            break;
                        }
                    }
                }
                if (toucheEnfoncer[HAUT]) {
                    angle = 0;
                }
                if (toucheEnfoncer[BAS]) {
                    angle = M_PI;
                }
                if (toucheEnfoncer[GAUCHE]) {
                    angle = (3 * M_PI) / 2;
                }
                if (toucheEnfoncer[DROITE]) {
                    angle = M_PI / 2;
                }
                if (toucheEnfoncer[HAUT] && toucheEnfoncer[GAUCHE]) {
                    angle = (7 * M_PI) / 4;
                }
                if (toucheEnfoncer[HAUT] && toucheEnfoncer[DROITE]) {
                    angle = M_PI / 4;
                }
                if (toucheEnfoncer[BAS] && toucheEnfoncer[GAUCHE]) {
                    angle = (5 * M_PI) / 4;
                }
                if (toucheEnfoncer[BAS] && toucheEnfoncer[DROITE]) {
                    angle = (3 * M_PI) / 4;
                }

                if (toucheEnfoncer[HAUT]) {
                    joueur1.y -= joueur1.vitesse;
                }
                if (toucheEnfoncer[BAS]) {
                    joueur1.y += joueur1.vitesse;
                }
                if (toucheEnfoncer[GAUCHE]) {
                    joueur1.x -= joueur1.vitesse;
                }
                if (toucheEnfoncer[DROITE]) {
                    joueur1.x += joueur1.vitesse;
                }

                afficherImage(transparent, 0, 0, 0);
                al_draw_rotated_bitmap(Personnage1, joueur1.longueur / 2, joueur1.hauteur / 2, joueur1.x, joueur1.y, angle, 0);
                display();
            }
        }
    }

    // Libérations
    al_destroy_display(fenetre);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    //al_destroy_font(ape);
    libererImages(&imagescuisine);
    al_destroy_bitmap(Personnage1);
    destroy(mrbeast);
    destroy(icone);
    destroy(transparent);
    destroy(menu);
    destroy(R);
    destroy(pseudo);
    destroy(confirm);
    return 0;
}