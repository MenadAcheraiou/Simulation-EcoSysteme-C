/********************************************************************/
/*		OUAMAR YANIS 21315506	&&	ACHERAIOU MENAD 21304430		*/
/********************************************************************/





#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "ecosys.h"
#include <time.h>


/* Definition des variables globales */

float p_ch_dir=0.5;
float p_reproduce_proie=0.3;
float p_reproduce_predateur=0.3;
int temps_repousse_herbe=-8;



/* ------------------------- PARTIE 1 ------------------------- */



/* Fourni : Part 1, exercice 4, question 2 */

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


/* Fourni : Part 1, exercice 4, question 3 */

Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}



/* Done : Part 1, exercice 6, question 2 */

void ajouter_animal(int x, int y, float energie, Animal **liste_animal) {
    	// Vérifictation des valeurs de la positions si elles sont dans le bon intervalle
	assert(x >= 0 && x < SIZE_X);
	assert(y >= 0 && y < SIZE_Y);

	*liste_animal = ajouter_en_tete_animal(*liste_animal, creer_animal(x,y,energie));
}



/* Done : Part 1, exercice 5, question 5 */

void enlever_animal(Animal **liste, Animal *animal) {
	Animal *pL = *liste;
	Animal *tmp = NULL;
    // Si on va supprimer l'animal en tete de liste
	if (pL == animal){
      // On fait juste avancer la tete de la liste
		*liste = (*liste)->suivant;
    free(pL);
	}else { // si l'animal est dans le reste de la liste
		while(pL){
			if(pL->suivant == animal){
				tmp = pL->suivant;
				pL->suivant = pL->suivant->suivant;
				free(tmp);
			}else{
        pL = pL->suivant;
      }
		}
	}
}



/* Done : Part 1, exercice 6, question 7 */

Animal* liberer_liste_animaux(Animal *liste) {
  Animal *tmp;
  while(liste){
    tmp = liste;
    liste = liste->suivant;
    free(tmp);
  }
  return NULL;
}



/* Fourni : part 1, exercice 4, question 4 */

unsigned int compte_animal_rec(Animal *la) {

  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}



/* Fourni : Part 1, exercice 4, question 4 */

unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  while (la) {
    ++cpt;
    la=la->suivant;
  }
  return cpt;
}



/* Fourni : Part 1 Exercice 5, question 1 */

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



/*-------------------------------Fonction Personnelle-------------------------------*/
/* Fonction utilisé juste lors de la lecture des listes des animaux dans un fichier */
/* Pour pouvoir donner la directions correspondante lue dans le fichier, non pas
l'initialiser avec des valeurs aléatoires */
void forcer_direction_animal(Animal *la,int dirx,int diry){
  la->dir[0]=dirx;
  la->dir[1]=diry;
}
/*--------------------------------------------------------------------*/

/* Done : Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la) {
  Animal *pL = la;
    // Passer par chaque animal de la liste
  while (pL != NULL) {
        // Changer de direction avec la probabilite : p_ch_dir
      if (rand()/(float)RAND_MAX< p_ch_dir) {
        pL->dir[0] = (rand() % 3) - 1;  // -1, 0, ou 1
        pL->dir[1] = (rand() % 3) - 1;
      }
        // Mise à jour des coordonnees en appliquant le monde torique
      pL->x = (pL->x + pL->dir[0] + SIZE_X) % SIZE_X;
      pL->y = (pL->y + pL->dir[1] + SIZE_Y) % SIZE_Y;
        // Passer a l'animal suivant dans la liste
      pL = pL->suivant;
  }
}

/* Done : Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce) {
  Animal *pL = *liste_animal;
    // Passer par chaque animal de la liste
  while (pL) {
      // Faire la reprocduction avec p_reproduce de chance
    if ((float)rand() / RAND_MAX < p_reproduce) {
        // Creer le nouvel animal a la meme position que le parent
        ajouter_animal(pL->x, pL->y, pL->energie / 2,liste_animal);
        // Diviser l'energie du parent par 2
        pL->energie /= 2;
    }
    pL = pL->suivant;
  }
}



/* Done : Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) {
    // etape 1 : Faire bouger les proies
  bouger_animaux(*liste_proie);
    // etape 2 : Parcourir la liste de proies
  Animal *pL = *liste_proie;
  while (pL) {
        // Reduire l'energie de chaque proie de 1
      pL->energie --;
        // Si l'energie de la proie est inferieure a 0, on la supprime
      if (pL->energie < 0) {
          enlever_animal(liste_proie, pL);
      }else{
          // Si la proie n est pas morte, on regarde si il y'a de l'herbe dans la case ou elle se trouve
        if(monde[pL->x][pL->y] > 0){
            // la proie reprend de l'énergie presente dans l herbe
          pL->energie += monde[pL->x][pL->y];
            // suppression de l herbe
          monde[pL->x][pL->y] = temps_repousse_herbe;
        }
      }
      pL=pL->suivant;
  }
    // etape 3 : Gerer la reproduction des proies
  reproduce(liste_proie, p_reproduce_proie);
}

/* Done : Part 2. Exercice 7, question 1 */
Animal *animal_en_XY(Animal *l, int x, int y) {
  Animal *pL = l;
    // on parcours la liste des animaux
  while(pL){
      // si on trouve un animal a la position x,y on retourne cet animal
    if ((pL->x == x) && (pL->y == y)){
      return pL;
    }
    pL = pL->suivant;
  }
    // on retourne un pointeur NULL si y'a pas d'animaux dans la case x,y
  return NULL;
}


/* Doone : Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) {
    // etape 1 : Faire bouger les predateurs
  bouger_animaux(*liste_predateur);
  Animal *pL = *liste_predateur; 
    // etape 2 : Parcourir la liste de predateurs
  while(pL){
      // Reduire l'energie de chaque predateur de 1
    pL->energie--;
      // Si l'energie du predateur est inferieure a 0, on le supprime
    if (pL->energie < 0){
      enlever_animal(liste_predateur, pL);
    }else {
        // Si le predateur n est pas mort, on regarde si il y'a de proie dans la case ou il se trouve
      Animal *killproie = animal_en_XY(*liste_proie, pL->x, pL->y);
      if (killproie != NULL){
          // le predateur reprend l energie du predateur
        pL->energie += killproie->energie;
          // suppression de la proie morte
        enlever_animal(liste_proie, killproie);
      }
    }

    pL = pL->suivant;
  }
    // etape 3 : Gerer la reproduction des predateurs
  reproduce(liste_predateur, p_reproduce_predateur);
}

/* Done : Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for(int i = 0; i < SIZE_X; i++)
    for(int j = 0; j < SIZE_Y; j++)
      monde[i][j]++;
}








