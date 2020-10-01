/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "objects.h"
#include "codemot.h"
#include "affiche_resultats.h"

int hashLineaire(char mot[10], int i) {
    return (codeMot(mot) + i) % M;
}

int main() {
    //On configure les variables temporaires pour lire le fichier.
    char prenom[10], nom[10];
    int age, numSiege, id;
    FILE * fp;
    fp = fopen("passagers40000.txt", "r"); //On ouvre le fichier.
    static TPassager table[M]; //On déclare la table.
    TPassager courant;
    int index = 0;
    //On parcourt toutes les lignes du fichier, en insérant dans le tableau.
    int collisions, insertions = 0;
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {
        courant = createPassager(id, nom, prenom, age, numSiege); //On crée le passager temporaire.
        index = hashLineaire(nom, index); //On lui calcule un index.
        RETRY:if(table[index].siege != 0) { //Si on est à une case occupée, on décale et on retente.
            index++; //On décale l'index de 1, jusqu'à trouver de la place.
            collisions++; //On incrémente le nombre de collisions.
            if(index > M) {
                printf("Il n'y a pas de case disponible, on retourne a 0. \n");
                index = 0;
            }
            goto RETRY;
        } else {
            insertions++;
            table[index] = courant; //On insère à cet index.
        }
    }
    printf("Il y a eu %d, insertions et %d collisions pour la methode lineaire. \n", insertions, collisions);
    fclose(fp);

    //afficheRepartition(table);
    calculeRepartition(table);

    return 0;
}
