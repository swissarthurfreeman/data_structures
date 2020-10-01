/*TP1:Implémentation
Auteur: Arthur Freeman
18/02/2020*/
#include <stdio.h>
#include <string.h>

/****************************************************************/
/*                        Exercice 1.)                          */
/****************************************************************/

//Déclaration du type voiture.
struct TVoiture {
  char marque[25], modele[25]; //Information de l'énoncé.$
  long int immatriculation;
  enum status {enattente, reparee} etat; //etat est la variable qu'on référence.
};

//Déclaration du type client.
struct TClient {
  char nom[25]; //Information essentielle pour garder contact avec le client.
  int numero; //On pourrait créer une contrainte, ils sont jamais plus long qu'un certain nb de caractères.
  struct TVoiture voiture; //Référence à TVoiture définit plus haut.
};


//Fonction qui crée et renvoie une voiture.
struct TVoiture creeVoiture(char marque[25], char modele[25], long int immatriculation) {
  struct TVoiture voiture;
  voiture.etat = enattente;
  strcpy(voiture.marque, marque);
  strcpy(voiture.modele, modele);
  voiture.immatriculation = immatriculation;
  return voiture;
}

//Fonction qui crée et renvoie un client.
struct TClient creeClient(char nom[25], int numero, struct TVoiture voiture) {
  struct TClient client;
  strcpy(client.nom, nom);
  client.numero = numero;
  client.voiture = voiture;
  return client;
}

void setName(struct TClient client, char newName) {
  strcpy(client.nom, newName);
}

void setNumber(struct TClient client, int newNumber) {
  client.numero = newNumber;
}

void setVoitureState(struct TClient client, etat) {
  client.voiture.etat = etat;
}

void afficheVoituresReparees(struct TClient clients[10]) {
  int p;
  printf("\nLes voitures réparées sont:\n");
  for(p = 0; p < 10; p++) {
    struct TVoiture voiture = clients[p].voiture;
    if(voiture.etat == reparee) {
      printf("Immatriculation: %s Marque: %s Modele: %s, \n", voiture.immatriculation, voiture.marque, voiture.modele);
    }
  }
}

//Main est la fonction qui est TOUJOURS dans un programme C, elle renvoie un int 0. Par construction de C.
int main(void) {
  //Initialisation d'un tableau.
  struct TClient clients[10];

  clients[0] = creeClient("Gordon", 05456517, creeVoiture("Mercedes", "GLK", "LAMBDA1") );
  clients[1] = creeClient("Walter", 5464897, creeVoiture("Honda", "ASF", "TSOIN34") );
  clients[2] = creeClient("White", 12134518, creeVoiture("Mercedes", "ABD", "WALTER99") );
  clients[3] = creeClient("Basil", 6984561, creeVoiture("Opel", "GLK", "BVC") );
  clients[4] = creeClient("Alan", 4894132, creeVoiture("Peugeot", "VBC", "PIMPON") );
  clients[5] = creeClient("Gerard", 98532, creeVoiture("Ford", "LGBT", "CHIUAUA11") );
  clients[6] = creeClient("Paul", 10464512, creeVoiture("Volkswagen", "TSNB", "CHAD9") );
  clients[7] = creeClient("Vittek", 656102, creeVoiture("Porsche", "MUFF", "PA12") );
  clients[8] = creeClient("Falcone", 651321, creeVoiture("Lotus", "ANTIFA", "GE128") );
  clients[9] = creeClient("Gisin", 047121454, creeVoiture("Fiat", "SOME", "PA19") );

  //printf n'aime pas imprimer des int directement, il faut nettre %d\n \n 0 => nouvelle ligne %u => paramètre à imprimer (u = unsigned decimal integer, s = string).
  //http://www.cplusplus.com/reference/cstdio/printf/
  printf("%u\n", sizeof(clients)/sizeof(clients[0])); //Il n'y a pas de length en C! Il faut récupérer cette valeur en divisant la taille en bits du tableau entier divisé par celle d'un élément pour avoir le nombre total d'éléments.

  clients[2].voiture.etat = reparee;
  clients[7].voiture.etat = reparee;
  
  afficheVoituresReparees(clients);
  afficheVoituresReparees(clients);
  return 0;
}