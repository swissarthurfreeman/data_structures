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
    static TPassager table[M]; //On d�clare la table.
    TPassager courant;
    int index = 0;
    //On parcourt toutes les lignes du fichier, en ins�rant dans le tableau.
    int collisions, insertions = 0;
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {
        courant = createPassager(id, nom, prenom, age, numSiege); //On cr�e le passager temporaire.
        index = hashLineaire(nom, index); //On lui calcule un index.
        RETRY:if(table[index].siege != 0) { //Si on est � une case occup�e, on d�cale et on retente.
            index++; //On d�cale l'index de 1, jusqu'� trouver de la place.
            collisions++; //On incr�mente le nombre de collisions.
            if(index > M) {
                printf("Il n'y a pas de case disponible, on retourne a 0. \n");
                index = 0;
            }
            goto RETRY;
        } else {
            insertions++;
            table[index] = courant; //On ins�re � cet index.
        }
    }
    printf("Il y a eu %d, insertions et %d collisions pour la methode lineaire. \n", insertions, collisions);
    fclose(fp);

    //afficheRepartition(table);
    calculeRepartition(table);

    return 0;
}
