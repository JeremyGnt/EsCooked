#include "jeu.h"
#include "general.h"
#include "commandes.h"
#include "sons.h"

int ingredientSuivant = 1;

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

void afficher_map(fichierTexteMap map, RessourcesJeu *ressources) {
    int k = 0,j = 0, i = 0;
    if (ressources->fond) {
        al_draw_bitmap(ressources->fond, 0, 0, 0);
    }
    for (j = 0; j < NB_LIGNES; j++) {
        for (i = 0; i < NB_COLONNES; i++) {
            ALLEGRO_BITMAP *bitmap = NULL;
            switch (map.map[i][j]) {
                case 1: bitmap = ressources->sol1; break;
                case 2: bitmap = ressources->plandetravail; break;
                case 3: bitmap = ressources->sol2; break;
                case 5: bitmap = ressources->cuisson; break;
                case 6: bitmap = ressources->poubelle; break;
                case 7: bitmap = ressources->sortie; break;
                case 8: bitmap = ressources->presseAgrume; break;
                case 9: bitmap = ressources->decoupe; break;
                case 10:
                    if (ressources->frigo) {
                        al_draw_bitmap(ressources->frigo, i * TAILLE_CARRE + map.decalMapX, j * TAILLE_CARRE + map.decalMapY, 0);
                    }
                    bitmap = ressources->verre;
                    break;
                case 30: bitmap = ressources->frigomenthe; break;
                case 31: bitmap = ressources->frigocitron; break;
                case 32: bitmap = ressources->frigolimonade; break;
                case 33: bitmap = ressources->frigocanneasucre; break;
            }
            if (bitmap) {
                al_draw_bitmap(bitmap, i * TAILLE_CARRE + map.decalMapX, j * TAILLE_CARRE + map.decalMapY, 0);
                map.mapImages[i][j] = bitmap;
            }
        }
    }

    for (k = 0; k < ressources->ItemLaches.compte; k++) {
        Ingredient *item = ressources->ItemLaches.items[k];
        if (item && item->bitmap) {
            al_draw_bitmap(item->bitmap, item->x, item->y, 0);
        }
    }
}

void dessinerJaugeTransformation(Ingredient *ingredient, double tempsActuel, double tempsTransformation) {
    if (ingredient->tempsTransformation > 0 && tempsTransformation > 0) {
        double tempsEcoule = tempsActuel - ingredient->tempsTransformation;
        double proportion = tempsEcoule / tempsTransformation;
        if (proportion > 1.0) proportion = 1.0;

        int jaugeLargeur = (int)(TAILLE_CARRE * (1 - proportion));
        int jaugeHauteur = 5;


        int posX = ingredient->x;
        int posY = ingredient->y - 10;


        ALLEGRO_COLOR couleurJauge;
        if (proportion < 0.5) {

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
    int d = 0, i = 0;
    static const int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    int mapX = (joueur->x - map->decalMapX) / TAILLE_CARRE;
    int mapY = (joueur->y - map->decalMapY) / TAILLE_CARRE;
    int pressionsNecessaires = 5; // Nombre de pressions nécessaires pour la découpe

    for (d = 0; d < 4; d++) {
        int adjX = mapX + directions[d][0];
        int adjY = mapY + directions[d][1];
        if (adjX < 0 || adjX >= NB_COLONNES || adjY < 0 || adjY >= NB_LIGNES) continue; // Si en dehors, alors iteration suivante

        int typeDeCase = map->map[adjX][adjY];
        bool directionRegard = (directions[d][0] == (joueur->vx > 0 ? 1 : (joueur->vx < 0 ? -1 : 0))) &&
                               (directions[d][1] == (joueur->vy > 0 ? 1 : (joueur->vy < 0 ? -1 : 0)));

        if (!directionRegard) continue;

        Ingredient *ingredient = NULL;
        for (i = 0; i < ressources->ItemLaches.compte; i++) {
            Ingredient *lache = ressources->ItemLaches.items[i];
            if (lache && lache->x == adjX * TAILLE_CARRE + map->decalMapX && lache->y == adjY * TAILLE_CARRE + map->decalMapY) {
                ingredient = lache;
                break;
            }
        }

        if (ingredient) {
            ALLEGRO_BITMAP *nouveauBitmap = NULL;

            if (typeDeCase == 9) { // Station de découpe
                if (ingredient->bitmap == ressources->mentheBrut && ingredient->compteurDecoupe < pressionsNecessaires) {
                    ingredient->compteurDecoupe++;
                    if (ingredient->compteurDecoupe >= pressionsNecessaires) {
                        nouveauBitmap = ressources->mentheDecoupe;
                    }
                } else if (ingredient->bitmap == ressources->citronBrut && ingredient->compteurDecoupe < pressionsNecessaires) {
                    ingredient->compteurDecoupe++;
                    if (ingredient->compteurDecoupe >= pressionsNecessaires) {
                        nouveauBitmap = ressources->citronDecoupe;
                    }
                }
            } else if (typeDeCase == 5 && ingredient->bitmap == ressources->canneasucreBrut) { // Station de cuisson
                if (ingredient->tempsTransformation == 0) {
                    ingredient->tempsTransformation = al_get_time(); // Initialisation du temps de transformation
                }
                if (al_get_time() - ingredient->tempsTransformation >= TEMPS_TRANSFORMATION_CUISSON) {
                    nouveauBitmap = ressources->alcoolCuit; // Transformation finale après cuisson
                }
            } else if (typeDeCase == 8 && ingredient->bitmap == ressources->citronDecoupe) { // Station de presse-agrumes
                if (ingredient->tempsTransformation == 0) {
                    ingredient->tempsTransformation = al_get_time(); // Initialisation du temps de transformation
                }
                if (al_get_time() - ingredient->tempsTransformation >= TEMPS_TRANSFORMATION_PRESSE) {
                    nouveauBitmap = ressources->citronPresse; // Transformation finale après pressage
                }
            }

            if (nouveauBitmap) {
                ingredient->bitmap = nouveauBitmap;
                ingredient->compteurDecoupe = 0; // Réinitialisation du compteur
                ingredient->tempsTransformation = 0; // Réinitialisation du temps de transformation
                if (nouveauBitmap == ressources->mentheDecoupe) {
                    ingredient->idIngredient = MENTHE_DECOUPE;
                } else if (nouveauBitmap == ressources->citronDecoupe) {
                    ingredient->idIngredient = CITRON_DECOUPE;
                } else if (nouveauBitmap == ressources->alcoolCuit) {
                    ingredient->idIngredient = ALCOOL_CUIT;
                } else if (nouveauBitmap == ressources->citronPresse) {
                    ingredient->idIngredient = CITRON_PRESSE;
                } else {
                    ingredient->idIngredient = ingredient->idIngredient; // Aucun changement
                }
            }
            return;
        }
    }
}

void afficherIngredientsVerre(Ingredient *verre) {
    VerreListe *actuel = verre->ingredientList;
    printf("ingredients dans le verre:\n");

    while (actuel) {
        switch (actuel->ingredient->idIngredient) {
            case CITRON_BRUT:
                printf(" - Citron Brut\n");
                break;
            case CITRON_DECOUPE:
                printf(" - Citron Decoupe\n");
                break;
            case CITRON_PRESSE:
                printf(" - Citron Presse\n");
                break;
            case CANNE_A_SUCRE_BRUT:
                printf(" - Canne a Sucre Brut\n");
                break;
            case ALCOOL_CUIT:
                printf(" - Alcool Cuit\n");
                break;
            case MENTHE_BRUT:
                printf(" - Menthe Brut\n");
                break;
            case MENTHE_DECOUPE:
                printf(" - Menthe Decoupe\n");
                break;
            case LIMONADE:
                printf(" - Limonade\n");
                break;
            default:
                printf(" inconito \n");
                break;
        }
        actuel = actuel->next;
    }
}

void dessinerJaugeDecoupe(Ingredient *ingredient, int pressionsNecessaires) {
    if (ingredient->compteurDecoupe > 0) {
        float proportion = (float)ingredient->compteurDecoupe / (float)pressionsNecessaires;
        int jaugeLargeur = (int)(TAILLE_CARRE * proportion);
        int jaugeHauteur = 5;

        int posX = ingredient->x;
        int posY = ingredient->y - 10;

        ALLEGRO_COLOR couleurJauge;
        if (proportion < 0.5) {
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

void mettreAJourTransformation(RessourcesJeu *ressources) {
    int i;
    double tempsActuel = al_get_time();
    for (i = 0; i < ressources->ItemLaches.compte; i++) {
        Ingredient *ingredient = ressources->ItemLaches.items[i];
        if (ingredient && (ingredient->tempsTransformation > 0 || ingredient->compteurDecoupe > 0)) {
            double tempsTransformation = 0;
            ALLEGRO_BITMAP *nouveauBitmap = NULL;
            ALLEGRO_BITMAP *iconeTransformation = NULL;

            if (ingredient->bitmap == ressources->mentheBrut || ingredient->bitmap == ressources->citronBrut) { // Découpe
                int pressionsNecessaires = 5;
                if (ingredient->bitmap == ressources->mentheBrut) {
                    nouveauBitmap = ressources->mentheDecoupe;
                    iconeTransformation = ressources->iconeDecoupe;
                } else if (ingredient->bitmap == ressources->citronBrut) {
                    nouveauBitmap = ressources->citronDecoupe;
                    iconeTransformation = ressources->iconeDecoupe;
                }

                // Vérifier si le nombre de pressions est suffisant
                if (ingredient->compteurDecoupe >= pressionsNecessaires) {
                    ingredient->bitmap = nouveauBitmap;
                    ingredient->compteurDecoupe = 0;
                    ingredient->tempsTransformation = 0;
                    if (nouveauBitmap == ressources->mentheDecoupe) {
                        ingredient->idIngredient = MENTHE_DECOUPE;
                    } else if (nouveauBitmap == ressources->citronDecoupe) {
                        ingredient->idIngredient = CITRON_DECOUPE;
                    }
                } else if (iconeTransformation) {
                    al_draw_bitmap(iconeTransformation, ingredient->x, ingredient->y, 0);
                    dessinerJaugeDecoupe(ingredient, pressionsNecessaires);
                }

            } else if (ingredient->bitmap == ressources->canneasucreBrut) { // Cuisson de la canne à sucre
                tempsTransformation = TEMPS_TRANSFORMATION_CUISSON;
                nouveauBitmap = ressources->alcoolCuit;
                iconeTransformation = ressources->iconeCuisson;
            } else if (ingredient->bitmap == ressources->citronDecoupe) { // Pressage de citron
                tempsTransformation = TEMPS_TRANSFORMATION_PRESSE;
                nouveauBitmap = ressources->citronPresse;
                iconeTransformation = ressources->iconePresse;
            }

            if (nouveauBitmap && (ingredient->bitmap != ressources->mentheBrut && ingredient->bitmap != ressources->citronBrut)) {
                if (tempsActuel - ingredient->tempsTransformation >= tempsTransformation) {
                    ingredient->bitmap = nouveauBitmap;
                    ingredient->tempsTransformation = 0;
                    if (nouveauBitmap == ressources->alcoolCuit) {
                        ingredient->idIngredient = ALCOOL_CUIT;
                    } else if (nouveauBitmap == ressources->citronPresse) {
                        ingredient->idIngredient = CITRON_PRESSE;
                    }
                } else if (iconeTransformation) {
                    al_draw_bitmap(iconeTransformation, ingredient->x, ingredient->y, 0);
                    dessinerJaugeTransformation(ingredient, tempsActuel, tempsTransformation);
                }
            }
        }
    }
}

Ingredient *creer_ingredient(ALLEGRO_BITMAP *bitmap, int x, int y, int idIngredient, const char *nom) {
    Ingredient *ingredient = malloc(sizeof(Ingredient));
    if (ingredient) {
        ingredient->id = ingredientSuivant++;
        ingredient->idIngredient = idIngredient;
        ingredient->x = x;
        ingredient->y = y;
        ingredient->bitmap = bitmap;
        ingredient->Tenir = false;
        ingredient->tempsTransformation = 0;
        ingredient->ingredientList = NULL;
        ingredient->compteurDecoupe = 0; // Initialisation du compteur
    }
    return ingredient;
}

void ajouterItemLache(ItemLache *itemsLache, Ingredient *ingredient) {
    if (itemsLache->compte < 10) {
        itemsLache->items[itemsLache->compte++] = ingredient;
    } else {
        printf("Taux d'items max atteint\n");
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

void ajouterIngredientListe(Ingredient *verre, Ingredient *ingredient) {
    VerreListe *nouvelleIngredient = malloc(sizeof(VerreListe));
    if (nouvelleIngredient) {
        nouvelleIngredient->ingredient = ingredient;
        nouvelleIngredient->next = verre->ingredientList;
        verre->ingredientList = nouvelleIngredient;
    }
}

void libererListeIngredients(VerreListe *verre) {
    VerreListe *temp;
    while (verre) {
        temp = verre;
        verre = verre->next;
        free(temp);
    }
}

void agir(Joueur *joueur, RessourcesJeu *ressources, fichierTexteMap *map) {
    int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
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
            if (typeDeCase == 10) {
                joueur->ingredient = creer_ingredient(ressources->verre,
                                                      joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                                                      joueur->y - al_get_bitmap_height(joueur->bitmap) / 2,
                                                      INGREDIENT_NULL,
                                                      "Verre");
            } else if (typeDeCase == 30) {
                joueur->ingredient = creer_ingredient(ressources->mentheBrut,
                                                      joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                                                      joueur->y - al_get_bitmap_height(joueur->bitmap) / 2,
                                                      MENTHE_BRUT,
                                                      "Menthe Brut");
            } else if (typeDeCase == 31) {
                joueur->ingredient = creer_ingredient(ressources->citronBrut,
                                                      joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                                                      joueur->y - al_get_bitmap_height(joueur->bitmap) / 2,
                                                      CITRON_BRUT,
                                                      "Citron Brut");
            } else if (typeDeCase == 32) {
                joueur->ingredient = creer_ingredient(ressources->limonade,
                                                      joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                                                      joueur->y - al_get_bitmap_height(joueur->bitmap) / 2,
                                                      LIMONADE,
                                                      "Limonade");
            } else if (typeDeCase == 33) {
                joueur->ingredient = creer_ingredient(ressources->canneasucreBrut,
                                                      joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                                                      joueur->y - al_get_bitmap_height(joueur->bitmap) / 2,
                                                      CANNE_A_SUCRE_BRUT,
                                                      "Canne à Sucre Brut");
            } else {
                joueur->ingredient = creer_ingredient(NULL,
                                                      joueur->x + al_get_bitmap_width(joueur->bitmap) / 2,
                                                      joueur->y - al_get_bitmap_height(joueur->bitmap) / 2,
                                                      INGREDIENT_NULL,
                                                      "Inconnito");
            }

            if (joueur->ingredient != NULL) {
                joueur->ingredient->Tenir = true;
            }
            return;
        }

        if (typeDeCase == 6 && joueur->ingredient != NULL) {
            if (joueur->ingredient->ingredientList) {
                libererListeIngredients(joueur->ingredient->ingredientList);
            }
            free(joueur->ingredient);
            joueur->ingredient = NULL;
            return;
        }

        if (typeDeCase == 9 || typeDeCase == 5 || typeDeCase == 8 || typeDeCase == 2 || typeDeCase == 7) {
            if (joueur->ingredient && joueur->ingredient->Tenir) {
                if (typeDeCase == 7 && joueur->ingredient->idIngredient == INGREDIENT_NULL) {
                    afficherIngredientsVerre(joueur->ingredient);
                }
                Ingredient *verre = NULL;
                for (int i = 0; i < ressources->ItemLaches.compte; i++) {
                    Ingredient *lache = ressources->ItemLaches.items[i];
                    if (lache && lache->idIngredient == INGREDIENT_NULL &&
                        lache->x == adjX * TAILLE_CARRE + map->decalMapX &&
                        lache->y == adjY * TAILLE_CARRE + map->decalMapY) {
                        verre = lache;
                        break;
                    }
                }

                if (verre) {
                    ajouterIngredientListe(verre, joueur->ingredient);
                } else {
                    bool decoupable = (joueur->ingredient->idIngredient == MENTHE_BRUT || joueur->ingredient->idIngredient == CITRON_BRUT);
                    bool cuissonPossible = (joueur->ingredient->idIngredient == CANNE_A_SUCRE_BRUT);
                    bool pressePossible = (joueur->ingredient->idIngredient == CITRON_DECOUPE);

                    if ((typeDeCase == 9 && !decoupable) || (typeDeCase == 5 && !cuissonPossible) || (typeDeCase == 8 && !pressePossible)) {
                        // Ignorer les ingrédients non appropriés pour la station
                        continue;
                    }

                    joueur->ingredient->Tenir = false;
                    joueur->ingredient->x = adjX * TAILLE_CARRE + map->decalMapX;
                    joueur->ingredient->y = adjY * TAILLE_CARRE + map->decalMapY;
                    map->mapImages[adjX][adjY] = joueur->ingredient->bitmap;
                    ajouterItemLache(&ressources->ItemLaches, joueur->ingredient);
                }
                joueur->ingredient = NULL;
                return;
            } else {
                Ingredient *ingredientPlusProche = NULL;
                int distanceMinimale = INT_MAX;
                for (int i = 0; i < ressources->ItemLaches.compte; i++) {
                    Ingredient *lache = ressources->ItemLaches.items[i];
                    if (lache && lache->x == adjX * TAILLE_CARRE + map->decalMapX && lache->y == adjY * TAILLE_CARRE + map->decalMapY) {
                        if (lache->tempsTransformation > 0) continue;

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

void gererEvenementsClavier(ALLEGRO_EVENT event, Joueur *joueur1, Joueur *joueur2, RessourcesJeu *resources, fichierTexteMap *map, bool pause) {
    if (pause) return;  // Ignorer les événements de clavier si en pause

    float vitesse = 1.0;

    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Z:
                joueur1->vy = -vitesse;
                break;
            case ALLEGRO_KEY_S:
                joueur1->vy = vitesse;
                break;
            case ALLEGRO_KEY_Q:
                joueur1->vx = -vitesse;
                break;
            case ALLEGRO_KEY_D:
                joueur1->vx = vitesse;
                break;
            case ALLEGRO_KEY_UP:
                joueur2->vy = -vitesse;
                break;
            case ALLEGRO_KEY_DOWN:
                joueur2->vy = vitesse;
                break;
            case ALLEGRO_KEY_LEFT:
                joueur2->vx = -vitesse;
                break;
            case ALLEGRO_KEY_RIGHT:
                joueur2->vx = vitesse;
                break;
            case ALLEGRO_KEY_C:
                agir(joueur1, resources, map);
                break;
            case ALLEGRO_KEY_L:
                agir(joueur2, resources, map);
                break;
            case ALLEGRO_KEY_V: // Mise à jour ici
                transformerIngredient(joueur1, resources, map);
                break;
            case ALLEGRO_KEY_M: // Mise à jour ici
                transformerIngredient(joueur2, resources, map);
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

void majPositionJoueur(Joueur *joueur1, Joueur *joueur2, fichierTexteMap *map) {
    Joueur *joueurs[2] = {joueur1, joueur2};

    for (int indexJoueur = 0; indexJoueur < 2; indexJoueur++) {
        Joueur *joueur = joueurs[indexJoueur];
        float nextX = joueur->x + joueur->vx;
        float nextY = joueur->y + joueur->vy;

        if (joueur->vx != 0 || joueur->vy != 0) {
            joueur->angle = atan2(joueur->vy, joueur->vx) + M_PI / 2;
        }

        Joueur *autre = joueurs[1 - indexJoueur];
        float temporaire = 0;
        if (joueur->bitmap != NULL) {
            temporaire = al_get_bitmap_width(joueur->bitmap);
        }

        if (fabs(nextX - autre->x) < temporaire && fabs(nextY - autre->y) < temporaire) continue; // collision entre les 2 joueurs

        int mapX = (int)((nextX - map->decalMapX) / TAILLE_CARRE);
        int mapY = (int)((nextY - map->decalMapY) / TAILLE_CARRE);

        if (mapX >= 0 && mapX < NB_COLONNES && mapY >= 0 && mapY < NB_LIGNES) {
            int typeDeCase = map->map[mapX][mapY];
            if (typeDeCase == 1 || typeDeCase == 3) {
                joueur->x = nextX;
                joueur->y = nextY;
            }
        }

        if (joueur->ingredient != NULL && joueur->ingredient->Tenir) {
            joueur->ingredient->x = joueur->x;
            joueur->ingredient->y = joueur->y;
        }
    }

    for (int i = 0; i < 2; i++) {
        Joueur *joueur = joueurs[i];
        if (joueur->bitmap != NULL) {
            al_draw_rotated_bitmap(joueur->bitmap, al_get_bitmap_width(joueur->bitmap) / 2,
                                   al_get_bitmap_height(joueur->bitmap) / 2, joueur->x, joueur->y, joueur->angle, 0);
        }

        if (joueur->ingredient != NULL && joueur->ingredient->Tenir) {
            al_draw_bitmap(joueur->ingredient->bitmap, joueur->ingredient->x, joueur->ingredient->y, 0);
        }
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
    ressources->MenuPause = al_load_bitmap("../images/MenuPause.png");

    ressources->startTime = al_get_time();
    ressources->tempsAccumulePause = 0;


    al_init_font_addon();
    al_init_ttf_addon();
    ressources->font = al_load_ttf_font("../PNGS/fonts/Jersey25-Regular.ttf", 36, 0);

    for (int i = 0; i < 10; i++) {
        ressources->ItemLaches.items[i] = NULL;
    }
    ressources->ItemLaches.compte = 0;

    return ressources;
}

void detruireRessourcesJeu(RessourcesJeu *ressources, Joueur *joueur1, Joueur *joueur2) {
    if (ressources) {
        al_destroy_bitmap(ressources->sol1);
        al_destroy_bitmap(ressources->sol2);
        al_destroy_bitmap(ressources->plandetravail);
        al_destroy_bitmap(ressources->frigomenthe);
        al_destroy_bitmap(ressources->frigocitron);
        al_destroy_bitmap(ressources->frigolimonade);
        al_destroy_bitmap(ressources->frigocanneasucre);
        al_destroy_bitmap(ressources->cuisson);
        al_destroy_bitmap(ressources->sortie);
        al_destroy_bitmap(ressources->decoupe);
        al_destroy_bitmap(ressources->frigo);
        al_destroy_bitmap(ressources->verre);
        al_destroy_bitmap(ressources->poubelle);
        al_destroy_bitmap(ressources->presseAgrume);

        for (int i = 0; i < ressources->ItemLaches.compte; i++) {
            free(ressources->ItemLaches.items[i]);
        }

        if (ressources->font) {
            al_destroy_font(ressources->font);
        }
        if (ressources->display) {
            al_destroy_display(ressources->display);
        }
        if (ressources->timer) {
            al_destroy_timer(ressources->timer);
        }
        if (ressources->event_queue) {
            al_destroy_event_queue(ressources->event_queue);
        }
        destroyJoueur(joueur1);
        destroyJoueur(joueur2);

        free(ressources);
    }
}

void destroyJoueur(Joueur *joueur) {
    if (joueur) {
        if (joueur->bitmap) {
            al_destroy_bitmap(joueur->bitmap);
        }
        free(joueur);
    }
}

void afficherTemps(RessourcesJeu *ressources) {
    double tempsActuel = al_get_time();
    int tempsRestant = DUREE_PARTIE - (int)(tempsActuel - ressources->startTime - ressources->tempsAccumulePause);
    if (tempsRestant < 0) tempsRestant = 0;

    int posX = WIDTH - al_get_bitmap_width(ressources->macaronTemps) - 10;
    int posY = HEIGHT - al_get_bitmap_height(ressources->macaronTemps);
    al_draw_bitmap(ressources->macaronTemps, posX, posY, 0);

    char temps[100];
    sprintf(temps, "%02d:%02d", tempsRestant / 60, tempsRestant % 60);
    al_draw_text(ressources->font, NOIR, posX + al_get_bitmap_width(ressources->macaronTemps) / 2,
                 posY + al_get_bitmap_height(ressources->macaronTemps) / 2 -
                 al_get_font_line_height(ressources->font) / 2,
                 ALLEGRO_ALIGN_CENTER, temps);
}


int jeu(Joueur *joueur1, Joueur *joueur2, RessourcesJeu *ressources) {
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

    ressources->startTime = al_get_time();

    int state = 5, pause = 0, tempsRestant;
    double tempsPauseDebut = 0;

    bool enCours = true;

    while (enCours) {
        ALLEGRO_EVENT ev;
        al_wait_for_event(ressources->event_queue, &ev);

        double tempsActuel = al_get_time();

        if (!pause) {
            tempsRestant = DUREE_PARTIE - (int)(tempsActuel - ressources->startTime - ressources->tempsAccumulePause);
        }

        if (tempsRestant <= 0) {
            enCours = false;
            continue;
        }

        if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                al_draw_bitmap(ressources->MenuPause, 0, 0, 0);
                pause = 1;
                tempsPauseDebut = al_get_time();  // Enregistrer le début de la pause
                al_flip_display();
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                if (pause) {
                    enCours = false;
                    state = 0;
                }
            }
            if (ev.keyboard.keycode == ALLEGRO_KEY_SPACE) {
                if (pause) {
                    pause = 0;
                    double tempsPauseFin = al_get_time();
                    double pauseDuree = tempsPauseFin - tempsPauseDebut;
                    ressources->tempsAccumulePause += pauseDuree;

                    // Ajuster tempsAccumulePause pour chaque maillon
                    struct Maillon *parcours = liste;
                    while (parcours != NULL) {
                        parcours->tempsAccumulePause += pauseDuree;
                        parcours = parcours->next;
                    }
                }
            }
        }

            switch (ev.type) {
            case ALLEGRO_EVENT_TIMER:
                if (!pause) {
                    supprimerMaillonsExpire(&liste);
                    if (liste == NULL || (rand() % FREQUENCE_NOUVELLE_RECETTE == 0 && nombreMaillons(&liste) < MAX_MAILLONS)) {
                        ajouterMaillonFin(&liste, recettes);
                    }
                    double tempsprecedent = 0;
                    double tempsactuel = al_get_time();
                    if (tempsactuel - tempsprecedent >= 5.0) {
                        // afficherIngredientsEnCours(&liste);
                        tempsprecedent = tempsactuel;
                    }
                    afficher_map(map, ressources);
                    dessinerToutMaillons(&liste, &imagesCommandes);
                    majPositionJoueur(joueur1, joueur2, &map);
                    mettreAJourTransformation(ressources);
                    afficherTemps(ressources);
                    al_flip_display();
                }
                break;
            case ALLEGRO_EVENT_KEY_DOWN:
            case ALLEGRO_EVENT_KEY_UP:
                gererEvenementsClavier(ev, joueur1, joueur2, ressources, &map, pause);
                break;
            case ALLEGRO_EVENT_DISPLAY_CLOSE:
                enCours = false;
                break;
            default:
                if (ev.type == ALLEGRO_EVENT_KEY_DOWN && ev.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                    enCours = false;
                }
                break;
        }
    }
    libererListeCommande(&liste);
    return state;
}

