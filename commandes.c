#include "commandes.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


typedef struct Boisson {
    char *nom;
    int timer;
    struct Boisson *next;
} Boisson;

Boisson *creerBoisson() {
    Boisson *boisson = malloc(sizeof(Boisson));
    if (!boisson) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(0);
    }

    int choix = rand() % 3;
    switch (choix) {
        case 0:
            boisson->nom = strdup("Pepsi");
            break;
        case 1:
            boisson->nom = strdup("Coca-Cola");
            break;
        case 2:
            boisson->nom = strdup("Fanta");
            break;
    }


    boisson->timer = rand() % 6;
    boisson->next = NULL;

    return boisson;
}

void afficherBoisson(Boisson *boisson) {
    printf("Commande de %s\n", boisson->nom);
    printf("Temps restant : %d secondes   ", boisson->timer);
}

int main() {
    srand(time(NULL));

    Boisson *fileCommandes = NULL;
    int nbCommandes = 0;
    while (nbCommandes < 5) {
        Boisson *boisson = creerBoisson();
        afficherBoisson(boisson);


        boisson->next = fileCommandes;
        fileCommandes = boisson;

        sleep(1);


        Boisson *prev = NULL;
        Boisson *fin = fileCommandes;
        while (fin != NULL) {
            fin->timer--;
            if (fin->timer <= 0) {
                Boisson *temp = fin;
                if (prev != NULL) {
                    prev->next = fin->next;
                } else {
                    fileCommandes = fin->next;
                }
                fin = fin->next;
                free(temp->nom);
                free(temp);
                nbCommandes++;
            } else {
                prev = fin;
                fin = fin->next;
            }
        }

        printf("\n");
    }

    Boisson *fin = fileCommandes;
    while (fin != NULL) {
        Boisson *temp = fin;
        fin = fin->next;
        free(temp->nom);
        free(temp);
    }

    return 0;
}




