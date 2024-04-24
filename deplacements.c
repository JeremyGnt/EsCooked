#include "deplacements.h"
/*
struct perso {
    int x, y, largeur, hauteur;
};
typedef struct personnage perso;

void dessinerPerso(perso p) {
    al_load_bitmap("../images/perso 1");
    al_flip_display();
}

void positionnerPersoAuCentre(perso *p, int largeur, int hauteur) {
    p->largeur = largeur;
    p->hauteur = hauteur;
    p->x = WIDTH / 2 - p->largeur / 2;
    p->y = HEIGHT / 2 - p->hauteur / 2;
}

void repositionnerPersoDansFenetre(perso * p) {
    if(p->x < 0) { p->x = 0; }
    if(p->y < 0) { p->y = 0; }
    if(p->x + p->largeur > WIDTH) { p->x = WIDTH- p->largeur; }
    if(p->y + p->hauteur > HEIGHT) { p->y = HEIGHT - p->hauteur; }
}

int main() {
    ALLEGRO_DISPLAY *fenetre = NULL;
    ALLEGRO_EVENT_QUEUE *queue = NULL;
    ALLEGRO_TIMER *timer = NULL;
    ALLEGRO_EVENT event;
    perso personnage;
    bool FlecheHaut = false;
    bool FlecheBas = false;
    bool FlecheDroite = false;
    bool FlecheGauche = false;
    bool redessiner = false;
    assert(al_init());
    assert(al_install_keyboard());
    assert(al_init_primitives_addon());
    assert(al_install_mouse());
    srand(time(NULL));

    fenetre = al_create_display(WIDTH, HEIGHT);
    assert(fenetre);
    positionnerPersoAuCentre(&personnage,80,60);
    dessinerPerso(personnage);
    queue = al_create_event_queue();
    assert(queue);
    timer = al_create_timer(1.0 / 200.0);
    al_set_window_position(fenetre, 0, 0);

    al_register_event_source(queue, al_get_display_event_source(fenetre));
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));

    bool fini = false;
    al_start_timer(timer);
    while (!fini) {
        al_wait_for_event(queue, &event);
        switch (event.type) {
            case ALLEGRO_EVENT_DISPLAY_CLOSE :
                fini = true;
                break;
            case ALLEGRO_EVENT_KEY_DOWN :
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_DOWN :
                        FlecheBas = true;
                        break;
                    case ALLEGRO_KEY_UP:
                        FlecheHaut = true;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        FlecheGauche = true;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        FlecheDroite = true;
                        break;
                }
                break;
            case ALLEGRO_EVENT_KEY_UP:
                switch (event.keyboard.keycode) {
                    case ALLEGRO_KEY_DOWN :
                        FlecheBas = false;
                        break;
                    case ALLEGRO_KEY_UP:
                        FlecheHaut = false;
                        break;
                    case ALLEGRO_KEY_LEFT:
                        FlecheGauche = false;
                        break;
                    case ALLEGRO_KEY_RIGHT:
                        FlecheDroite = false;
                        break;
                }
                break;
            case ALLEGRO_EVENT_TIMER:
                if (FlecheBas){
                    personnage.y += 2;
                    redessiner = true;
                }
                if (FlecheHaut){
                    personnage.y -= 2;
                    redessiner = true;
                }
                if (FlecheDroite){
                    personnage.x += 2;
                    redessiner = true;
                }
                if (FlecheGauche){
                    personnage.x -= 2;
                    redessiner = true;
                }
                repositionnerPersoDansFenetre(&personnage);
                if (redessiner){
                    dessinerPerso(personnage);
                    redessiner = false;
                }
        }
    }

    al_destroy_display(fenetre);
    al_destroy_event_queue(queue);
    al_destroy_timer(timer);
    return 0;
}
 */