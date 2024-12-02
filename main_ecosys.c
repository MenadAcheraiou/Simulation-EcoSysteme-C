#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include "ecosys.h"



#define NB_PROIES 20
#define NB_PREDATEURS 10
#define T_WAIT 40000

/*

//TME 3 EXO 4.1

void test(){
    // Initialisation de l'écosystème
    Animal *liste_proie = NULL;
    int monde[SIZE_X][SIZE_Y] = {0};  // Carte de l'écosystème

    // Création d'un animal unique à une position spécifique
    int position_x = SIZE_X - 1;  // Par exemple, à la dernière ligne
    int position_y = SIZE_Y - 1;  // Par exemple, à la dernière colonne
    float energie = 10.0f;

    // Ajouter l'animal à la liste des proies
    ajouter_animal(position_x, position_y, energie, &liste_proie);

    // Forcer la direction de l'animal vers la droite et le bas
    forcer_direction_animal(liste_proie, 1, 1);

    // Afficher la position initiale de l'animal
    printf("Position initiale : x=%d, y=%d\n", liste_proie->x, liste_proie->y);

    // Nombre d'itérations pour tester le déplacement
    const int iterations = 5;

    // Boucle de déplacement
    for (int i = 0; i < iterations; i++) {
        bouger_animaux(liste_proie);  // Déplacer l'animal

        // Afficher la nouvelle position de l'animal
        printf("Position après déplacement %d : x=%d, y=%d\n", i + 1, liste_proie->x, liste_proie->y);

        // Pause pour observer le déplacement
        usleep(500000);  // Pause de 0.5 seconde
    }

    // Libérer la mémoire
    liberer_liste_animaux(liste_proie);

    return 0;
}*/

/* Reste de votre code */

int main() {
    // Initialisation de l'écosystème
    srand( time( NULL ) );
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    // Créer 20 proies
    int herbes[SIZE_X][SIZE_Y];
    for (int i = 0; i < SIZE_X; i++) {
        for (int j=0;j<SIZE_Y;j++){
            herbes[i][j]=0;
        }
    }

    for (int i = 0; i < NB_PROIES; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10.0f, &liste_proie);
    }

    // Créer 20 predateurs
    for (int i = 0; i < NB_PREDATEURS; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 100.0f, &liste_predateur);
    }

    // Variables de contrôle de la boucle
    int iterations = 0;
    const int max_iterations = 200;

    FILE *f = fopen("Evol_Pop.txt", "w");
        if (f == NULL){
            printf("Erreur lors de l'ouverture.");
            exit(1);
        }

    fprintf(f, "gen proies predateurs\n");

    //Test TME 2 EXO 6.3
    printf("Le nombre de proies %d, le nombre de prédateurs %d \n",compte_animal_it(liste_proie),compte_animal_it(liste_predateur));






    // Boucle principale de simulation
    while (liste_proie != NULL && iterations < max_iterations) {

        // Mettre à jour les proies
        rafraichir_proies(&liste_proie, herbes);

        // Mettre à jour les predateurs
        rafraichir_predateurs(&liste_predateur, &liste_proie);

        rafraichir_monde(herbes);

        // Afficher l'état actuel de l'écosystème
        afficher_ecosys(liste_proie, liste_predateur);


  // Ecrire du nombre de proies/predateurs par génération, afin de l'utiliser avec gnuplot.

    fprintf(f, "%d %d %d\n", iterations, compte_animal_it(liste_proie), compte_animal_it(liste_predateur));
        // Pause pour observer l'état de l'écosystème
        usleep(T_WAIT);  // Pause de 0.5 seconde (500000 microsecondes)

        // Incrémenter le nombre d'itérations
        iterations++;
    }


    // Si on sort de la boucle, cela signifie que soit toutes les proies sont mortes, soit on a atteint la limite d'itérations.
    if (liste_proie == NULL) {
        printf("Toutes les proies sont mortes.\n");

    }else if (liste_predateur==NULL){
        printf("Tous les predateurs sont morts");
    }
     else if (iterations >= max_iterations) {
        printf("Le nombre maximal d'itérations a été atteint.\n");
    }

  fclose(f);
  //Libérer la mémoire allouée;
  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);

  printf("La simulation est terminée !\n");

    return 0;
}

