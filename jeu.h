#ifndef ESCOOKED_JEU_H
#define ESCOOKED_JEU_H

#include "general.h"
#include "sons.h"

typedef struct {
    int scoreJoueur1;
    int scoreJoueur2;
    int commandesRendues;
} Score;

typedef struct {
    int map[NB_COLONNES][NB_LIGNES];
    ALLEGRO_BITMAP *mapImages[NB_COLONNES][NB_LIGNES];
    int decalMapX, decalMapY;
    int posJoueur1X, posJoueur1Y, posJoueur2X, posJoueur2Y;
} fichierTexteMap;

typedef struct Ingredient Ingredient;
typedef struct VerreListe VerreListe;

struct VerreListe {
    Ingredient *ingredient;
    struct VerreListe *next;
};

 struct Ingredient {
    int id;
    int idIngredient;
    int x;
    int y;
    ALLEGRO_BITMAP *bitmap;
    bool Tenir;
    double tempsTransformation;
    int compteurDecoupe;
    VerreListe *ingredientList;
} ;

typedef struct {
    Ingredient *items[10];
    int compte;
} ItemLache;


typedef struct {
    int x, y;
    ALLEGRO_BITMAP *bitmap;
    char nom[50];
    float angle;
    float vx, vy;
    Ingredient *ingredient;
} Joueur;


typedef struct {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer;
    ALLEGRO_TIMER *timer_commande;
    double startTime;
    double tempsAccumulePause;


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
    ALLEGRO_BITMAP *fond;
    ALLEGRO_BITMAP *macaronTemps;

    ALLEGRO_BITMAP *limonade;
    ALLEGRO_BITMAP *canneasucreBrut;
    ALLEGRO_BITMAP *citronBrut;
    ALLEGRO_BITMAP *mentheBrut;

    ALLEGRO_BITMAP *citronDecoupe;
    ALLEGRO_BITMAP *mentheDecoupe;
    ALLEGRO_BITMAP *alcoolCuit;
    ALLEGRO_BITMAP *citronPresse;

    ALLEGRO_BITMAP *iconeCuisson;
    ALLEGRO_BITMAP *iconeDecoupe;
    ALLEGRO_BITMAP *iconePresse;

    ALLEGRO_BITMAP *MenuPause;

    ItemLache ItemLaches;


} RessourcesJeu;

void chargerEtLireFichierTexte(const char *nomFichier, fichierTexteMap *map);
void afficher_map(fichierTexteMap map, RessourcesJeu *ressources);
Ingredient *creer_ingredient(ALLEGRO_BITMAP *bitmap, int x, int y, int idIngredient, const char *nom);
void ajouterItemLache(ItemLache *itemsLache, Ingredient *ingredient);
void enleveItemLache(ItemLache *itemsLache, Ingredient *ingredient);
void ajouterIngredientListe(Ingredient *verre, Ingredient *ingredient);
void libererListeIngredients(VerreListe *verre);
void afficherIngredientsVerre(Ingredient *verre);
void agir(Joueur *joueur, RessourcesJeu *ressources, fichierTexteMap *map);
void gererEvenementsClavier(ALLEGRO_EVENT event, Joueur *joueur1, Joueur *joueur2, RessourcesJeu *resources, fichierTexteMap *map,bool pause,Sons *son);
void majPositionJoueur(Joueur *joueur1, Joueur *joueur2, fichierTexteMap *map);
RessourcesJeu *initRessourcesJeu();
void detruireRessourcesJeu(RessourcesJeu *ressources, Joueur *joueur1, Joueur *joueur2);
void destroyJoueur(Joueur *joueur);
void afficherTemps(RessourcesJeu *ressources);
int jeu(Joueur *joueur1, Joueur *joueur2, RessourcesJeu *ressources,Sons *son);
void transformerIngredient(Joueur *joueur, RessourcesJeu *ressources, fichierTexteMap *map,Sons *son);
void mettreAJourTransformation(RessourcesJeu *ressources,Sons *son);
void initialiser_scores(Score score);
void afficher_scores(RessourcesJeu *ressources, Score score);




#endif //ESCOOKED_JEU_H
