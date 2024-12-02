#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#include "ecosys.h"
/*

void ecrire_ecosys(const char *nom_fichier, Animal *liste_predateur, Animal *liste_proie){
	FILE *f=fopen(nom_fichier,"w");
	fprintf(f,"<proies>\n");
	while(liste_proie){
		fprintf(f,"x=%d y=%d dir=[%d %d] e=%.6f\n",liste_proie->x,liste_proie->y,liste_proie->dir[0],liste_proie->dir[1],liste_proie->energie);
		liste_proie=liste_proie->suivant;
	}
	fprintf(f,"</proies>\n");
	fprintf(f,"<predateurs>\n");
    while (liste_predateur){
        fprintf(f,"x=%d y=%d dir=[%d %d] e=%.6f\n",liste_predateur->x,liste_predateur->y,liste_predateur->dir[0],liste_predateur->dir[1],liste_predateur->energie);
        liste_predateur=liste_predateur->suivant;
    }
    fprintf(f,"</predateurs>\n");

	fclose(f);
}


void lire_ecosys(const char *nom_fichier, Animal **liste_predateur,Animal **liste_proie){
    FILE *f=fopen(nom_fichier,"r");
    char buffer[50];
    fgets(buffer,50,f);
    int x=0;
    int y=0;
    int dir[2];
    float e=0;
    if (strcmp(buffer, "<proies>\n") == 0) {  // Inclut le saut de ligne pour correspondance exacte
        printf("Lecture des proies...\n");

        // Lire les données des proies jusqu'à rencontrer la balise "</proies>"
        while (fgets(buffer, sizeof(buffer), f) != NULL && strcmp(buffer, "</proies>\n") != 0) {
            // Cherche les éléments "x=", "y=", "dir=", "e=" dans chaque ligne
            sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f", &x, &y, dir,(dir+1), &e);
                printf("Proie : x = %d, y = %d, dir = [%d, %d], energie = %.2f\n", x, y, dir[0], dir[1], e);
                ajouter_animal(x,y,e,liste_proie);
                forcer_direction_animal(*liste_proie,dir[0],dir[1]);
        }
    }
    fgets(buffer,50,f);
    if (strcmp(buffer, "<predateurs>\n") == 0) {  // Inclut le saut de ligne pour correspondance exacte
        printf("Lecture des predateurs...\n");

        while (fgets(buffer, sizeof(buffer), f) != NULL && strcmp(buffer, "</predateurs>\n") != 0) {
            // Cherche les éléments "x=", "y=", "dir=", "e=" dans chaque ligne
            sscanf(buffer, "x=%d y=%d dir=[%d,%d] e=%f", &x, &y, &dir[0], &dir[1], &e);
                printf("Predateur : x = %d, y = %d, dir = [%d, %d], energie = %.2f\n", x, y, dir[0], dir[1], e);
                ajouter_animal(x,y,e,liste_predateur);
                forcer_direction_animal(*liste_predateur,dir[0],dir[1]);
        }
}
    fclose(f);
}


int main(void) {

	int i ;
	Animal *liste_proie = NULL;
	Animal *liste_predateur = NULL;
	float energie = 10;

	/* Part 1, exercice 6, question 3 */
/*
	srand(time(NULL));
	for(int i=0;i<20;i++){
    		ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_proie);
        	ajouter_animal(rand()%SIZE_X,rand()%SIZE_Y,energie,&liste_predateur);
    	}

	assert(compte_animal_it(liste_proie)==20);
	assert(compte_animal_it(liste_predateur)==20);
	assert(compte_animal_rec(liste_proie)==20);
	assert(compte_animal_rec(liste_predateur)==20);

	afficher_ecosys(liste_proie,liste_predateur);

	/* --------------------------------------------- */
/*
	ecrire_ecosys("file.txt",liste_predateur,liste_proie);

	Animal *liste_proie_lu=NULL;
	Animal *liste_predateur_lu=NULL;

    	lire_ecosys("file.txt",&liste_predateur_lu,&liste_proie_lu);

    	afficher_ecosys(liste_proie_lu,liste_predateur_lu);

        enlever_animal(&liste_proie,liste_proie);
        enlever_animal(&liste_predateur,liste_predateur);

    assert(compte_animal_it(liste_proie)==19);
	assert(compte_animal_it(liste_predateur)==19);

        enlever_animal(&liste_proie,liste_proie->suivant);
        enlever_animal(&liste_predateur,liste_predateur->suivant);

	assert(compte_animal_rec(liste_proie)==18);
	assert(compte_animal_rec(liste_predateur)==18);


	liberer_liste_animaux(liste_proie_lu);
	liberer_liste_animaux(liste_predateur_lu);

	liberer_liste_animaux(liste_proie);
	liberer_liste_animaux(liste_predateur);



    return 0;
}

*/

