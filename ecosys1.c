#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ecosys.h"
#include <time.h>


/* Définition des variables globales */

float p_ch_dir=0.5;
float p_reproduce_proie=0.3;
float p_reproduce_predateur=0.3;
int temps_repousse_herbe=-15;

/* ------------------------- PARTIE 1 ------------------------- */



/* Fourni: Part 1, exercice 4, question 2 */

Animal *creer_animal(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;

}

Animal *creer_animal_avec_dir(int x, int y, float energie) {
  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}



/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
	assert(x >= 0 && x < SIZE_X);
	assert(y >= 0 && y < SIZE_Y);

	*liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
}



/* Done: Part 1, exercice 5, question 5 */

void enlever_animal(Animal **liste, Animal *animal) {
	Animal *listeP = *liste;
	Animal *temp = NULL;

	if (listeP == animal){
		*liste = (*liste)->suivant;
    free(listeP);
	}

	else {
		while(listeP){
			if(listeP->suivant == animal){
				temp = listeP->suivant;
				listeP->suivant = listeP->suivant->suivant;
				free(temp);
			}

			else listeP = listeP->suivant;
		}
	}
}



/* Done: Part 1, exercice 6, question 7 */

Animal* liberer_liste_animaux(Animal *liste) {

   Animal *tmp;
   while(liste){
   	tmp = liste;
   	liste = liste->suivant;
   	free(tmp);
   }
  return NULL;
}



/* Fourni: part 1, exercice 4, question 4 */

unsigned int compte_animal_rec(Animal *la) {

  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}



/* Fourni: part 1, exercice 4, question 4 */

unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Fourni: Part 1 Exercice 5, question 1 */

void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur) {

  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa=NULL;

  /* on initialise le tableau */
  for (i = 0; i < SIZE_X; ++i) {
    for (j = 0; j < SIZE_Y; ++j) {
      ecosys[i][j]=' ';
    }
  }

  /* on ajoute les proies */
  pa = liste_proie;

  while (pa) {

    ecosys[pa->x][pa->y] = '*';

    pa=pa->suivant;
  }

  /* on ajoute les predateurs */
  pa = liste_predateur;

  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  for (i = 0; i < SIZE_X; ++i) {
    printf("|");
    for (j = 0; j < SIZE_Y; ++j) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j<SIZE_Y; ++j) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);

  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}



/* ------------------------- PARTIE 2 ------------------------- */

/*Fonction Personnelle*/
void forcer_direction_animal(Animal *la,int dirx,int diry){
    la->dir[0]=dirx;
    la->dir[1]=diry;
}



void bouger_animaux(Animal *la) {


    Animal *courant = la;


    while (courant != NULL) {
        // Changer de direction avec probabilité p_ch_dir
        if (rand() < p_ch_dir) {
            courant->dir[0] = (rand() % 3) - 1;  // -1, 0, ou 1
            courant->dir[1] = (rand() % 3) - 1;
        }

        // Mise à jour des coordonnées en appliquant le monde torique
        courant->x = (courant->x + courant->dir[0] + SIZE_X) % SIZE_X;
        courant->y = (courant->y + courant->dir[1] + SIZE_Y) % SIZE_Y;

        courant = courant->suivant;  // Passer à l'animal suivant dans la liste
    }
}

/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
    Animal *courant = *liste_animal;
    while (courant) {
        if ((float)rand() / RAND_MAX < p_reproduce) {  // Vérifier la probabilité de reproduction
            // Créer le nouvel animal à la même position que le parent
            ajouter_animal(courant->x, courant->y, courant->energie / 2,liste_animal);
            // Diviser l'énergie du parent par 2
            courant->energie /= 2;
        }
        courant = courant->suivant;  // Passer à l'animal suivant
    }
}



/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    // Étape 1 : Faire bouger les proies
    bouger_animaux(*liste_proie);

    // Étape 2 : Parcourir la liste de proies
    Animal *temp = liste_proie ? *liste_proie : NULL;


    while (temp) {
        // Réduire l'énergie de chaque proie de 1
        temp->energie --;
        // Si l'énergie de la proie est inférieure à 0, on la supprime
        if (temp->energie < 0) {
            enlever_animal(liste_proie, temp);
            }
        else if (monde[temp->x][temp->y] > 0){
            temp->energie += monde[temp->x][temp->y];
            monde[temp->x][temp->y] = temps_repousse_herbe;
            }
           temp=temp->suivant;
    }



    // Étape 3 : Gérer la reproduction des proies
    reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  Animal *temp = l;
  while(temp){
    if ((temp->x == x) && (temp->y == y))
      return temp;

    temp = temp->suivant;
  }

  return NULL;
}


/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
  bouger_animaux(*liste_predateur);
  Animal *temp = liste_predateur ? *liste_predateur : NULL;

  while(temp){
    temp->energie--;

    if (temp->energie < 0){
      enlever_animal(liste_predateur, temp);
    }
    else {
      Animal *proieVictime = animal_en_XY(*liste_proie, temp->x, temp->y);
      if (proieVictime != NULL){
        temp->energie += proieVictime->energie;
        enlever_animal(liste_proie, proieVictime);
      }
    }

    temp = temp->suivant;
  }

  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for(int i = 0; i < SIZE_X; i++)
    for(int j = 0; j < SIZE_Y; j++)
      monde[i][j]++;
}



/*    EXERCICE 4 , Q1  */



