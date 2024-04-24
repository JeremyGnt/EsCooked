#include "fichierTexteMap.h"


void chargerImages(ImagesCuisine *pMap) {
    pMap->sol1 = al_load_bitmap("../sol 1.png");
    pMap->sol2 = al_load_bitmap("../sol 2.png");
    pMap->plandetravail = al_load_bitmap("../plan de travail.png");
    pMap->frigomenthe = al_load_bitmap("../frigo menthe.png");
    pMap->frigocitron = al_load_bitmap("../frigo citron.png");
    pMap->frigolimonade = al_load_bitmap("../frigo limonade.png");
    pMap->frigocanneasucre = al_load_bitmap("../frigo canne  a sucre.png");
    pMap->cuisson = al_load_bitmap("../plaque de cuisson.png");
    pMap->sortie = al_load_bitmap("../sortie.png");
    pMap->decoupe = al_load_bitmap("../station de decoupe.png");
    pMap->frigo = al_load_bitmap("../frigo.png");
    pMap->verre = al_load_bitmap("../verre.png");
    pMap->poubelle = al_load_bitmap("../poubelle.png");
    pMap->presseAgrume = al_load_bitmap("../presse agrume.png");
}


void libererImages(ImagesCuisine *pMap) {
    al_destroy_bitmap(pMap->sol1);
    al_destroy_bitmap(pMap->sol2);
    al_destroy_bitmap(pMap->frigomenthe);
    al_destroy_bitmap(pMap->frigocitron);
    al_destroy_bitmap(pMap->frigolimonade);
    al_destroy_bitmap(pMap->frigocanneasucre);
    al_destroy_bitmap(pMap->cuisson);
    al_destroy_bitmap(pMap->sortie);
    al_destroy_bitmap(pMap->decoupe);
    al_destroy_bitmap(pMap->frigo);
    al_destroy_bitmap(pMap->verre);
    al_destroy_bitmap(pMap->poubelle);
    al_destroy_bitmap(pMap->presseAgrume);
}

void chargerEtLireFichierTexte(const char *nomFichier, fichierTexteMap *mapCuisine) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", nomFichier);
        return;
    }

    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            if (!fscanf(fichier, "%d", &mapCuisine->map[i][j])) {
                printf("Erreur de lecture du fichier.\n");
                fclose(fichier);
                return;
            }
        }
    }
    fscanf(fichier, "%d %d", &mapCuisine->decalMapX, &mapCuisine->decalMapY);

    fclose(fichier);
}

void afficher_map(fichierTexteMap mapCuisine, ImagesCuisine *pImages) {
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            switch (mapCuisine.map[i][j]) {
                case 2:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->plandetravail, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                   (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 1:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->sol1,
                                   (i * TAILLE_CARRE) + mapCuisine.decalMapX, (j * TAILLE_CARRE) + mapCuisine.decalMapY,
                                   0);
                    break;
                case 3:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->sol2,
                                   (i * TAILLE_CARRE) + mapCuisine.decalMapX, (j * TAILLE_CARRE) + mapCuisine.decalMapY,
                                   0);
                    break;
                case 30:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->frigomenthe,
                                   (i * TAILLE_CARRE) + mapCuisine.decalMapX, (j * TAILLE_CARRE) + mapCuisine.decalMapY,
                                   0);
                    break;
                case 31:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->frigocitron,
                                   (i * TAILLE_CARRE) + mapCuisine.decalMapX, (j * TAILLE_CARRE) + mapCuisine.decalMapY,
                                   0);
                    break;
                case 32:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->frigolimonade,
                                   (i * TAILLE_CARRE) + mapCuisine.decalMapX, (j * TAILLE_CARRE) + mapCuisine.decalMapY,
                                   0);
                    break;
                case 33:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->frigocanneasucre, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                   (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 5:
                    al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->cuisson, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                   (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 6: al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->poubelle, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                       (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 7: al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->sortie, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                       (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 8: al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->presseAgrume, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                       (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 9: al_draw_bitmap(mapCuisine.mapImages[i][j] = pImages->decoupe, (i * TAILLE_CARRE) + mapCuisine.decalMapX,
                                       (j * TAILLE_CARRE) + mapCuisine.decalMapY, 0);
                    break;
                case 10:
                    break;
                default:
                    break;
            }
        }
    }
}

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
    fond = al_load_bitmap("../fond.jpg");
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
