#include "commandes.h"
double get_current_time() {
    return al_get_time();
}

void chargerImages(struct imagesCommandes *imagesCommandes) {
    imagesCommandes->tableauBitmap[0] = al_load_bitmap("../images/caipirinha.png");
    imagesCommandes->tableauBitmap[1] = al_load_bitmap("../images/mojito.png");
    imagesCommandes->tableauBitmap[2] = al_load_bitmap("../images/hintzy.png");
    imagesCommandes->tableauBitmap[3] = al_load_bitmap("../images/plaza.png");
    imagesCommandes->tableauBitmap[4] = al_load_bitmap("../images/MOJITO_COMMANDE.png");
    imagesCommandes->tableauBitmap[5] = al_load_bitmap("../images/PLAZA_COMMANDE.png");
    imagesCommandes->tableauBitmap[6] = al_load_bitmap("../images/HINTZY_COMMANDE.png");
    imagesCommandes->tableauBitmap[7] = al_load_bitmap("../images/CAIPIRINHA_COMMANDE.png");
    imagesCommandes->tableauBitmap[8] = al_load_bitmap("../images/pierre.png");
}

int nombreMaillons(struct Maillon **pListe) {
    int nombre = 0;
    struct Maillon *parcours = *pListe;
    while (parcours != NULL) {
        nombre++;
        parcours = parcours->next;
    }
    return nombre;
}

void ajouterMaillonFin(struct Maillon **pListe, struct Recette *recettes[NB_RECETTES]) {
    if (nombreMaillons(pListe) >= MAX_MAILLONS) {
        return;  // rien faire si le nombre maximum de maillons est atteint
    }

    int choix = rand() % NB_RECETTES;
    struct Maillon *nouveau = (struct Maillon *) calloc(1, sizeof(struct Maillon));
    nouveau->recette = recettes[choix];
    nouveau->tempsCreation = get_current_time();
    nouveau->tempsAccumulePause = 0;  // Initialisation
    nouveau->next = NULL;

    if (*pListe == NULL) {
        *pListe = nouveau;
    } else {
        struct Maillon *parcours = *pListe;
        while (parcours->next != NULL) {
            parcours = parcours->next;
        }
        parcours->next = nouveau;
    }
}

void supprimerMaillonsExpire(struct Maillon **pListe) {
    struct Maillon *parcours = *pListe;
    struct Maillon *precedent = NULL;

    while (parcours != NULL) {
        double tempsActuel = get_current_time();
        int tempsPasse = (int) (tempsActuel - parcours->tempsCreation - parcours->tempsAccumulePause);

        if (tempsPasse >= DUREE_VIE) {
            if (precedent == NULL) {
                *pListe = parcours->next;
            } else {
                precedent->next = parcours->next;
            }
            free(parcours);
            parcours = (precedent == NULL ? *pListe : precedent->next);
        } else {
            precedent = parcours;
            parcours = parcours->next;
        }
    }
}

void libererListeCommande(struct Maillon **pListe) {
    struct Maillon *courant = *pListe;
    while (courant != NULL) {
        struct Maillon *temp = courant;
        courant = courant->next;
        free(temp);
    }
    *pListe = NULL;
}

void dessinerMaillon(struct Maillon *maillon, struct imagesCommandes *images, float x, float y) {
    float maillon_width = 150;  // Taille pour le maillon
    float maillon_height = 40;

    // Dessin des images de commande
    ALLEGRO_BITMAP *ingredient_image = images->tableauBitmap[maillon->recette->id + 4];
    float ingredient_width = maillon_width * 0.8; // reduire la largeur à 80% de celle du maillon
    float ingredient_height = al_get_bitmap_height(ingredient_image) * (ingredient_width / al_get_bitmap_width(ingredient_image));
    al_draw_scaled_bitmap(ingredient_image,
                          0, 0, al_get_bitmap_width(ingredient_image), al_get_bitmap_height(ingredient_image),
                          x + (maillon_width - ingredient_width) / 2,
                          (y + maillon_height) - 9, // centrage horizontal sous le maillon
                          ingredient_width, ingredient_height,
                          0);

    // Dessin de l'image de fond "pierre"
    ALLEGRO_BITMAP *pierre_image = images->tableauBitmap[8];
    al_draw_scaled_bitmap(pierre_image,
                          0, 0, al_get_bitmap_width(pierre_image), al_get_bitmap_height(pierre_image),
                          x, y,
                          maillon_width, maillon_height,
                          0);

    // Dessin de l'image de la recette au centre
    ALLEGRO_BITMAP *recette_image = images->tableauBitmap[maillon->recette->id];
    float img_ratio = al_get_bitmap_width(recette_image) / (float) al_get_bitmap_height(recette_image);
    float img_height = maillon_height * 0.6; // Hauteur de l'image à 60% de celle du maillon
    float img_width = img_height * img_ratio; // Largeur calculée pour maintenir l'aspect ratio
    al_draw_scaled_bitmap(recette_image,
                          0, 0, al_get_bitmap_width(recette_image), al_get_bitmap_height(recette_image),
                          x + (maillon_width - img_width) / 2, y + (maillon_height - img_height) / 2, // Centrage
                          img_width, img_height,
                          0);

    // Dessin de la barre de progression au-dessus du maillon
    double temps_actuel = get_current_time();
    double temps_restant = DUREE_VIE - (temps_actuel - maillon->tempsCreation - maillon->tempsAccumulePause);
    double proportion_restante = temps_restant / DUREE_VIE;
    float bar_start = x + 6; // Debut de la barre, 3 pixels à l'intérieur du maillon
    float bar_end = x + maillon_width - 6; // Fin de la barre, 3 pixels avant la fin du maillon
    float bar_width = (bar_end - bar_start) * proportion_restante;
    ALLEGRO_COLOR bar_color = al_map_rgb_f(1.0 - proportion_restante, proportion_restante, 0);
    al_draw_filled_rectangle(bar_start, y - 6, bar_start + bar_width, y, bar_color);
}

void dessinerToutMaillons(struct Maillon **pListe, imagesCommandes *images) {
    const float initial_x_offset = 30; // Décalage initial
    float x = initial_x_offset;
    float y = 10;                      // Position initiale en y

    struct Maillon *parcours = *pListe;
    while (parcours != NULL) {
        dessinerMaillon(parcours, images, x, y);
        x += 150 + 10; // Espacement entre les maillons
        parcours = parcours->next;
    }
}
