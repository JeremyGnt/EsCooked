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

void agir(Joueur *joueur, GameResources *resources, fichierTexteMap *map) {
    joueur->ingredientPorte = false;
    if (joueur->toucheEnfoncer[ESPACE]) {
        int mapX = (joueur->x - map->decalMapX) / TAILLE_CARRE;
        int mapY = (joueur->y - map->decalMapY) / TAILLE_CARRE;
        // Verre
        if (map->map[mapX + 1][mapY] == 10 || map->map[mapX - 1][mapY] == 10 || map->map[mapX][mapY + 1] == 10 || map->map[mapX][mapY - 1] == 10) {
            Ingredients ingredient;
            ingredient.x = joueur->x + al_get_bitmap_width(joueur->bitmap);
            ingredient.y = joueur->y;
            int bitmap_width = al_get_bitmap_width(joueur->bitmap);
            int bitmap_height = al_get_bitmap_height(joueur->bitmap);
            al_draw_bitmap(resources->sol1, ingredient.x - bitmap_width, ingredient.y - bitmap_height / 2, 0);
            joueur->toucheEnfoncer[ESPACE] = false;
            joueur->ingredientPorte = true;
        }
        // Menthe
        if (map->map[mapX + 1][mapY] == 30 || map->map[mapX - 1][mapY] == 30 || map->map[mapX][mapY + 1] == 30 || map->map[mapX][mapY - 1] == 30) {
            Ingredients ingredient;
            ingredient.x = joueur->x + al_get_bitmap_width(joueur->bitmap);
            ingredient.y = joueur->y;
            int bitmap_width = al_get_bitmap_width(joueur->bitmap);
            int bitmap_height = al_get_bitmap_height(joueur->bitmap);
            al_draw_bitmap(resources->sol1, ingredient.x - bitmap_width, ingredient.y - bitmap_height / 2, 0);
            joueur->toucheEnfoncer[ESPACE] = false;
            joueur->ingredientPorte = true;
        }
        // Citron
        if (map->map[mapX + 1][mapY] == 31 || map->map[mapX - 1][mapY] == 31 || map->map[mapX][mapY + 1] == 31 || map->map[mapX][mapY - 1] == 31) {
            Ingredients ingredient;
            ingredient.x = joueur->x + al_get_bitmap_width(joueur->bitmap);
            ingredient.y = joueur->y;
            int bitmap_width = al_get_bitmap_width(joueur->bitmap);
            int bitmap_height = al_get_bitmap_height(joueur->bitmap);
            al_draw_bitmap(resources->sol1, ingredient.x - bitmap_width, ingredient.y - bitmap_height / 2, 0);
            joueur->toucheEnfoncer[ESPACE] = false;
            joueur->ingredientPorte = true;
        }
        // Limonade
        if (map->map[mapX + 1][mapY] == 32 || map->map[mapX - 1][mapY] == 32 || map->map[mapX][mapY + 1] == 32 || map->map[mapX][mapY - 1] == 32) {
            Ingredients ingredient;
            ingredient.x = joueur->x + al_get_bitmap_width(joueur->bitmap);
            ingredient.y = joueur->y;
            int bitmap_width = al_get_bitmap_width(joueur->bitmap);
            int bitmap_height = al_get_bitmap_height(joueur->bitmap);
            al_draw_bitmap(resources->sol1, ingredient.x - bitmap_width, ingredient.y - bitmap_height / 2, 0);
            joueur->toucheEnfoncer[ESPACE] = false;
            joueur->ingredientPorte = true;
        }
        // Canne à sucre
        if (map->map[mapX + 1][mapY] == 33 || map->map[mapX - 1][mapY] == 33 || map->map[mapX][mapY + 1] == 33 || map->map[mapX][mapY - 1] == 33) {
            Ingredients ingredient;
            ingredient.x = joueur->x + al_get_bitmap_width(joueur->bitmap);
            ingredient.y = joueur->y;
            int bitmap_width = al_get_bitmap_width(joueur->bitmap);
            int bitmap_height = al_get_bitmap_height(joueur->bitmap);
            al_draw_bitmap(resources->sol1, ingredient.x - bitmap_width, ingredient.y - bitmap_height / 2, 0);
            joueur->toucheEnfoncer[ESPACE] = false;
            joueur->ingredientPorte = true;
        }
        // il faut réussir à afficher de manière permanente la nouvelle image
    }
    // tant que joueur->ingredientPorte = true, l'image de l'ingrédient doit suivre la position du joueur tout en étant devant (utilisation de l'angle de vue du joueur)
    // quand joueur->ingredientPorte = false, l'image de l'ingrédient ne doit plus suivre la posistion du joueur mais doit continuer à être dessiner
}

void handle_keyboard_events(ALLEGRO_EVENT event, Joueur *joueur1, Joueur *joueur2) {
    float speed = 1.0;  // Vitesse de déplacement
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_Z:
                joueur1->vy -= speed;
                break;
            case ALLEGRO_KEY_S:
                joueur1->vy += speed;
                break;
            case ALLEGRO_KEY_Q:
                joueur1->vx -= speed;
                break;
            case ALLEGRO_KEY_D:
                joueur1->vx += speed;
                break;
            case ALLEGRO_KEY_UP:
                joueur2->vy -= speed;
                break;
            case ALLEGRO_KEY_DOWN:
                joueur2->vy += speed;
                break;
            case ALLEGRO_KEY_LEFT:
                joueur2->vx -= speed;
                break;
            case ALLEGRO_KEY_RIGHT:
                joueur2->vx += speed;
                break;


                break;
        }
    } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        switch (event.keyboard.keycode) {
            // Reset vx, vy to 0 when keys are released
            case ALLEGRO_KEY_Z:
            case ALLEGRO_KEY_S:
                joueur1->vy = 0;
                break;
            case ALLEGRO_KEY_Q:
            case ALLEGRO_KEY_D:
                joueur1->vx = 0;
                break;
            case ALLEGRO_KEY_UP:
            case ALLEGRO_KEY_DOWN:
                joueur2->vy = 0;
                break;
            case ALLEGRO_KEY_LEFT:
            case ALLEGRO_KEY_RIGHT:
                joueur2->vx = 0;
                break;
        }
    }
}

void update_players_position(Joueur *joueur1, Joueur *joueur2, fichierTexteMap *map) {
    Joueur* joueurs[2] = {joueur1, joueur2};

    for (int idx = 0; idx < 2; idx++) {
        Joueur *joueur = joueurs[idx];
        // Calcul de la nouvelle position prévue
        float nextX = joueur->x + joueur->vx;
        float nextY = joueur->y + joueur->vy;

        // Mise à jour de l'angle du joueur en fonction du vecteur de déplacement
        float angle = atan2(joueur->vy, joueur->vx);
        if (joueur->vx != 0 || joueur->vy != 0) {
            // Rotation de 90 degrés pour correspondre à l'orientation "haut" par défaut
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

GameResources *initGameResources() {
    GameResources *resources = malloc(sizeof(GameResources));
    if (!resources) {
        fprintf(stderr, "Failed to allocate GameResources\n");
        return NULL;
    }

    // Création du timer
    resources->timer = al_create_timer(1.0 / 120.0);
    if (!resources->timer) {
        fprintf(stderr, "Failed to create timer\n");
        free(resources);
        return NULL;
    }
    al_start_timer(resources->timer);

    // Création de la file d'événements
    resources->event_queue = al_create_event_queue();
    if (!resources->event_queue) {
        fprintf(stderr, "Failed to create event queue\n");
        al_destroy_timer(resources->timer);
        free(resources);
        return NULL;
    }

    // Création de l'affichage
    resources->display = al_create_display(WIDTH, HEIGHT); // Ajuste la taille selon tes besoins
    al_set_window_position(resources->display, 0, 0);
    if (!resources->display) {
        fprintf(stderr, "Failed to create display\n");
        al_destroy_timer(resources->timer);
        al_destroy_event_queue(resources->event_queue);
        free(resources);
        return NULL;
    }

    al_register_event_source(resources->event_queue, al_get_keyboard_event_source());
    al_register_event_source(resources->event_queue, al_get_timer_event_source(resources->timer));
    al_register_event_source(resources->event_queue, al_get_display_event_source(resources->display));
    al_register_event_source(resources->event_queue, al_get_display_event_source(resources->display));
// Charge les bitmaps (ajuste selon tes besoins)
    resources->sol1 = al_load_bitmap("../images/sol 1.png");
    if (!resources->sol1) {
        fprintf(stderr, "Failed to load sol 1 bitmap\n");
    }
    resources->sol2 = al_load_bitmap("../images/sol 2.png");
    if (!resources->sol2) {
        fprintf(stderr, "Failed to load sol 2 bitmap\n");
    }
    resources->plandetravail = al_load_bitmap("../images/plan de travail.png");
    if (!resources->plandetravail) {
        fprintf(stderr, "Failed to load plan de travail bitmap\n");
    }
    resources->frigomenthe = al_load_bitmap("../images/frigo menthe.png");
    if (!resources->frigomenthe) {
        fprintf(stderr, "Failed to load frigo menthe bitmap\n");
    }
    resources->frigocitron = al_load_bitmap("../images/frigo citron.png");
    if (!resources->frigocitron) {
        fprintf(stderr, "Failed to load frigo citron bitmap\n");
    }
    resources->frigolimonade = al_load_bitmap("../images/frigo limonade.png");
    if (!resources->frigolimonade) {
        fprintf(stderr, "Failed to load frigo limonade bitmap\n");
    }
    resources->frigocanneasucre = al_load_bitmap("../images/frigo canne  a sucre.png");
    if (!resources->frigocanneasucre) {
        fprintf(stderr, "Failed to load frigo canne a sucre bitmap\n");
    }
    resources->cuisson = al_load_bitmap("../images/plaque de cuisson.png");
    if (!resources->cuisson) {
        fprintf(stderr, "Failed to load plaque de cuisson bitmap\n");
    }
    resources->sortie = al_load_bitmap("../images/sortie.png");
    if (!resources->sortie) {
        fprintf(stderr, "Failed to load sortie bitmap\n");
    }
    resources->decoupe = al_load_bitmap("../images/station de decoupe.png");
    if (!resources->decoupe) {
        fprintf(stderr, "Failed to load station de decoupe bitmap\n");
    }
    resources->frigo = al_load_bitmap("../images/frigo.png");
    if (!resources->frigo) {
        fprintf(stderr, "Failed to load frigo bitmap\n");
    }
    resources->verre = al_load_bitmap("../images/verre.png");
    if (!resources->verre) {
        fprintf(stderr, "Failed to load verre bitmap\n");
    }
    resources->poubelle = al_load_bitmap("../images/poubelle.png");
    if (!resources->poubelle) {
        fprintf(stderr, "Failed to load poubelle bitmap\n");
    }
    resources->presseAgrume = al_load_bitmap("../images/presse agrume.png");
    if (!resources->presseAgrume) {
        fprintf(stderr, "Failed to load presse agrume bitmap\n");
    }
    resources->fond = al_load_bitmap("../images/fond.jpg");
    if (!resources->fond) {
        fprintf(stderr, "Failed to load fond bitmap\n");
    }
/// TEMPS PARTIE
    resources->macaronTemps = al_load_bitmap("../images/macaron temps.png");
    if (!resources->macaronTemps) {
        fprintf(stderr, "Failed to load macaronTemps bitmap\n");
    }
    resources->startTime = al_get_time();



    // Initialisation et chargement de la police
    al_init_font_addon(); // Initialisation du module de police
    al_init_ttf_addon();  // Support des polices TTF
    resources->font = al_load_ttf_font("../PNGS/fonts/Jersey25-Regular.ttf", 36, 0);
    if (!resources->font) {
        fprintf(stderr, "Failed to load font\n");
        // Ajoutez un traitement approprié, par exemple un nettoyage et sortie
    }
    return resources;
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

void afficherTemps(GameResources *resources) {
    // Calculer le temps restant
    double currentTime = al_get_time();
    int remainingTime = DUREE_PARTIE - (int)(currentTime - resources->startTime);
    if (remainingTime < 0) remainingTime = 0;  // S'assurer que le temps ne va pas en-dessous de zéro

    // Position de l'image macaronScore en bas à droite
    int posX = (WIDTH - al_get_bitmap_width(resources->macaronTemps))-10;
    int posY = HEIGHT - al_get_bitmap_height(resources->macaronTemps);
    al_draw_bitmap(resources->macaronTemps, posX, posY, 0);

    // Formatage et affichage du texte du temps
    char timeText[100];
    sprintf(timeText, "%02d:%02d", remainingTime / 60, remainingTime % 60);
    al_draw_text(resources->font, NOIR, posX + al_get_bitmap_width(resources->macaronTemps) / 2,
                 posY + al_get_bitmap_height(resources->macaronTemps) / 2 - al_get_font_line_height(resources->font) / 2,
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

