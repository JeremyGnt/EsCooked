#include "jeu.h"
#include "general.h"
#include "commandes.h"


void chargerEtLireFichierTexte(const char *nomFichier, fichierTexteMap *map) {
    FILE *fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Impossible d'ouvrir le fichier %s.\n", nomFichier);
        return;
    }

    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            if (!fscanf(fichier, "%d", &map->map[i][j])) {
                printf("Erreur de lecture du fichier.\n");
                fclose(fichier);
                return;
            }
        }
    }
    fscanf(fichier, "%d %d", &map->decalMapX, &map->decalMapY);
    fclose(fichier);
}

void afficher_map(fichierTexteMap map, GameResources *resources) {
    al_draw_bitmap(resources->fond, 0, 0, 0);
    for (int j = 0; j < NB_LIGNES; j++) {
        for (int i = 0; i < NB_COLONNES; i++) {
            switch (map.map[i][j]) {
                case 2:
                    al_draw_bitmap(map.mapImages[i][j] = resources->plandetravail, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 1:
                    al_draw_bitmap(map.mapImages[i][j] = resources->sol1,
                                   (i * TAILLE_CARRE) + map.decalMapX, (j * TAILLE_CARRE) + map.decalMapY,
                                   0);
                    break;
                case 3:
                    al_draw_bitmap(map.mapImages[i][j] = resources->sol2,
                                   (i * TAILLE_CARRE) + map.decalMapX, (j * TAILLE_CARRE) + map.decalMapY,
                                   0);
                    break;
                case 30:
                    al_draw_bitmap(map.mapImages[i][j] = resources->frigomenthe,
                                   (i * TAILLE_CARRE) + map.decalMapX, (j * TAILLE_CARRE) + map.decalMapY,
                                   0);
                    break;
                case 31:
                    al_draw_bitmap(map.mapImages[i][j] = resources->frigocitron,
                                   (i * TAILLE_CARRE) + map.decalMapX, (j * TAILLE_CARRE) + map.decalMapY,
                                   0);
                    break;
                case 32:
                    al_draw_bitmap(map.mapImages[i][j] = resources->frigolimonade,
                                   (i * TAILLE_CARRE) + map.decalMapX, (j * TAILLE_CARRE) + map.decalMapY,
                                   0);
                    break;
                case 33:
                    al_draw_bitmap(map.mapImages[i][j] = resources->frigocanneasucre,
                                   (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 5:
                    al_draw_bitmap(map.mapImages[i][j] = resources->cuisson, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 6:
                    al_draw_bitmap(map.mapImages[i][j] = resources->poubelle, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 7:
                    al_draw_bitmap(map.mapImages[i][j] = resources->sortie, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 8:
                    al_draw_bitmap(map.mapImages[i][j] = resources->presseAgrume, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 9:
                    al_draw_bitmap(map.mapImages[i][j] = resources->decoupe, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                case 10:
                    al_draw_bitmap(map.mapImages[i][j] = resources->frigo, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    al_draw_bitmap(map.mapImages[i][j] = resources->verre, (i * TAILLE_CARRE) + map.decalMapX,
                                   (j * TAILLE_CARRE) + map.decalMapY, 0);
                    break;
                default:
                    break;
            }
        }
    }
}

void dessinerJaugeTransformation(Ingredient *ingredient, double tempsActuel, double tempsTransformation) {
    if (ingredient->transformStartTime > 0 && tempsTransformation > 0) {
        double tempsEcoule = tempsActuel - ingredient->transformStartTime;
        double proportion = tempsEcoule / tempsTransformation;
        if (proportion > 1.0) proportion = 1.0;

        int jaugeLargeur = (int)(TAILLE_CARRE * (1 - proportion));
        int jaugeHauteur = 5;


        int posX = ingredient->x;
        int posY = ingredient->y - 10;


        ALLEGRO_COLOR couleurJauge;
        if (proportion < 0.5) {
            // De vert à orange
            float vert = 1.0;
            float rouge = proportion * 2.0;
            couleurJauge = al_map_rgb_f(rouge, vert, 0.0);
        } else {

            float vert = 1.0 - ((proportion - 0.5) * 2.0);
            couleurJauge = al_map_rgb_f(1.0, vert, 0.0);
        }


        al_draw_filled_rectangle(posX, posY, posX + jaugeLargeur, posY + jaugeHauteur, couleurJauge);
    }
}

void transformerIngredient(Joueur *joueur, RessourcesJeu *ressources, fichierTexteMap *map) {
    static const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int mapX = (joueur->x - map->decalMapX) / TAILLE_CARRE;
    int mapY = (joueur->y - map->decalMapY) / TAILLE_CARRE;
    double tempsActuel = al_get_time();

    for (int d = 0; d < 4; d++) {
        int adjX = mapX + directions[d][0];
        int adjY = mapY + directions[d][1];
        if (adjX < 0 || adjX >= NB_COLONNES || adjY < 0 || adjY >= NB_LIGNES) continue;

        int typeDeCase = map->map[adjX][adjY];
        bool directionRegard = (directions[d][0] == (joueur->vx > 0 ? 1 : (joueur->vx < 0 ? -1 : 0))) &&
                               (directions[d][1] == (joueur->vy > 0 ? 1 : (joueur->vy < 0 ? -1 : 0)));

        if (!directionRegard) continue;

        Ingredient *ingredient = NULL;
        for (int i = 0; i < ressources->ItemLaches.compte; i++) {
            Ingredient *lache = ressources->ItemLaches.items[i];
            if (lache && lache->x == adjX * TAILLE_CARRE + map->decalMapX && lache->y == adjY * TAILLE_CARRE + map->decalMapY) {
                ingredient = lache;
                break;
            }
        }

        if (ingredient) {
            double tempsTransformation = 0;
            ALLEGRO_BITMAP *nouveauBitmap = NULL;
            ALLEGRO_BITMAP *iconeTransformation = NULL;

            if (typeDeCase == 9) {
                if (ingredient->bitmap == ressources->mentheBrut) {
                    nouveauBitmap = ressources->mentheDecoupe;
                    tempsTransformation = TEMPS_TRANSFORMATION_MENTHE;
                    iconeTransformation = ressources->iconeDecoupe;
                } else if (ingredient->bitmap == ressources->citronBrut) {
                    nouveauBitmap = ressources->citronDecoupe;
                    tempsTransformation = TEMPS_TRANSFORMATION_CITRON;
                    iconeTransformation = ressources->iconeDecoupe;
                }
            } else if (typeDeCase == 5 && ingredient->bitmap == ressources->canneasucreBrut) {
                nouveauBitmap = ressources->alcoolCuit;
                tempsTransformation = TEMPS_TRANSFORMATION_CUISSON;
                iconeTransformation = ressources->iconeCuisson;
            } else if (typeDeCase == 8 && ingredient->bitmap == ressources->citronDecoupe) {
                nouveauBitmap = ressources->citronPresse;
                tempsTransformation = TEMPS_TRANSFORMATION_PRESSE;
                iconeTransformation = ressources->iconePresse;
            }

            if (nouveauBitmap) {
                if (ingredient->transformStartTime == 0) {
                    ingredient->transformStartTime = tempsActuel;
                }
                if (tempsActuel - ingredient->transformStartTime >= tempsTransformation) {
                    ingredient->bitmap = nouveauBitmap;
                    ingredient->transformStartTime = 0; // Reset time after transformation
                } else if (iconeTransformation) {
                    al_draw_bitmap(iconeTransformation, ingredient->x, ingredient->y, 0);
                    dessinerJaugeTransformation(ingredient, tempsActuel, tempsTransformation);
                }
            }
            return;
        }
    }
}

void mettreAJourTransformation(RessourcesJeu *ressources) {
    double tempsActuel = al_get_time();
    for (int i = 0; i < ressources->ItemLaches.compte; i++) {
        Ingredient *ingredient = ressources->ItemLaches.items[i];
        if (ingredient && ingredient->transformStartTime > 0) {
            double tempsTransformation = 0;
            ALLEGRO_BITMAP *nouveauBitmap = NULL;
            ALLEGRO_BITMAP *iconeTransformation = NULL;

            if (ingredient->bitmap == ressources->mentheBrut) {
                tempsTransformation = TEMPS_TRANSFORMATION_MENTHE;
                nouveauBitmap = ressources->mentheDecoupe;
                iconeTransformation = ressources->iconeDecoupe;
            } else if (ingredient->bitmap == ressources->citronBrut) {
                tempsTransformation = TEMPS_TRANSFORMATION_CITRON;
                nouveauBitmap = ressources->citronDecoupe;
                iconeTransformation = ressources->iconeDecoupe;
            } else if (ingredient->bitmap == ressources->canneasucreBrut) {
                tempsTransformation = TEMPS_TRANSFORMATION_CUISSON;
                nouveauBitmap = ressources->alcoolCuit;
                iconeTransformation = ressources->iconeCuisson;
            } else if (ingredient->bitmap == ressources->citronDecoupe) {
                tempsTransformation = TEMPS_TRANSFORMATION_PRESSE;
                nouveauBitmap = ressources->citronPresse;
                iconeTransformation = ressources->iconePresse;
            }

            if (nouveauBitmap) {
                if (tempsActuel - ingredient->transformStartTime >= tempsTransformation) {
                    ingredient->bitmap = nouveauBitmap;
                    ingredient->transformStartTime = 0;
                } else if (iconeTransformation) {
                    al_draw_bitmap(iconeTransformation, ingredient->x, ingredient->y, 0);
                    dessinerJaugeTransformation(ingredient, tempsActuel, tempsTransformation);
                }
            }
        }
    }
}

Ingredient *creer_ingredient(ALLEGRO_BITMAP *bitmap, int x, int y) {
    Ingredient *ingredient = malloc(sizeof(Ingredient));
    if (ingredient) {
        ingredient->id = ingredientSuivant++;
        ingredient->x = x;
        ingredient->y = y;
        ingredient->bitmap = bitmap;
        ingredient->Tenir = false;
        ingredient->transformStartTime = 0;
    }
    return ingredient;
}

void ajouterItemLache(ItemLache *itemsLache, Ingredient *ingredient) {
    if (itemsLache->compte < 10) {
        itemsLache->items[itemsLache->compte++] = ingredient;
    } else {
        fprintf(stderr, "Taux d'items max atteint\n");
    }
}

void enleveItemLache(ItemLache *itemsLache, Ingredient *ingredient) {
    for (int i = 0; i < itemsLache->compte; i++) {
        if (itemsLache->items[i] == ingredient) {
            for (int j = i; j < itemsLache->compte - 1; j++) {
                itemsLache->items[j] = itemsLache->items[j + 1];
            }
            itemsLache->items[--itemsLache->compte] = NULL;
            break;
        }
    }
}

void agir(Joueur *joueur, RessourcesJeu *ressources, fichierTexteMap *map) {
    static const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int mapX = (joueur->x - map->decalMapX) / TAILLE_CARRE;
    int mapY = (joueur->y - map->decalMapY) / TAILLE_CARRE;

    for (int d = 0; d < 4; d++) {
        int adjX = mapX + directions[d][0];
        int adjY = mapY + directions[d][1];
        if (adjX < 0 || adjX >= NB_COLONNES || adjY < 0 || adjY >= NB_LIGNES) continue;

        int typeDeCase = map->map[adjX][adjY];
        bool directionRegard = (directions[d][0] == (joueur->vx > 0 ? 1 : (joueur->vx < 0 ? -1 : 0))) &&
                               (directions[d][1] == (joueur->vy > 0 ? 1 : (joueur->vy < 0 ? -1 : 0)));

        if (!directionRegard) continue;

        if ((typeDeCase == 10 || (typeDeCase >= 30 && typeDeCase <= 33)) && joueur->ingredient == NULL) {
            joueur->ingredient = creer_ingredient(
                    (typeDeCase == 10) ? ressources->verre :
                    (typeDeCase == 30) ? ressources->mentheBrut :
                    (typeDeCase == 31) ? ressources->citronBrut :
                    (typeDeCase == 32) ? ressources->limonade :
                    (typeDeCase == 33) ? ressources->canneasucreBrut : NULL,
                    joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                    joueur->y - al_get_bitmap_height(joueur->bitmap) / 2
            );
            if (joueur->ingredient != NULL) {
                joueur->ingredient->Tenir = true;
            }
            return;
        }

        if (typeDeCase == 6 && joueur->ingredient != NULL) {
            free(joueur->ingredient);
            joueur->ingredient = NULL;
            return;
        }

        if (typeDeCase == 9 || typeDeCase == 5 || typeDeCase == 8 || typeDeCase == 2) {
            if (joueur->ingredient && joueur->ingredient->Tenir) {
                joueur->ingredient->Tenir = false;
                joueur->ingredient->x = adjX * TAILLE_CARRE + map->decalMapX;
                joueur->ingredient->y = adjY * TAILLE_CARRE + map->decalMapY;
                map->mapImages[adjX][adjY] = joueur->ingredient->bitmap;
                ajouterItemLache(&ressources->ItemLaches, joueur->ingredient);
                joueur->ingredient = NULL;
                return;
            } else {
                Ingredient *ingredientPlusProche = NULL;
                int distanceMinimale = INT_MAX;
                for (int i = 0; i < ressources->ItemLaches.compte; i++) {
                    Ingredient *lache = ressources->ItemLaches.items[i];
                    if (lache && lache->x == adjX * TAILLE_CARRE + map->decalMapX && lache->y == adjY * TAILLE_CARRE + map->decalMapY) {
                        int distance = abs(lache->x - (adjX * TAILLE_CARRE + map->decalMapX)) +
                                       abs(lache->y - (adjY * TAILLE_CARRE + map->decalMapY));
                        if (distance < distanceMinimale) {
                            distanceMinimale = distance;
                            ingredientPlusProche = lache;
                        }
                    }
                }
                if (ingredientPlusProche) {
                    joueur->ingredient = ingredientPlusProche;
                    joueur->ingredient->Tenir = true;
                    map->mapImages[adjX][adjY] = NULL;
                    enleveItemLache(&ressources->ItemLaches, ingredientPlusProche);
                    return;
                }
            }
        }
    }
}
void handle_keyboard_events(ALLEGRO_EVENT event, Joueur *joueur1, Joueur *joueur2) {
    float speed = 1.0;

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Z:
                joueur1->vy = -speed;
                break;
            case ALLEGRO_KEY_S:
                joueur1->vy = speed;
                break;
            case ALLEGRO_KEY_Q:
                joueur1->vx = -speed;
                break;
            case ALLEGRO_KEY_D:
                joueur1->vx = speed;
                break;
            case ALLEGRO_KEY_UP:
                joueur2->vy = -speed;
                break;
            case ALLEGRO_KEY_DOWN:
                joueur2->vy = speed;
                break;
            case ALLEGRO_KEY_LEFT:
                joueur2->vx = -speed;
                break;
            case ALLEGRO_KEY_RIGHT:
                joueur2->vx = speed;
                break;
        }
    } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Z:
                if (joueur1->vy < 0) joueur1->vy = 0;
                break;
            case ALLEGRO_KEY_S:
                if (joueur1->vy > 0) joueur1->vy = 0;
                break;
            case ALLEGRO_KEY_Q:
                if (joueur1->vx < 0) joueur1->vx = 0;
                break;
            case ALLEGRO_KEY_D:
                if (joueur1->vx > 0) joueur1->vx = 0;
                break;
            case ALLEGRO_KEY_UP:
                if (joueur2->vy < 0) joueur2->vy = 0;
                break;
            case ALLEGRO_KEY_DOWN:
                if (joueur2->vy > 0) joueur2->vy = 0;
                break;
            case ALLEGRO_KEY_LEFT:
                if (joueur2->vx < 0) joueur2->vx = 0;
                break;
            case ALLEGRO_KEY_RIGHT:
                if (joueur2->vx > 0) joueur2->vx = 0;
                break;
        }
    }
}

void update_players_position(Joueur *joueur1, Joueur *joueur2, fichierTexteMap *map) {
    Joueur* joueurs[2] = {joueur1, joueur2};

    for (int idx = 0; idx < 2; idx++) {
        Joueur *joueur = joueurs[idx];

        float nextX = joueur->x + joueur->vx;
        float nextY = joueur->y + joueur->vy;


        float angle = atan2(joueur->vy, joueur->vx);
        if (joueur->vx != 0 || joueur->vy != 0) {
            
            joueur->angle = angle + M_PI / 2;
        }

        // Vérifier la collision avec l'autre joueur en utilisant les bords de la bitmap
        Joueur *other = joueurs[1 - idx];
        float buffer = al_get_bitmap_width(joueur->bitmap);  // Utilisez la largeur de la bitmap comme buffer de collision

        // Calcul des rectangles englobants pour les collisions
        if (fabs(nextX - other->x) < buffer && fabs(nextY - other->y) < buffer) {
            continue; // Annuler le déplacement si collision
        }

        // Vérification des collisions avec les limites de la carte
        int mapX = (int)((nextX - map->decalMapX) / TAILLE_CARRE);
        int mapY = (int)((nextY - map->decalMapY) / TAILLE_CARRE);

        if (mapX >= 0 && mapX < NB_COLONNES && mapY >= 0 && mapY < NB_LIGNES) {
            int tileType = map->map[mapX][mapY];
            if (tileType == 1 || tileType == 3) {  // Sol valide pour le déplacement
                joueur->x = nextX;
                joueur->y = nextY;
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        Joueur *joueur = joueurs[i];
        int bitmap_width = al_get_bitmap_width(joueur->bitmap);
        int bitmap_height = al_get_bitmap_height(joueur->bitmap);
        // Ajuster la position du pivot pour correspondre à l'orientation "haut"
        al_draw_rotated_bitmap(joueur->bitmap, bitmap_width / 2, bitmap_height / 2, joueur->x, joueur->y, joueur->angle, 0);
    }
}

RessourcesJeu *initRessourcesJeu() {
    RessourcesJeu *ressources = malloc(sizeof(RessourcesJeu));

    ressources->timer = al_create_timer(1.0 / 120.0);
    al_start_timer(ressources->timer);

    ressources->event_queue = al_create_event_queue();
    ressources->display = al_create_display(WIDTH, HEIGHT);

    al_register_event_source(ressources->event_queue, al_get_keyboard_event_source());
    al_register_event_source(ressources->event_queue, al_get_timer_event_source(ressources->timer));
    al_register_event_source(ressources->event_queue, al_get_display_event_source(ressources->display));

    ressources->sol1 = al_load_bitmap("../images/sol 1.png");
    ressources->sol2 = al_load_bitmap("../images/sol 2.png");
    ressources->plandetravail = al_load_bitmap("../images/plan de travail.png");
    ressources->frigomenthe = al_load_bitmap("../images/frigo menthe.png");
    ressources->frigocitron = al_load_bitmap("../images/frigo citron.png");
    ressources->frigolimonade = al_load_bitmap("../images/frigo limonade.png");
    ressources->frigocanneasucre = al_load_bitmap("../images/frigo canne  a sucre.png");
    ressources->cuisson = al_load_bitmap("../images/plaque de cuisson.png");
    ressources->sortie = al_load_bitmap("../images/sortie.png");
    ressources->decoupe = al_load_bitmap("../images/station de decoupe.png");
    ressources->frigo = al_load_bitmap("../images/frigo.png");
    ressources->verre = al_load_bitmap("../images/verre.png");
    ressources->poubelle = al_load_bitmap("../images/poubelle.png");
    ressources->presseAgrume = al_load_bitmap("../images/presse agrume.png");
    ressources->fond = al_load_bitmap("../images/fond.jpg");
    ressources->limonade = al_load_bitmap("../images/limonade.png");
    ressources->canneasucreBrut = al_load_bitmap("../images/canneasucreBRUT.png");
    ressources->citronBrut = al_load_bitmap("../images/citronBRUT.png");
    ressources->mentheBrut = al_load_bitmap("../images/mentheBRUT.png");
    ressources->macaronTemps = al_load_bitmap("../images/macaron temps.png");
    ressources->citronDecoupe = al_load_bitmap("../images/citronDECOUPE.png");
    ressources->mentheDecoupe = al_load_bitmap("../images/mentheDECOUPE.png");
    ressources->alcoolCuit = al_load_bitmap("../images/alcoolCUIT.png");
    ressources->citronPresse = al_load_bitmap("../images/citronPRESSE.png");
    ressources->iconeCuisson = al_load_bitmap("../images/icone cuisson.png");
    ressources->iconeDecoupe = al_load_bitmap("../images/icone decoupe.png");
    ressources->iconePresse = al_load_bitmap("../images/icone presse.png");

    ressources->startTime = al_get_time();

    al_init_font_addon();
    al_init_ttf_addon();
    ressources->font = al_load_ttf_font("../font/Jersey25-Regular.ttf", 36, 0);

    for (int i = 0; i < 10; i++) {
        ressources->ItemLaches.items[i] = NULL;
    }
    ressources->ItemLaches.compte = 0;

    return ressources;
}

void destroyGameResources(GameResources *resources) {
    if (resources) {
        al_destroy_bitmap(resources->sol1);
        al_destroy_bitmap(resources->sol2);
        al_destroy_bitmap(resources->plandetravail);
        al_destroy_bitmap(resources->frigomenthe);
        al_destroy_bitmap(resources->frigocitron);
        al_destroy_bitmap(resources->frigolimonade);
        al_destroy_bitmap(resources->frigocanneasucre);
        al_destroy_bitmap(resources->cuisson);
        al_destroy_bitmap(resources->sortie);
        al_destroy_bitmap(resources->decoupe);
        al_destroy_bitmap(resources->frigo);
        al_destroy_bitmap(resources->verre);
        al_destroy_bitmap(resources->poubelle);
        al_destroy_bitmap(resources->presseAgrume);

        // Destroy other resources if any
        if (resources->font) {
            al_destroy_font(resources->font);
        }
        if (resources->display) {
            al_destroy_display(resources->display);
        }
        if (resources->timer) {
            al_destroy_timer(resources->timer);
        }
        if (resources->event_queue) {
            al_destroy_event_queue(resources->event_queue);
        }

        free(resources);
    }
}

// Fonction pour libérer un joueur
void destroyJoueur(Joueur *joueur) {
    if (joueur) {
        if (joueur->bitmap) {
            al_destroy_bitmap(joueur->bitmap);  // Libération du bitmap
        }
        free(joueur);  // Libération de la structure Joueur
    }
}

void afficherTemps(RessourcesJeu *ressources) {
    double tempsActuel = al_get_time();
    int tempsRestant = DUREE_PARTIE - (int)(tempsActuel - ressources->startTime);
    if (tempsRestant < 0) tempsRestant = 0;

    int posX = WIDTH - al_get_bitmap_width(ressources->macaronTemps) - 10;
    int posY = HEIGHT - al_get_bitmap_height(ressources->macaronTemps);
    al_draw_bitmap(ressources->macaronTemps, posX, posY, 0);

    char timeText[100];
    sprintf(timeText, "%02d:%02d", tempsRestant / 60, tempsRestant % 60);
    al_draw_text(ressources->font, NOIR, posX + al_get_bitmap_width(ressources->macaronTemps) / 2,
                 posY + al_get_bitmap_height(ressources->macaronTemps) / 2 -
                 al_get_font_line_height(ressources->font) / 2,
                 ALLEGRO_ALIGN_CENTER, timeText);
}

void jeu(Joueur *joueur1, Joueur *joueur2, GameResources *resources) {
    struct Recette mojito = {MOJITO, {LIMONADE, CITRON_PRESSE, MENTHE_DECOUPE, ALCOOL_CUIT, INGREDIENT_NULL}};
    struct Recette caipirinha = {CAIPIRINHA, {LIMONADE, CITRON_PRESSE, ALCOOL_CUIT, INGREDIENT_NULL}};
    struct Recette hintzy = {HINTZY, {LIMONADE, CITRON_PRESSE, MENTHE_DECOUPE, INGREDIENT_NULL}};
    struct Recette plaza = {PLAZA, {LIMONADE, CITRON_PRESSE, INGREDIENT_NULL}};

    fichierTexteMap map;
    chargerEtLireFichierTexte("../map1.txt", &map);

    imagesCommandes imagesCommandes;
    chargerImages(&imagesCommandes);
    struct Maillon *liste = NULL;
    struct Recette *recettes[NB_RECETTES] = {&mojito, &caipirinha, &hintzy, &plaza};

    resources->startTime = al_get_time();  // Réinitialiser le temps au début du jeu
    bool running = true;

    while (running) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(resources->event_queue, &ev);

        double currentTime = al_get_time();
        int remainingTime = DUREE_PARTIE - (int)(currentTime - resources->startTime);

        if (remainingTime <= 0) {
            running = false;  // Arrêter la boucle de jeu lorsque le temps est écoulé
            continue;
        }

        switch (ev.type) {
            case ALLEGRO_EVENT_TIMER:
                supprimerMaillonsExpire(&liste);
                if (liste == NULL ||
                    (rand() % FREQUENCE_NOUVELLE_RECETTE == 0 && nombreMaillons(&liste) < MAX_MAILLONS)) {
                    ajouterMaillonFin(&liste, recettes);
                }
                afficher_map(map, resources);
                dessinerToutMaillons(&liste, &imagesCommandes);
                update_players_position(joueur1,joueur2, &map);
                agir(joueur1, resources, &map);
                afficherTemps(resources);
                al_flip_display();
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_KEY_UP:
                handle_keyboard_events(ev, joueur1, joueur2);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                running = false;
                break;
            default:
                if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    running = false;
                }
                break;
        }
    }
    libererListeCommande(&liste);
    destroyJoueur(joueur1);
    destroyJoueur(joueur2);
}

