#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#define MAX_LENGTH 5

struct TNoeud tableauDeNoeuds[8]; //On initialise la liste d'adjacence.

//Fonction qui crée et renvoie un pointeur sur une liste chainée de 7 TVoisins.
struct TVoisins* createListeChainee(int tableau[MAX_LENGTH]) {
  struct TVoisins *newList; //On crée un pointeur de départ, qu'on alloue.
  newList = malloc(sizeof(struct TVoisins));
  int i;i = 0; 
  struct TVoisins *courant;
  courant = newList; //On initialise i et courant qui gère l'élément sur lequel on est.
  while ( (-1 < tableau[i]) && (i < MAX_LENGTH) ) { //Du moment qu'on a pas finit de parcourir la liste.
    courant->indexNoeud = tableau[i]; //On mets la propriété indexNoeud de l'élément courant à celle du tableau à cet index.
    //On fait attention à ce que la prochaine case ne sois pas "vide" afin de ne pas allouer un pointeur qui pointera dieu sais ou, et ne pas être en dehors du tableau.
    if (tableau[i + 1] > -1 && i < MAX_LENGTH) { 
      courant->suivant = malloc(sizeof(struct TVoisins)); //On alloue son prochain pointeur.
    }
    courant = courant->suivant; //On décale le pointeur et on refait la procédure pour ce nouveau pointeur.
    i = i + 1; //On incrémente i, pour pouvoir avoir un break et parcourir tout le tableau.
  }
  return newList;
}

//Fonction qui crée un noeud avec sa liste chaînée de voisins et le renvoie.
struct TNoeud addNoeud(struct TContenu contenu, int tableau[5]) {
  struct TNoeud newNoeud; //Variable locale nouveau noeud.
  newNoeud.contenu = contenu; //On initialise son contenu.
  newNoeud.voisins = createListeChainee(tableau); //On configure sa liste de voisins. createListeChainee renvoie un pointeur.
  return newNoeud; //On retourne le noeud pour le mettre dans la liste d'adjacence du main.
  
}

//Fonction qui crée le contenu d'un noeud et le renvoie.
struct TContenu createContenu(char nom[20], char IATA[3]) {
  struct TContenu newContenu;
  strcpy(newContenu.IATA, IATA);
  strcpy(newContenu.nom, nom);
  newContenu.visite = false; //Initialement, personne n'est visité.
  return newContenu;
}

//Fonction pour rajouter un élément à une file.
void enfiler(struct TNoeud w, struct TFile *Q) {
  struct TFile *courant; //Pointeur courant.
  courant = Q; //Pour ne pas jouer avec des paramètres.
  while(1) { //tant que le suivant est alloué.
    if(courant->suivant == NULL) { //Si le suivant n'est pas alloué.
      courant->suivant = malloc(sizeof(struct TFile)); //On l'alloue.
      courant->noeud = w; //On lui assigne un contenu.
      break;
    } else if(courant->suivant != NULL) {
      //printf("HELLOOOO");
      courant = courant->suivant; //On passe au suivant.
    }
  }
}

//Fonction qui enlève le premier élément d'une file et le renvoie.
struct TNoeud enlever1er(struct TFile** Q) { //On passe l'adresse du pointeur vers la file.
  struct TNoeud noeud;
  noeud = (**Q).noeud; //Le noeud qu'on renvoie est le premier élément pointé.
  *Q = (**Q).suivant; //Le pointeur pointé par le double pointeur devient égal au suivant du premier élément.
  return noeud; //On renvoie le premier noeud.
}

int length(struct TFile *debut) {
  int i; 
  i = 0;
  struct TFile* courant; 
  courant = debut;
  while(courant->suivant != NULL) {
    courant = courant->suivant;
    i++;
  } 
  return i;
}

void BFS(struct TNoeud *depart) { //Problème, BFS ne fait qu'une fois pour le départ...
  struct TFile *Q;
  Q = malloc(sizeof(struct TFile));
  depart->contenu.visite = true;
  enfiler(*depart, Q);
  while (length(Q) > 0) {
    struct TNoeud v;
    v = enlever1er(&Q);
    printf("Noeud marqué = %s \n", v.contenu.nom);
    struct TVoisins *courant;
    courant = v.voisins;
    while (courant != NULL) {
      if(tableauDeNoeuds[courant->indexNoeud].contenu.visite == false) {
        tableauDeNoeuds[courant->indexNoeud].contenu.visite = true;
        enfiler(tableauDeNoeuds[courant->indexNoeud], Q);
        printf("Noeuds adjacents : %s \n ", tableauDeNoeuds[courant->indexNoeud].contenu.nom);
      }
      courant = courant->suivant;
    }
  }
}

void DFS(struct TNoeud *start) {  //On ne modifie pas le pointeur => pas de double pointeur.
    if (start->contenu.visite == false) {    
      start->contenu.visite = true;
      struct TVoisins *voisinCourant;
      voisinCourant = start->voisins; 
      while (1) {
        printf("%s \n", start->contenu.nom);
        printf("%i \n", voisinCourant->indexNoeud);
        DFS(&tableauDeNoeuds[voisinCourant->indexNoeud]);  
        if(voisinCourant->suivant != NULL) { //Si le pointeur d'après est NULL, on s'arrête,
          voisinCourant = voisinCourant->suivant;  //car j'aurais déjà parcouru le courant.
        } else {
          break;
        }
      }
    }
}


int main() {
    
    //C n'aime pas les tableaux de tailles variables en paramètre de fonction.
    int voisins0[5] = {1,3,4,6,-1};  //Je choisit donc une taille statique maximale de 5 et mets -1,
    int voisins1[5] = {4,-1,-1,-1,-1};  //Pour signifier le vide.
    int voisins2[5] = {4,7,-1,-1,-1};
    int voisins3[5] = {0,4,5,-1,-1};
    int voisins4[5] = {0,1,2,3,7}; 
    int voisins5[5] = {0,3,4,-1,-1}; 
    int voisins6[5] = {7,-1,-1,-1,-1}; 
    int voisins7[5] = {0,3,4,-1,-1};
    
    //On assigne les valeurs de la liste, avec les noeuds et les codes associés.
    tableauDeNoeuds[0] = addNoeud(createContenu("Londres", "LHR"), voisins0);
    tableauDeNoeuds[1] = addNoeud(createContenu("Berlin", "BER"), voisins1);
    tableauDeNoeuds[2] = addNoeud(createContenu("Milan", "MXP"), voisins2);
    tableauDeNoeuds[3] = addNoeud(createContenu("Tokyo","NRT" ), voisins3);
    tableauDeNoeuds[4] = addNoeud(createContenu("Paris", "CDG"), voisins4);
    tableauDeNoeuds[5] = addNoeud(createContenu("Montreal", "YUL"), voisins5);
    tableauDeNoeuds[6] = addNoeud(createContenu("Madrid", "MAD"), voisins6);
    tableauDeNoeuds[7] = addNoeud(createContenu("Geneve", "GVA"), voisins7);
    
    BFS(&tableauDeNoeuds[0]);
    //DFS(&tableauDeNoeuds[0]);
    return 0;
}

