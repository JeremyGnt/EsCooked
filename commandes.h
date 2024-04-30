#ifndef ESCOOKED_COMMANDES_H
#define ESCOOKED_COMMANDES_H

#define WINDOW_WIDTH 1248
#define WINDOW_HEIGHT 702

#define DUREE_VIE 3
#define MAX_MAILLONS 5
#define NB_RECETTES 4
#define FREQUENCE_NOUVELLE_RECETTE 120
#define NOMBRE_IMAGES 9


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

// Initialisation avec ID
struct Recette mojito = {MOJITO, {LIMONADE, CITRON_PRESSE, MENTHE_DECOUPE, ALCOOL_CUIT, INGREDIENT_NULL}};
struct Recette caipirinha = {CAIPIRINHA, {LIMONADE, CITRON_PRESSE, ALCOOL_CUIT, INGREDIENT_NULL}};
struct Recette hintzy = {HINTZY, {LIMONADE, CITRON_PRESSE, MENTHE_DECOUPE, INGREDIENT_NULL}};
struct Recette plaza = {PLAZA, {LIMONADE, CITRON_PRESSE, INGREDIENT_NULL}};

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

void init_allegro(ALLEGRO_DISPLAY **display, ALLEGRO_TIMER **timer);

double get_current_time();

int nombreMaillons(struct Maillon **pListe);

void ajouterMaillonFin(struct Maillon **pListe, struct Recette *recettes[NB_RECETTES]);

void supprimerMaillonsExpire(struct Maillon **pListe);

void libererListe(struct Maillon **pListe);

void dessinerMaillon(struct Maillon *maillon, struct imagesCommandes *images, float x, float y);

void dessinerToutMaillons(struct Maillon **pListe, imagesCommandes *images);

#endif
