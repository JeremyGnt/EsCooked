#ifndef ESCOOKED_COMMANDES_H
#define ESCOOKED_COMMANDES_H

#include "general.h"
/// commandes ///
enum Ingredients {
    CITRON_PRESSE,
    ALCOOL_CUIT,
    MENTHE_DECOUPE,
    LIMONADE,
    INGREDIENT_NULL
};

enum RecetteID {
    MOJITO,
    CAIPIRINHA,
    HINTZY,
    PLAZA
};

struct Recette {
    enum RecetteID id;
    int ingredients[5];
};

struct Maillon {
    struct Recette *recette;
    double tempsCreation;
    struct Maillon *next;
};

struct imagesCommandes {
    ALLEGRO_BITMAP *tableauBitmap[NOMBRE_IMAGES];

};
typedef struct imagesCommandes imagesCommandes;
void chargerImages(struct imagesCommandes *imagesCommandes);
int nombreMaillons(struct Maillon **pListe);
void ajouterMaillonFin(struct Maillon **pListe, struct Recette *recettes[NB_RECETTES]);
void supprimerMaillonsExpire(struct Maillon **pListe);
void libererListeCommande(struct Maillon **pListe);
void dessinerMaillon(struct Maillon *maillon, struct imagesCommandes *images, float x, float y);
void dessinerToutMaillons(struct Maillon **pListe, imagesCommandes *images);


#endif
