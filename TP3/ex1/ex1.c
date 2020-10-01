/*#################################################################
# Ex 1.) TP3.)                                                    #
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

struct TChaine { //Structure récursive, contenant un pointeur sur elle même.
    struct TPassager contenu;
    struct TChaine* suivant;
};

//Fonction qui crée et renvoie un TPersonne.
struct TPersonne creePersonne(char nom[10], char prenom[10], int age) {
    struct TPersonne newPersonne;
    newPersonne.age = age;
    strcpy(newPersonne.nom, nom);
    strcpy(newPersonne.prenom, prenom);
    return newPersonne;
};

//Fonction qui renvoie et crée un TPassager, prenant un TPersonne en paramètre.
struct TPassager creePassager(struct TPersonne personne, int numClient, int numSiege) {
    struct TPassager newPassanger;
    newPassanger.personne = personne;
    newPassanger.numClient = numClient;
    newPassanger.numSiege = numSiege;
    return newPassanger;
};

//Fonction qui ajoute une personne au bout de la liste.
void add(struct TPassager newElement, struct TChaine* debut) {
    if (debut->suivant != NULL) { //Si le pointeur suivant n'est pas NULL.
        add(newElement, debut->suivant); //On passe au suivant et on regarde.
    } else { //Si il est nul.
        debut->suivant = malloc(sizeof(*debut->suivant)); //On l'alloue (pointera donc sur un nouvel élément vide)
        debut->contenu = newElement; //On rempli son contenu avec un TPassager.
    }
}

int main () {
    //Code récupéré sur: https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm
    //Modifications faites par moi.
    char prenom[10], nom[10];
    int age, numSiege, numClient;
    FILE * fp;
    fp = fopen("passagers.txt", "r");

    struct TChaine* debut;
    debut = malloc(sizeof(*debut));

    struct TPassager current;
    while (fscanf(fp, "%d %s %s %d %d", &numClient, prenom, nom, &age, &numSiege) != EOF) {
        current = creePassager(creePersonne(nom, prenom, age), numClient, numSiege); //Code à moi.
        add(current, debut); //code à moi.
        printf("%s, %s, \n", nom, prenom);
    }
    fclose(fp); //Fin du code de tutorialspoint.


    printf("Name of first passenger: %s\n", debut->contenu.personne.nom);
    //C'est bien la deuxième personne dans la liste.
    printf("Name of second passenger: %s\n", debut->suivant->contenu.personne.nom);
    //C'est bien la dernière personne dans la liste.
    printf("Name of 39th passenger: %s\n", debut->suivant->suivant->suivant->suivant->
    suivant->suivant->suivant->suivant->suivant->suivant->suivant->suivant->suivant->
    suivant->suivant->suivant->suivant->suivant->suivant->suivant->suivant->suivant->
    suivant->suivant->suivant->suivant->suivant->suivant->suivant->suivant->suivant->
    suivant->suivant->suivant->suivant->suivant->suivant->suivant->contenu.personne.nom);

    return 0;
}
