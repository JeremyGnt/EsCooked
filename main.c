#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "general.h"
#include "jeu.h"
#include "menu.h"
#include "sons.h"


#define NBMENU 20
#define SPACE 5
#define NOIR al_map_rgb(0,0,0)
#define BLANC al_map_rgb(255,255,255)

void destroy(ALLEGRO_BITMAP *buh) {
    al_destroy_bitmap(buh);
}

int main() {
    // Initialisations / Installations
    srand(time(NULL));
    assert(al_init());
    assert(al_init_primitives_addon());
    assert(al_init_image_addon());
    assert(al_install_keyboard());
    al_init_font_addon();
    assert(al_init_ttf_addon());
    assert(al_install_mouse());
    assert(al_install_audio());
    assert(al_init_acodec_addon());


    // Déclarations

    bool fini = false;

    RessourcesJeu *ressources = initRessourcesJeu();
    if (!ressources) {
        fprintf(stderr, "Failed to initialize game resources\n");
        return 1;
    }

    Sons son;

    //BITMAPS
    ALLEGRO_BITMAP *mrbeast = NULL;
    ALLEGRO_BITMAP *transparent = NULL;
    ALLEGRO_BITMAP *menu = NULL;
    ALLEGRO_BITMAP *fleche = NULL;
    ALLEGRO_BITMAP *R = NULL;
    ALLEGRO_BITMAP *pseudo = NULL;
    ALLEGRO_BITMAP *confirm = NULL;

    ALLEGRO_BITMAP *Fleche = NULL;
    ALLEGRO_BITMAP *boxesM = NULL;
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_BITMAP *perso1 = NULL;
    ALLEGRO_BITMAP *perso2 = NULL;
    ALLEGRO_BITMAP *pseudoM = NULL;
    ALLEGRO_BITMAP *confirM = NULL;

    //icone
    ALLEGRO_BITMAP *icone = NULL;
    icone = al_load_bitmap("..\\PNGS\\temp\\icone.png");
    assert(icone != NULL);


    al_set_window_position(ressources->display, 0, 0);
    al_set_window_title(ressources->display, "word.exe");
    al_set_display_icon(ressources->display, icone);
    al_clear_to_color(al_map_rgb(0, 0, 0));


    al_set_window_position(ressources->display, 0, 0);
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

    Fleche = al_load_bitmap("..\\PNGS\\ImagesMenu\\fleche.png");
    assert(Fleche != NULL);
    boxesM = al_load_bitmap("..\\PNGS\\ImagesMenu\\MenuBoxes.png");
    assert(boxesM != NULL);
    fond = al_load_bitmap("..\\PNGS\\ImagesMenu\\MenuFond.png");
    assert(fond != NULL);
    perso1 = al_load_bitmap("..\\PNGS\\ImagesMenu\\Perso1.png");
    assert(perso1 != NULL);
    perso2 = al_load_bitmap("..\\PNGS\\ImagesMenu\\Perso2.png");
    assert(perso2 != NULL);
    pseudoM = al_load_bitmap("..\\PNGS\\ImagesMenu\\MenuPseudo.png");
    assert(pseudoM != NULL);
    confirM = al_load_bitmap("..\\PNGS\\ImagesMenu\\QuitterConfirmation.png");
    assert(confirM != NULL);


    //init
    const char *charac = "a\0b\0c\0d\0e\0f\0g\0h\0i\0j\0k\0l\0m\0n\0o\0p\0q\0r\0s\0t\0u\0v\0w\0x\0y\0z\0";
    int window_width = al_get_display_width(ressources->display);
    int window_height = al_get_display_height(ressources->display);
    int retour = 0;


    enum {
        MENUPRINCIPAL, NEW, GUIDE, OPT, QUIT, JEU, OFF
    };
    int state = MENUPRINCIPAL;

    declarationMenu(fleche, menu);
    transitionmenu(Fleche, fond, perso1, boxesM);


    Joueur joueur1 = {
            .x = 424,
            .y = 361,
            .bitmap = al_load_bitmap("../images/perso 1.png"),
    };

    Joueur joueur2 = {
            .x = 824,
            .y = 361,
            .bitmap = al_load_bitmap("../images/perso 2.png"),
    };


    initialiserRessourcesAudio(&son);
    jouerMusiqueMenu(&son);


    // Boucle d'événements
    while (!fini) {
        ALLEGRO_EVENT event;
        al_wait_for_event(ressources->event_queue, &event);
        if(state == MENUPRINCIPAL && retour == 1){
            transitionmenu(Fleche, fond, perso1, boxesM);
            jouerMusiqueMenu(&son);
            retour = 0;
        }
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }


            case ALLEGRO_EVENT_KEY_DOWN: {
                if(state == QUIT || state == OPT || state == GUIDE || state == NEW || state == MENUPRINCIPAL){
                    state = menuf(&event, fond, Fleche, perso1, perso2,
                                      boxesM, pseudoM, confirM, state, &son);
                }
                if(state == JEU){
                    state = jeu(&joueur1, &joueur2, ressources);
                    arreterMusiqueJeu(&son);
                    retour = 1;
                }
                if(state == OFF){
                    fini = true;
                }
                break;
            }
            case ALLEGRO_EVENT_TIMER: {
                al_flip_display();
                break;
            }
        }
    }


    // Libérations
    detruireRessourcesJeu(ressources, &joueur1, &joueur2);
    destroy(mrbeast);
    destroy(icone);
    destroy(transparent);
    destroy(menu);
    destroy(R);
    destroy(pseudo);
    destroy(confirm);
    return 0;
}