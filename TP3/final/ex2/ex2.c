/*#################################################################
# Ex 2.) TP3.)                                                    #
# Auteur: Arthur Freeman.                                         #
# Date: 25/03/2020                                                #
#################################################################*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TPersonne {
  char nom[10];
  char prenom[10];
  int age;
};

struct TPassager {
  struct TPersonne personne;
  int numClient;
  int numSiege;
};

// Structure récursive d'arbre binaire.
struct TNoeud {
  struct TPassager contenu;
  struct TNoeud *droite;
  struct TNoeud *gauche;
};

// Fonction qui crée et renvoie un TPersonne.
struct TPersonne creePersonne(char nom[10], char prenom[10], int age) {
  struct TPersonne newPersonne;
  newPersonne.age = age;
  strcpy(newPersonne.nom, nom);
  strcpy(newPersonne.prenom, prenom);
  return newPersonne;
};

// Fonction qui renvoie et crée un TPassager, prenant un TPersonne en paramètre.
struct TPassager creePassager(struct TPersonne personne, int numClient,
                              int numSiege) {
  struct TPassager newPassanger;
  newPassanger.personne = personne;
  newPassanger.numClient = numClient;
  newPassanger.numSiege = numSiege;
  return newPassanger;
};

void insert(struct TPassager newElement, struct TNoeud **courant) {
  if (!(*courant)) {
    //printf("Assignement\n");
    *courant = malloc(sizeof(struct TNoeud));
    (*courant)->contenu = newElement;
    (*courant)->droite = NULL;
    (*courant)->gauche = NULL;
  } else {
    if (newElement.numSiege < (*courant)->contenu.numSiege) {
          //printf("Insert gauche\n");
      insert(newElement, &(*courant)->gauche);
    } else {
            //printf("Insert droit\n");
      insert(newElement, &(*courant)->droite);
    }
  }
}

struct TPassager recherche(struct TNoeud **courant, int numSiege) {
  printf("%d == %d \n", (*courant)->contenu.numSiege, numSiege);
  if( ((*courant)->contenu.numSiege == numSiege) ) {
    printf("name is: %s \n", (*courant)->contenu.personne.nom);
    struct TPassager res;
    res = (*courant)->contenu;
    printf("name is: %s \n", res.personne.nom);
    return res;
  } else {
    if(numSiege < (*courant)->contenu.numSiege) {
      return recherche( &(*courant)->gauche, numSiege);
    } else {
      return recherche( &(*courant)->droite, numSiege);
    }
  }
}

int main() {
  // Code récupéré sur:
  // https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
  // Modifications faites par moi.
  char prenom[10], nom[10];
  int age, numSiege, numClient;
  FILE *fp;
  fp = fopen("passagers.txt", "r");

  struct TNoeud *racine = NULL;

  struct TPassager current;
  while (fscanf(fp, "%d %s %s %d %d", &numClient, prenom, nom, &age,
                &numSiege) != EOF) {
    current = creePassager(creePersonne(nom, prenom, age), numClient,
                           numSiege); // Code à moi.
    insert(current, &racine);
  }
  // printf("\n valeur de debut: %i \n", debut->contenu.numSiege);
  fclose(fp); // Fin du code de tutorialspoint.

  int numRecherche = 36;
  struct TPassager passagerRecherche = recherche(&racine, numRecherche);;

  printf("His name is: %s", passagerRecherche.personne.nom);

  return 0;
}
