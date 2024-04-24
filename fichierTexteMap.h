#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#define TAILLE_CARRE 60
#define NB_LIGNES 8
#define NB_COLONNES 15
#define BLANCO al_map_rgb(255, 255, 255)
#define HEIGHT 702
#define WIDTH 1248

#ifndef ESCOOKED_FICHIERTEXTEMAP_H
#define ESCOOKED_FICHIERTEXTEMAP_H

struct fichierTexteMap {
    int map[NB_COLONNES][NB_LIGNES];
    ALLEGRO_BITMAP *mapImages[NB_COLONNES][NB_LIGNES];
    int decalMapX, decalMapY;
};

typedef struct fichierTexteMap fichierTexteMap;

struct ImagesCuisine {
    ALLEGRO_BITMAP *sol1;
    ALLEGRO_BITMAP *plandetravail;
    ALLEGRO_BITMAP *sol2;
    ALLEGRO_BITMAP *frigomenthe;
    ALLEGRO_BITMAP *frigocitron;
    ALLEGRO_BITMAP *frigolimonade;
    ALLEGRO_BITMAP *frigocanneasucre;
    ALLEGRO_BITMAP *cuisson;
    ALLEGRO_BITMAP *sortie;
    ALLEGRO_BITMAP *decoupe;
    ALLEGRO_BITMAP *verre;
    ALLEGRO_BITMAP *frigo;
    ALLEGRO_BITMAP *poubelle;
    ALLEGRO_BITMAP *presseAgrume;
};

typedef struct ImagesCuisine ImagesCuisine;

void chargerImages(ImagesCuisine *pMap);
void libererImages(ImagesCuisine *pMap);
void chargerEtLireFichierTexte(const char *nomFichier, fichierTexteMap *mapCuisine);
void afficher_map(fichierTexteMap mapCuisine, ImagesCuisine *pImages);

#endif //ESCOOKED_FICHIERTEXTEMAP_H
