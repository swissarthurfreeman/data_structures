#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "objects.h"


int main(void) {
  struct TFile *debut;
  
  srand(time(NULL));
  //Initalement, on crée la première "version" de notre liste d'attente.
  debut = malloc(sizeof(*debut)); //On réserve un espace mémoire pour ce pointeur.
  
  //On crée la file au ponteur début.
  createFile(debut, 4, NULL); //(On compte depuis 0, donc en mettant 4 => 5 passagers.)
  
  printf("\n Nombre de personnes dans la file initiale: %i", getFileLength(debut,0) + 1);
  printf("\n La dernière personne a %i ans.", debut->contenu.age);
  printf("\n La avant-dernière personne a %i ans.", debut->suivant->contenu.age);
  printf("\n La avant-avant-dernière personne a %i ans.", debut->suivant->suivant->contenu.age);
  printf("\n La avant-avant-avant-dernière personne a %i ans.", debut->suivant->suivant->suivant->contenu.age);
  printf("\n La avant-avant-avant-avant-dernière personne a %i ans.", debut->suivant->suivant->suivant->suivant->contenu.age);
  
  
  printf("\n Maitenant, on manipule, on rajoute 5 et on enlève 6\n");
  
  //Il faut déplacer le pointeur du début! Donc, on le renvoie. cf.rapport, schéma d'ajout de chaîne.
  debut = add(debut, 4); //Idem qu'avec createFile => 5 passagers en plus.

  printf("\n Taille de file post-rajout: %i", getFileLength(debut,0)+1);
  
  //Il y a un pépin au niveau des index.  
  removeLast(debut, 8); //Inverse, on enlève n-1 personnes. n = 8 => 7 personnes en moins.
  
  printf("\n Taille de file post-deletion: %i", getFileLength(debut,0) + 1);
  printf("\n La dernière personne a %i ans.", debut->contenu.age);
  printf("\n La avant-dernière personne a %i ans.", debut->suivant->contenu.age);
  //Y'a un pépin de contenu pour le premier dans la file, c'est toujours 0 ans et 0 en sexe.
  printf("\n La première personne a %i ans.", debut->suivant->suivant->contenu.age); 
  return 0;
}
