/*TP1:Implémentation
Auteur: Arthur Freeman
10/02/2020*/

/****************************************************************/
/*                        Exercice 2.)                          */
/****************************************************************/

#include <stdio.h>
#include <string.h>

struct TPersonne {
  char nom[50];
  char prenom[50];
  enum sexe{male, female} sexe;
};

struct TEquipage {
  struct TPersonne personne;
  char fonction[50];
};

struct TPassager {
  struct TPersonne personne;
  char nationalite[50];
  char patologies[50];
};

struct TVol {
  char depart[50];
  char arrivee[50];
  char date[50];
  enum status{predecollage, envol, arrivee} status;
};

struct TAvion {
  struct TEquipage equipage[3];
  struct TPersonne personnes[5]; //C'est un jet privé ;)
  struct TVol vol;
  char description[10000];
};

char* getPlaneStatus(int p) {
  char status[50];
  switch(p) {
    case 1:
      strcpy(status, "pré-decollage");
    case 2:
      strcpy(status, "en cours de vol");
    case 3:
      strcpy(status, "arrivé");
  }
  return status;
}

//La taille des tableaux est statique, c'est pas pratique si on a des avions de capacité passagère différente.
void afficheAvions(struct TAvion avions[2]) {
  int p;
  
  printf("\nLa flotte est composée des avions suivants:\n");
  for(p = 0; p < 2; p++) {
    //printf("%d", p);
    printf("\n##################################################\n");
    printf("Nom: %s \n Trajet: %s, %s \n Status: %s \n Date: %s \n", avions[p].description, avions[p].vol.depart, avions[p].vol.arrivee, getPlaneStatus(avions[p].vol.status), avions[p].vol.date);
  }
}

//Fonction pour créer un vol.
struct TVol creeVol(char depart[50], char arrivee[50], int status) {
  struct TVol vol;
  strcpy(vol.depart, depart);
  strcpy(vol.arrivee, arrivee);
  vol.status = status;
  return vol;
}

//Fonction pour créer une personne.
struct TPersonne creePersonne(char nom[50], char prenom[50], int sex) {
  struct TPersonne personne;
  strcpy(personne.nom, nom);
  strcpy(personne.prenom, prenom);
  personne.sexe = sex;
  return personne;
}

//Fonction pour créer un passager.
struct TPassager creePassager(struct TPersonne personne, char nationalite[50], char patologies[50]) {
  struct TPassager passager;
  passager.personne = personne;
  strcpy(passager.nationalite, nationalite);
  strcpy(passager.patologies, patologies);
  return passager;
}

//Fonction pour créer un membre de l'équipage.
struct TEquipage creeEquipage(struct TPersonne personne, char fonction[50]) {
  struct TEquipage equipage;
  equipage.personne = personne;
  strcpy(equipage.fonction, fonction);
  return equipage;
}

//Fonction pour créer un avion.
struct TAvion creeAvion(char desc[50], struct TVol vol, struct TEquipage staff[3], struct TPassager passagers[5], char date[50]) {
  struct TAvion avion;
  strcpy(avion.description, desc);
  avion.vol = vol;
  memcpy(avion.equipage, staff, 3);
  memcpy(avion.personnes, passagers, 5);
  strcpy(avion.vol.date, date);
  return avion; //Il faut retourner pour ne pas avoir warning control reaches end of non-void function.
}

//Fonction pour récupérer le sexe d'un TPersonne.
char* getSexe(int n) {
  switch(n) {
    case 0:
      return "male";
    case 1:
      return "female";
    default:
      return "Hélicoptère d'attaque T200";
  }
}

//Fonction qui renvoie les infos d'un passager.
void getPersonalInfo(struct TPersonne personne) {
  char desc[4000];
  strcpy(desc, strcat(strcat(personne.nom, personne.prenom), getSexe(personne.sexe) ) );
  printf("\n%s", desc);
}

int main(void)
{
  struct TAvion flotte[2];
  struct TEquipage equipage0[3] = { 
    creeEquipage(creePersonne("Yagerin", "Scott", 0), "Pilote"), 
    creeEquipage(creePersonne("Aldrin", "Buzz", 0), "Co-Pilote"), 
    creeEquipage(creePersonne("Jessica", "Jones", 1), "Stewardess")
  };

  struct TPassager passagers0[5] = {
    creePassager(creePersonne("Fabienne", "Mozère", 1), "Suisse", "Stressé"),
    creePassager(creePersonne("Boris", "Dmitri", 0), "Russe", "Adidas"),
    creePassager(creePersonne("Walter", "White", 0), "USA", "Meth-Cook"),
    creePassager(creePersonne("Lan Pen", "Guien", 1), "Vietnam", "Petit"),
    creePassager(creePersonne("Pinkman", "Jesse", 0), "USA", "Meth-Cook")
  };


  flotte[0] = creeAvion("A330 USA", creeVol("Washington", "Moscow", 1), equipage0, passagers0, "11.09.1999");

  struct TEquipage equipage1[3] = { 
    creeEquipage(creePersonne("Travolta", "John", 0), "Pilote"), 
    creeEquipage(creePersonne("BEaver", "Alan", 0), "Co-Pilote"), 
    creeEquipage(creePersonne("Jess", "Wallace", 1), "Stewardess")
  };

  struct TPassager passagers1[5] = {
    creePassager(creePersonne("Fabien", "Momo", 1), "Suisse", "Stressé"),
    creePassager(creePersonne("Boris", "Yeltsin", 0), "Russe", "Adidas"),
    creePassager(creePersonne("Schrader", "Hank", 0), "USA", "PTSD"),
    creePassager(creePersonne("Ho Chi", "Min", 1), "Vietnam", "Petit"),
    creePassager(creePersonne("Eduardo", "Garcia", 0), "USA", "Beard")
  };

  flotte[1] = creeAvion("Concorde", creeVol("Paris", "Rio", 2), equipage1, passagers1, "12.05.2020");

  afficheAvions(flotte);
  struct TPersonne monstre;
  monstre = creePersonne("Fabienne", "Mozère", 1);

  //printf("\n%s", monstre.nom);

  printf("\n%s", flotte[1].personnes[1].nom);

	return 0;
}