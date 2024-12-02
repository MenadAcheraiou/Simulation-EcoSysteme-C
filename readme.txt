    Menad Acheraiou 21304430
    Yanis Ouamar 21315540


# Projet Écosystème de Proies et Prédateurs

## Description
Ce projet simule un écosystème avec des proies et des prédateurs dans un environnement de type torique. Les proies et les prédateurs sont représentés par des structures en lien qui se déplacent, consomment de l'énergie et se reproduisent suivant des règles spécifiques. L'écosystème est visualisé dans une grille, où les positions des animaux sont mises à jour à chaque itération. Le projet est implémenté en langage C et permet de tester plusieurs aspects, tels que le mouvement des animaux, la reproduction et la consommation d’énergie.

## Fonctionnalités
Le projet comporte deux catégories principales d'entités : les **proies** et les **prédateurs**. Les proies se déplacent, perdent de l'énergie, mangent pour survivre, et se reproduisent. Les prédateurs suivent une logique similaire mais consomment les proies pour survivre. Le monde est représenté comme une grille de taille fixe, définie par les constantes `SIZE_X` et `SIZE_Y`, avec un comportement torique (les entités qui sortent d’un bord réapparaissent de l'autre côté).

## Installation
### Prérequis
- Compilateur GCC (ou tout autre compilateur compatible avec le langage C)
- Utilitaire `make` (facultatif mais recommandé pour simplifier la compilation)

### Compilation
Pour compiler le projet, ouvrez un terminal dans le dossier du projet et exécutez la commande :
>make

#Fichiers du Projet
##ecosys.h

###Contient les définitions des structures de données et les déclarations des fonctions principales. Voici quelques éléments importants définis dans ce fichier :

    ####Structures :
        Animal : représente une entité animale, avec des coordonnées x et y, une direction dir, un niveau d'énergie, et un pointeur vers l'animal suivant dans la liste chaînée.
    ####Constantes globales :
        SIZE_X, SIZE_Y : dimensions de la grille de simulation.
        p_ch_dir : probabilité pour une entité de changer de direction.
        p_reproduce_proie, p_reproduce_predateur : probabilités de reproduction des proies et des prédateurs.
        temps_repousse_herbe : temps de repousse de l'herbe consommée par les proies.

##ecosys.c

###contient les définitions des fonctions principales pour manipuler les animaux et simuler le comportement de l'écosystème. Voici un résumé des fonctions clés :
####Partie 1 - Manipulation des Animaux

    creer_animal(int x, int y, float energie) : crée un nouvel animal avec des coordonnées et une énergie initiale.
    ajouter_en_tete_animal(Animal *liste, Animal *animal) : ajoute un animal en tête d'une liste d'animaux.
    compte_animal_rec(Animal *la) et compte_animal_it(Animal *la) : comptent le nombre d'animaux dans une liste, de manière récursive et itérative respectivement.
    enlever_animal(Animal **liste, Animal *animal) : supprime un animal spécifique de la liste.
    liberer_liste_animaux(Animal *liste) : libère la mémoire allouée pour une liste d'animaux.

####Partie 2 - Simulation de l'Écosystème

    bouger_animaux(Animal *la) : déplace chaque animal dans la liste suivant sa direction. Applique la toricité de l'espace.
    reproduce(Animal **liste_animal, float p_reproduce) : gère la reproduction des animaux, avec une probabilité de reproduction p_reproduce.
    rafraichir_proies(Animal **liste_proie, int monde[SIZE_X][SIZE_Y]) : met à jour l'état des proies, en diminuant leur énergie, en les supprimant si leur énergie est épuisée, et en appelant la fonction de reproduction.
    rafraichir_predateurs(Animal **liste_predateur, Animal **liste_proie) : met à jour l'état des prédateurs, qui consomment les proies s'ils en trouvent, perdent de l'énergie sinon, et se reproduisent.
    rafraichir_monde(int monde[SIZE_X][SIZE_Y]) : met à jour la grille représentant l'écosystème.

##main_ecosys.c

###Ce fichier contient le point d'entrée principal (main) pour le projet. Il initialise les proies et les prédateurs, et démarre une boucle de simulation. Voici les étapes principales :

    ####Création et initialisation des animaux :
        20 proies sont créées avec des coordonnées et de l'énergie aléatoires.
    ####Boucle de simulation :
        La boucle continue tant qu'il y a des proies et que le nombre d'itérations est inférieur à un maximum (par exemple, 200 itérations).
        À chaque itération :
            rafraichir_proies et rafraichir_predateurs sont appelées pour mettre à jour les états des animaux.
            rafraichir_monde est appelée pour mettre à jour l'état de la grille de simulation.
            L'écosystème est affiché via afficher_ecosys.
            Une pause est introduite avec usleep pour ralentir la simulation et permettre une observation visuelle.

##Exemples d'Utilisation

###Après avoir lancé le programme, vous verrez un affichage dans le terminal représentant la grille de l'écosystème avec :

    * pour les proies,
    O pour les prédateurs,
    @ pour les cases contenant à la fois une proie et un prédateur.

Le programme met à jour les positions et les états des animaux à chaque itération jusqu'à ce qu'il n'y ait plus de proies ou que la limite d'itérations soit atteinte.
Auteurs

##main_tests.c

###Fichier de tests unitaires pour vérifier certaines fonctions de ecosys.c. Voici les éléments principaux testés :

    Création et manipulation de listes d'animaux.
    Ajout et suppression d'animaux dans les listes.
    Affichage de l'écosystème dans le terminal pour observer les résultats.

###Tests réalisés :

    Création de plusieurs animaux avec des coordonnées et une énergie définies.
    Test des fonctions d'ajout et de suppression d'animaux.
    Affichage de la liste pour vérifier le bon fonctionnement.

##main_tests2.c

###Un autre fichier de test qui vérifie le bon fonctionnement des fonctions de lecture et d'écriture des états de l'écosystème dans un fichier. Ce fichier permet de sauvegarder l'état des animaux dans une grille et de les lire depuis un fichier.
Fonctionnalités :

    ecrire_ecosys : écrit l'état actuel des listes de proies et prédateurs dans un fichier texte.
    lire_ecosys : lit l'état des listes de proies et prédateurs depuis un fichier texte.

###Tests réalisés :

    Création de 20 proies et prédateurs.
    Sauvegarde de l'état des animaux dans un fichier (file.txt).
    Lecture de l'état des animaux depuis le fichier pour reconstituer les listes de proies et de prédateurs.
    Vérification des compteurs d'animaux et de la suppression des animaux.



#Améliorations futures

    Optimisation de la consommation d'énergie : ajouter une meilleure gestion de la consommation d'énergie pour les proies et prédateurs.
    Conditions environnementales : ajouter des facteurs environnementaux, comme des obstacles ou des sources de nourriture supplémentaires.
    Interface graphique : création d'une interface graphique pour visualiser l'écosystème.