/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h"
#include "codemot.h"
#include "affiche_resultats.h"

int hashSimple(char mot[10]) { //Fonction de hachage simple.
    return codeMot(mot) % M;
}

int main() {
    //On configure les variables temporaires pour lire le fichier.
    char prenom[10], nom[10];
    int age, numSiege, id;
    FILE * fp;
    fp = fopen("passagers.txt", "r"); //On ouvre le fichier avec 10 000 passagers.

    static TPassager table[M]; //On déclare le tableau de passagers de taille M.
    TPassager courant;
    int index;

    //On parcoure toutes les lignes du fichier.
    int collisions, insertions = 0; //On comptera les collisions et insertions.
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {
        courant = createPassager(id, nom, prenom, age, numSiege); //Passager temporaire, redéfini à chaque itération.
        index = hashSimple(courant.nom); //On calcule l'index avec la fonction de hashSimple.
        if(table[index].siege != 0) { //Si on est à une case occupée,
            collisions++; //On incrémente le nombre de collisions et on ne fait rien.
        } else {
            insertions++; //Sinon on insère et on incrémente le nombre d'insertions.
            table[index] = courant;
        }
    }
    printf("Il y a eu %d, insertions et %d collisions pour la methode simple. \n", insertions, collisions);
    fclose(fp);

    //afficheRepartition(table); //C'est des gros clusters !
    //calculeRepartition(table);

    return 0;
}
