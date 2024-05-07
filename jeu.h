#ifndef ESCOOKED_JEU_H
#define ESCOOKED_JEU_H

#include "general.h"

typedef struct {
    int map[NB_COLONNES][NB_LIGNES];
    ALLEGRO_BITMAP *mapImages[NB_COLONNES][NB_LIGNES];
    int decalMapX, decalMapY;
    int posJoueur1X, posJoueur1Y, posJoueur2X, posJoueur2Y;
} fichierTexteMap;

typedef struct {
    int x, y;                // Coordonnées du joueur
    ALLEGRO_BITMAP *bitmap;  // Bitmap pour l'affichage du joueur
    char nom[50];            // Nom du joueur
    bool toucheEnfoncer[4];  // État des touches [HAUT, BAS, GAUCHE, DROITE]
    float vitesse;           // Vitesse de déplacement du joueur
    float angle;             // Angle de déplacement pour l'affichage orienté
} Joueur;

typedef struct {
    ALLEGRO_DISPLAY *display;
    ALLEGRO_EVENT_QUEUE *event_queue;
    ALLEGRO_FONT *font;
    ALLEGRO_TIMER *timer;
    ALLEGRO_TIMER *timer_commande;
    double startTime;

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

} GameResources;
enum {BAS, HAUT, GAUCHE, DROITE, FBAS, FHAUT, FGAUCHE, FDROITE, ESPACE, NB_TOUCHES_GEREES};

void handle_keyboard_events(ALLEGRO_EVENT event, Joueur *joueur1, Joueur *joueur2);
void update_player_position(Joueur *joueur, fichierTexteMap *map);
void chargerEtLireFichierTexte(const char *nomFichier, fichierTexteMap *map);
void afficher_map(fichierTexteMap map, GameResources *resources);
void jeu(Joueur *joueur1, Joueur *joueur2, GameResources *resources);
void agir(Joueur *joueur1, Joueur *joueur2, GameResources *resources);

GameResources* initGameResources();
void destroyGameResources(GameResources *resources);
void destroyJoueur(Joueur *joueur);
void afficherTemps(GameResources *resources);




#endif //ESCOOKED_JEU_H
