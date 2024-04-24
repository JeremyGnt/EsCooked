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
#include "fichierTexteMap.h"

int main() {

    ALLEGRO_DISPLAY *display = NULL;
    fichierTexteMap mapCuisine = {0};
    ImagesCuisine imagescuisine;

    assert(al_init());
    assert(al_init_image_addon());
    display = al_create_display(WIDTH, HEIGHT);
    assert(display);
    al_set_window_position(display, 0, 0);
    al_clear_to_color(BLANCO);

    ALLEGRO_BITMAP* fond = NULL;
    fond = al_load_bitmap("../images/fond.jpg");
    int window_width = al_get_display_width(display);
    int window_height = al_get_display_height(display);


    al_draw_scaled_bitmap(fond, 0, 0, al_get_bitmap_width(fond), al_get_bitmap_height(fond), 0, 0, window_width, window_height, 0);
    chargerImages(&imagescuisine);
    chargerEtLireFichierTexte("../map1.txt", &mapCuisine);
    afficher_map(mapCuisine, &imagescuisine);


    al_flip_display();
    al_rest(15);

    libererImages(&imagescuisine);
    al_destroy_display(display);

    return 0;
}