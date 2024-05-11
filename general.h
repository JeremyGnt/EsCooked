#ifndef ESCOOKED_GENERAL_H
#define ESCOOKED_GENERAL_H

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


#define WIDTH 1248
#define HEIGHT 702
#define NB_COLONNES 15
#define NB_INGREDIENTS 9
#define NB_LIGNES 8
#define TAILLE_CARRE 60

///COMMANDES///
#define DUREE_VIE 40
#define MAX_MAILLONS 5
#define NB_RECETTES 4
#define FREQUENCE_NOUVELLE_RECETTE 1200
#define NOMBRE_IMAGES 9

#define DUREE_PARTIE 90
#define TEMPS_TRANSFORMATION_MENTHE 5
#define TEMPS_TRANSFORMATION_CITRON 5
#define TEMPS_TRANSFORMATION_CUISSON 15
#define TEMPS_TRANSFORMATION_PRESSE 3

#define NOIR al_map_rgb(0,0,0)
#define BLANC al_map_rgb(255,255,255)

enum Ingredients {
    CITRON_BRUT,
    CITRON_DECOUPE,
    CITRON_PRESSE,
    CANNE_A_SUCRE_BRUT,
    ALCOOL_CUIT,
    MENTHE_BRUT,
    MENTHE_DECOUPE,
    LIMONADE,
    INGREDIENT_NULL
};

/// faire en sorte de ne plus pouvoir poser un aliment quand un aliment est deja en transformation

#endif //ESCOOKED_GENERAL_H
