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
#define SPACE 1
#define NOIR al_map_rgb(0,0,0)
#define BLANC al_map_rgb(255,255,255)

void destroy(ALLEGRO_BITMAP *buh) {
    al_destroy_bitmap(buh);
}

void initialiserJoueurs(Joueur *joueur1, Joueur *joueur2) {
    joueur1->x = 424;
    joueur1->y = 361;
    joueur1->vx = 0;
    joueur1->vy = 0;
    joueur1->angle = 0;
    joueur1->ingredient = NULL;
    joueur1->bitmap = al_load_bitmap("../images/perso 1.png");

    joueur2->x = 824;
    joueur2->y = 361;
    joueur2->vx = 0;
    joueur2->vy = 0;
    joueur2->angle = 0;
    joueur2->ingredient = NULL;
    joueur2->bitmap = al_load_bitmap("../images/perso 2.png");
}

void reinitialiserRessourcesJeu(RessourcesJeu *ressources) {
    if (ressources) {
        ressources->startTime = al_get_time();
        ressources->tempsAccumulePause = 0;

        // Réinitialiser la liste des items lâchés
        for (int i = 0; i < 10; i++) {
            if (ressources->ItemLaches.items[i]) {
                free(ressources->ItemLaches.items[i]);
                ressources->ItemLaches.items[i] = NULL;
            }
        }
        ressources->ItemLaches.compte = 0;
    }
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
    ALLEGRO_BITMAP *R = NULL;

    ALLEGRO_BITMAP *Fleche = NULL;
    ALLEGRO_BITMAP *boxesM = NULL;
    ALLEGRO_BITMAP *fond = NULL;
    ALLEGRO_BITMAP *perso1 = NULL;
    ALLEGRO_BITMAP *perso2 = NULL;
    ALLEGRO_BITMAP *pseudoM = NULL;
    ALLEGRO_BITMAP *confirM = NULL;
    ALLEGRO_BITMAP *guide = NULL;
    ALLEGRO_BITMAP *options = NULL;
    ALLEGRO_BITMAP *sonOn = NULL;
    ALLEGRO_BITMAP *sonOff = NULL;

    ALLEGRO_FONT *font = al_load_ttf_font("..\\PNGS\\fonts\\britanic.ttf", 30, 0);
    ALLEGRO_FONT *mfont = al_load_ttf_font("..\\PNGS\\fonts\\britanic.ttf", 15, 0);


    //icone
    ALLEGRO_BITMAP *icone = NULL;
    icone = al_load_bitmap("..\\PNGS\\temp\\icone.png");
    assert(icone != NULL);


    al_set_window_position(ressources->display, 0, 0);
    al_set_window_title(ressources->display, "Escooked");
    al_set_display_icon(ressources->display, icone);
    al_clear_to_color(al_map_rgb(0, 0, 0));


    al_set_window_position(ressources->display, 0, 0);
    al_set_new_display_flags(ALLEGRO_FULLSCREEN | ALLEGRO_RESIZABLE);

    //Images
    mrbeast = al_load_bitmap("..\\PNGS\\temp\\maxresdefault.jpg");
    assert(mrbeast != NULL);
    transparent = al_load_bitmap("..\\PNGS\\temp\\default.png");
    assert(transparent != NULL);
    R = al_load_bitmap("..\\PNGS\\temp\\hardR.png");
    assert(R != NULL);

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
    guide = al_load_bitmap("..\\PNGS\\ImagesMenu\\MenuGuide.png");
    assert(guide != NULL);
    options = al_load_bitmap("..\\PNGS\\ImagesMenu\\Options.png");
    assert(options != NULL);
    sonOn = al_load_bitmap("..\\PNGS\\ImagesMenu\\SonActivé.png");
    assert(sonOn != NULL);
    sonOff = al_load_bitmap("..\\PNGS\\ImagesMenu\\SonDésactivé.png");
    assert(sonOff != NULL);

    assert(font);
    assert(mfont);


    //init
    const char *charac = "A\0B\0C\0D\0E\0F\0G\0H\0I\0J\0K\0L\0M\0N\0O\0P\0Q\0R\0S\0T\0U\0V\0W\0X\0Y\0Z\0";
    int window_width = al_get_display_width(ressources->display);
    int window_height = al_get_display_height(ressources->display);
    int retour = 0, mute = 0, a, nb1 = 0, nb2 = 0;
    float x1 = 67, y1 = 147, x2 = 731, y2 = 147;
    char pseudo1[21], pseudo2[21]; pseudo1[0] = '\0'; pseudo2[0] = '\0';


    enum {
        MENUPRINCIPAL, NEW, GUIDEMENU, OPT, QUIT, JEU, OFF, PSEUDO1, PSEUDO2
    };
    int state = MENUPRINCIPAL;

    declarationMenu();
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
        if (state == MENUPRINCIPAL && retour == 1) {
            transitionmenu(Fleche, fond, perso1, boxesM);
            if (mute == 0) {
                jouerMusiqueMenu(&son);
            }
            retour = 0;
        }
        if (mute == 1) {
            arreterMusiqueJeu(&son);
            arreterMusiqueMenu(&son);
        }
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE: {
                fini = true;
                break;
            }

            case ALLEGRO_EVENT_KEY_DOWN: {
                if (state == PSEUDO1) {
                    char *current;
                    if (event.keyboard.keycode <= 26 && event.keyboard.keycode >= 1) {
                        if (nb1 < 19) {
                            a = event.keyboard.keycode;
                            current = &charac[(a - 1) * 2];
                            pseudo1[nb1] = *current;
                            nb1++;
                            pseudo1[nb1]= '\0';
                        }
                        else{
                            pseudo1[nb1] = '\0';
                        }

                    } else {
                        a = 0;
                    }
                    float largeur = al_get_text_width(font, current);
                    float hauteur = al_get_font_ascent(font);
                    if (a && nb1 < 19) {
                        al_draw_text(font, BLANC, x1, y1, 0, current);
                        x1 = x1 + largeur + SPACE;
                    } else {
                        switch (event.keyboard.keycode) {
                            case ALLEGRO_KEY_BACKSPACE: {
                                int x1temp;
                                if(x1>67 + largeur){
                                    x1temp = x1 - largeur;
                                }
                                else{
                                    x1temp = 67;
                                }
                                if(nb1 > 0){
                                    pseudo1[nb1 - 1] = '\0';
                                    nb1--;

                                }
                                al_draw_bitmap(fond, 0, 0, 0);
                                al_draw_bitmap(pseudoM, 0, 0, 0);
                                x1 = 67;
                                al_draw_text(font, BLANC, x1, y1, 0, pseudo1);
                                x1 = x1temp;
                                break;
                            }
                            case ALLEGRO_KEY_ESCAPE: {
                                state = MENUPRINCIPAL;
                                strcpy(pseudo1, "");
                                x1 = 67; y1 = 147; x2 = 731; y2 = 147; nb1 = 0;
                                transitionmenu(Fleche, fond, perso1, boxesM);
                                arreterMusiqueJeu(&son);
                                jouerMusiqueMenu(&son);
                                break;
                            }
                            case ALLEGRO_KEY_ENTER: {
                                printf("%s", pseudo1);
                                if (pseudo1[0] != '\0') {
                                    x1 = 67; y1 = 147; x2 = 731; y2 = 147;
                                    state = PSEUDO2;
                                }
                                break;
                            }
                        }
                    }
                }
                if (state == PSEUDO2) {
                    char *current;
                    if (event.keyboard.keycode <= 26 && event.keyboard.keycode >= 1) {
                        if (nb2 < 19) {
                            a = event.keyboard.keycode;
                            current = &charac[(a - 1) * 2];
                            pseudo2[nb2] = *current;
                            nb2++;
                            pseudo2[nb2]= '\0';
                        }

                    } else {
                        a = 0;
                    }
                    float largeur = al_get_text_width(font, current);
                    float hauteur = al_get_font_ascent(font);
                    if (a && nb2 < 19) {
                        al_draw_text(font, BLANC, x2, y2, 0, current);
                        x2 = x2 + largeur + SPACE;
                    } else {
                        switch (event.keyboard.keycode) {
                            case ALLEGRO_KEY_BACKSPACE: {
                                int x2temp;
                                if(x2>67 + largeur){
                                    x2temp = x2 - largeur;
                                }
                                else{
                                    x2temp = 67;
                                }
                                if(nb2 > 0){
                                    pseudo2[nb2 - 1] = '\0';
                                    nb2--;

                                }
                                al_draw_bitmap(fond, 0, 0, 0);
                                al_draw_bitmap(pseudoM, 0, 0, 0);
                                x2 = 731; x1 = 67;
                                al_draw_text(font, BLANC, x1, y1, 0, pseudo1);
                                al_draw_text(font, BLANC, x2, y2, 0, pseudo2);
                                x2 = x2temp;
                                break;
                            }
                            case ALLEGRO_KEY_ESCAPE: {
                                state = PSEUDO1;
                                strcpy(pseudo2, "");
                                al_draw_bitmap(fond, 0, 0, 0);
                                al_draw_bitmap(pseudoM, 0, 0, 0);
                                al_draw_text(font, BLANC, 67, y1, 0, pseudo1);
                                x2 = 731; y2 = 147; nb2 = 0;
                                break;
                            }
                            case ALLEGRO_KEY_ENTER: {
                                if (pseudo2[0] != '\0') {
                                    x1 = 67; y1 = 147; x2 = 731; y2 = 147;
                                    state = JEU;
                                }
                                break;
                            }
                        }
                    }
                }
                if (state == QUIT || state == OPT || state == GUIDEMENU || state == NEW || state == MENUPRINCIPAL) {
                    state = menuf(&event, fond, Fleche, perso1, perso2, boxesM, pseudoM, confirM, guide, sonOn, sonOff,
                                  options, state, &mute, &son);
                }
                if (state == JEU) {
                    reinitialiserRessourcesJeu(ressources);
                    initialiserJoueurs(&joueur1, &joueur2);
                    state = jeu(&joueur1, &joueur2, ressources, &son, pseudo1, pseudo2, mfont);
                    arreterMusiqueJeu(&son);
                    retour = 1;
                }
                if (state == OFF) {
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
    destroy(icone);
    destroy(transparent);
    destroy(Fleche);
    destroy(perso1);
    destroy(perso2);
    destroy(mrbeast);
    destroy(boxesM);
    destroy(fond);
    destroy(pseudoM);
    destroy(confirM);
    destroy(guide);
    destroy(options);
    destroy(sonOn);
    destroy(sonOff);
    al_destroy_font(font);
    al_destroy_font(mfont);
    strcpy(pseudo1, "");
    strcpy(pseudo2, "");
    return 0;
}


