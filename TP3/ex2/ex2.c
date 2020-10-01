#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#define MAX_LENGTH 5

struct TNoeud tableauDeNoeuds[8]; //On initialise la liste d'adjacence.

//Fonction qui cr�e et renvoie un pointeur sur une liste chain�e de 7 TVoisins.
struct TVoisins* createListeChainee(int tableau[MAX_LENGTH]) {
  struct TVoisins *newList; //On cr�e un pointeur de d�part, qu'on alloue.
  newList = malloc(sizeof(struct TVoisins));
  int i;i = 0; 
  struct TVoisins *courant;
  courant = newList; //On initialise i et courant qui g�re l'�l�ment sur lequel on est.
  while ( (-1 < tableau[i]) && (i < MAX_LENGTH) ) { //Du moment qu'on a pas finit de parcourir la liste.
    courant->indexNoeud = tableau[i]; //On mets la propri�t� indexNoeud de l'�l�ment courant � celle du tableau � cet index.
    //On fait attention � ce que la prochaine case ne sois pas "vide" afin de ne pas allouer un pointeur qui pointera dieu sais ou, et ne pas �tre en dehors du tableau.
    if (tableau[i + 1] > -1 && i < 5) { 
      courant->suivant = malloc(sizeof(struct TVoisins)); //On alloue son prochain pointeur.
    }
    courant = courant->suivant; //On d�cale le pointeur et on refait la proc�dure pour ce nouveau pointeur.
    i = i + 1; //On incr�mente i, pour pouvoir avoir un break et parcourir tout le tableau.
  }
  return newList;
}

//Fonction qui cr�e un noeud avec sa liste cha�n�e de voisins et le renvoie.
struct TNoeud addNoeud(struct TContenu contenu, int tableau[5]) {
  struct TNoeud newNoeud; //Variable locale nouveau noeud.
  newNoeud.contenu = contenu; //On initialise son contenu.
  newNoeud.voisins = createListeChainee(tableau); //On configure sa liste de voisins. createListeChainee renvoie un pointeur.
  return newNoeud; //On retourne le noeud pour le mettre dans la liste d'adjacence du main.
  
}

//Fonction qui cr�e le contenu d'un noeud et le renvoie.
struct TContenu createContenu(char nom[20], char IATA[3]) {
  struct TContenu newContenu;
  strcpy(newContenu.IATA, IATA);
  strcpy(newContenu.nom, nom);
  newContenu.visite = false; //Initialement, personne n'est visit�.
  return newContenu;
}

//Fonction pour rajouter un �l�ment � une file.
void enfiler(struct TNoeud w, struct TFile *Q) {
  struct TFile *courant; //Pointeur courant.
  courant = Q; //Pour ne pas jouer avec des param�tres.
  while(1) { //tant que le suivant est allou�.
    if(courant->suivant == NULL) { //Si le suivant n'est pas allou�.
      courant->suivant = malloc(sizeof(struct TFile)); //On l'alloue.
      courant->noeud = w; //On lui assigne un contenu.
      break;
    } else if(courant->suivant != NULL) {
      printf("HELLOOOO");
      courant = courant->suivant; //On passe au suivant.
    }
  }
}

//Fonction qui enl�ve le premier �l�ment d'une file et le renvoie.
struct TNoeud enlever1er(struct TFile** Q) { //On passe l'adresse du pointeur vers la file.
  struct TNoeud noeud;
  noeud = (**Q).noeud; //Le noeud qu'on renvoie est le premier �l�ment point�.
  *Q = (**Q).suivant; //Le pointeur point� par le double pointeur devient �gal au suivant du premier �l�ment.
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
    //printf("\n i of length %i \n", i);
  } 
  
  //printf("Return read");
  
  return i;
}

void BFS(struct TNoeud *depart) {
  struct TFile *Q;
  Q = malloc(sizeof(struct TFile));
  
  struct TNoeud *debut;
  debut = depart;
  
  debut->contenu.visite = true;
  
  
  
  enfiler( (*debut) , Q);
  
  printf("\n nom of current BFS noeud %s", (*debut).contenu.nom);
  
  printf("\n longueur de file %i", length(Q));
  
  while (length(Q) > 0) {
    
    printf("\n Poff");
    
    struct TNoeud v;
    
    v = enlever1er(&Q);
    
    struct TVoisins *element;
    
    element = v.voisins;
    
    do {
      struct TNoeud w;
      w = tableauDeNoeuds[element->indexNoeud]; 
      
      if(w.contenu.visite = false) {
        
        w.contenu.visite = true;
        
        printf("%s", w.contenu.nom);
        
        enfiler(w, Q);
      }
    } while(element->suivant != NULL);
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
      
        if(voisinCourant->suivant != NULL) { //Si le pointeur d'apr�s est NULL, on s'arr�te,
          voisinCourant = voisinCourant->suivant;  //car j'aurais d�j� parcouru le courant.
        } else {
          break;
        }
      }
    }
}


int main() {
    
    //C n'aime pas les tableaux de tailles variables en param�tre de fonction.
    int voisins0[5] = {1,3,4,6,-1};  //Je choisit donc une taille statique maximale de 5 et mets -1,
    int voisins1[5] = {4,-1,-1,-1,-1};  //Pour signifier le vide.
    int voisins2[5] = {4,7,-1,-1,-1};
    int voisins3[5] = {0,4,5,-1,-1};
    int voisins4[5] = {0,1,2,3,7}; 
    int voisins5[5] = {0,3,4,-1,-1}; 
    int voisins6[5] = {7,-1,-1,-1,-1}; 
    int voisins7[5] = {0,3,4,-1,-1};
    
    //On assigne les valeurs de la liste, avec les noeuds et les codes associ�s.
    tableauDeNoeuds[0] = addNoeud(createContenu("Londres", "LHR"), voisins0);
    tableauDeNoeuds[1] = addNoeud(createContenu("Berlin", "BER"), voisins1);
    tableauDeNoeuds[2] = addNoeud(createContenu("Milan", "MXP"), voisins2);
    tableauDeNoeuds[3] = addNoeud(createContenu("Tokyo","NRT" ), voisins3);
    tableauDeNoeuds[4] = addNoeud(createContenu("Paris", "CDG"), voisins4);
    tableauDeNoeuds[5] = addNoeud(createContenu("Montreal", "YUL"), voisins5);
    tableauDeNoeuds[6] = addNoeud(createContenu("Madrid", "MAD"), voisins6);
    tableauDeNoeuds[7] = addNoeud(createContenu("Geneve", "GVA"), voisins7);
    
    BFS(&tableauDeNoeuds[0]);
    //printf("\n Value %i \n", tableauDeNoeuds[4].voisins->suivant->suivant->suivant->suivant->indexNoeud);
    
    //printf("Appel de DFS \n");
    //DFS(&tableauDeNoeuds[0]);
    /*
    struct TFile* test;
    test = malloc(sizeof(struct TFile));
    
    enfiler(tableauDeNoeuds[0], test); //Enfiler marche.
    enfiler(tableauDeNoeuds[6], test);
    */
    /*  
    struct TNoeud premier;
    premier = enlever1er(&test);
  
    printf("Enlev� %s \n", premier.contenu.nom);
  
    premier = enlever1er(&test); //enlver1er marche, la file fonctionne.
    printf("Enlev� %s\n", premier.contenu.nom);
    */
    
    
  
    //printf("%s", test->suivant->noeud.contenu.nom);
  
    return 0;
}

