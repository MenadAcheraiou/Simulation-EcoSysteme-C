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
    // Initialisation de l'�cosyst�me
    Animal *liste_proie = NULL;
    int monde[SIZE_X][SIZE_Y] = {0};  // Carte de l'�cosyst�me

    // Cr�ation d'un animal unique � une position sp�cifique
    int position_x = SIZE_X - 1;  // Par exemple, � la derni�re ligne
    int position_y = SIZE_Y - 1;  // Par exemple, � la derni�re colonne
    float energie = 10.0f;

    // Ajouter l'animal � la liste des proies
    ajouter_animal(position_x, position_y, energie, &liste_proie);

    // Forcer la direction de l'animal vers la droite et le bas
    forcer_direction_animal(liste_proie, 1, 1);

    // Afficher la position initiale de l'animal
    printf("Position initiale : x=%d, y=%d\n", liste_proie->x, liste_proie->y);

    // Nombre d'it�rations pour tester le d�placement
    const int iterations = 5;

    // Boucle de d�placement
    for (int i = 0; i < iterations; i++) {
        bouger_animaux(liste_proie);  // D�placer l'animal

        // Afficher la nouvelle position de l'animal
        printf("Position apr�s d�placement %d : x=%d, y=%d\n", i + 1, liste_proie->x, liste_proie->y);

        // Pause pour observer le d�placement
        usleep(500000);  // Pause de 0.5 seconde
    }

    // Lib�rer la m�moire
    liberer_liste_animaux(liste_proie);

    return 0;
}*/

/* Reste de votre code */

int main() {
    // Initialisation de l'�cosyst�me
    srand( time( NULL ) );
    Animal *liste_proie = NULL;
    Animal *liste_predateur = NULL;
    // Cr�er 20 proies
    int herbes[SIZE_X][SIZE_Y];
    for (int i = 0; i < SIZE_X; i++) {
        for (int j=0;j<SIZE_Y;j++){
            herbes[i][j]=0;
        }
    }

    for (int i = 0; i < NB_PROIES; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 10.0f, &liste_proie);
    }

    // Cr�er 20 predateurs
    for (int i = 0; i < NB_PREDATEURS; i++) {
        ajouter_animal(rand() % SIZE_X, rand() % SIZE_Y, 100.0f, &liste_predateur);
    }

    // Variables de contr�le de la boucle
    int iterations = 0;
    const int max_iterations = 200;

    FILE *f = fopen("Evol_Pop.txt", "w");
        if (f == NULL){
            printf("Erreur lors de l'ouverture.");
            exit(1);
        }

    fprintf(f, "gen proies predateurs\n");

    //Test TME 2 EXO 6.3
    printf("Le nombre de proies %d, le nombre de pr�dateurs %d \n",compte_animal_it(liste_proie),compte_animal_it(liste_predateur));






    // Boucle principale de simulation
    while (liste_proie != NULL && iterations < max_iterations) {

        // Mettre � jour les proies
        rafraichir_proies(&liste_proie, herbes);

        // Mettre � jour les predateurs
        rafraichir_predateurs(&liste_predateur, &liste_proie);

        rafraichir_monde(herbes);

        // Afficher l'�tat actuel de l'�cosyst�me
        afficher_ecosys(liste_proie, liste_predateur);


  // Ecrire du nombre de proies/predateurs par g�n�ration, afin de l'utiliser avec gnuplot.

    fprintf(f, "%d %d %d\n", iterations, compte_animal_it(liste_proie), compte_animal_it(liste_predateur));
        // Pause pour observer l'�tat de l'�cosyst�me
        usleep(T_WAIT);  // Pause de 0.5 seconde (500000 microsecondes)

        // Incr�menter le nombre d'it�rations
        iterations++;
    }


    // Si on sort de la boucle, cela signifie que soit toutes les proies sont mortes, soit on a atteint la limite d'it�rations.
    if (liste_proie == NULL) {
        printf("Toutes les proies sont mortes.\n");

    }else if (liste_predateur==NULL){
        printf("Tous les predateurs sont morts");
    }
     else if (iterations >= max_iterations) {
        printf("Le nombre maximal d'it�rations a �t� atteint.\n");
    }

  fclose(f);
  //Lib�rer la m�moire allou�e;
  liste_proie = liberer_liste_animaux(liste_proie);
  liste_predateur = liberer_liste_animaux(liste_predateur);

  printf("La simulation est termin�e !\n");

    return 0;
}

