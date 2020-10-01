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

int hashQuad(char nom[10], int i) { //Fonction de hachage quadratique.
    int a1 = 1; int a2 = 3;
    return (codeMot(nom) + a1*i + a2*puissance(i, 2)) % M; //La fonction puissance renvoie déjà un modulo M. (évite les overflow au passage)
}

int main() {
    //On configure les variables temporaires pour lire le fichier.
    char prenom[10], nom[10];
    int age, numSiege, id;
    FILE * fp;
    fp = fopen("passagers.txt", "r"); //On ouvre le fichier.

    static TPassager table[M]; //On déclare la table.
    TPassager courant; //On déclare le passager "itérateur"

    int index;
    //On parcourt toutes les lignes du fichier, en insérant dans le tableau.
    int collisions = 0, insertions = 0; //On compte le nombre d'insertions.
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {
        courant = createPassager(id, nom, prenom, age, numSiege); //On crée un passager à chaque itération.
        int i = 0; //facteur de décalage.
        index = hashQuad(nom, i); //On calcule l'index dans la table.
        RETRY:if(table[index].siege != 0) { //Si on est à une case occupée, on décale et on retente.
            i++;
            if(i > M/10) { //Si on a tenté 1000 décalages, on s'arrête.
                goto EXIT;
            }
            index = hashQuad(nom, i); //On décale l'index de i, jusqu'à trouver de la place.
            collisions++; //On incrémente le nombre de collisions.

            if(index > M) { //Si on déborde, on retourne à 0.
                printf("Il n'y a pas de case disponible, on retourne à 0. \n");
                index = 0;
            }
            goto RETRY;
        } else {
            insertions++; //Si on a de la place...
            table[index] = courant; //...on insère à cet index.
        }
    }
    EXIT:printf("Il y a eu %d, insertions et %d collisions pour la methode quadratique. \n", insertions, collisions);
    fclose(fp);

    //afficheRepartition(table);
    calculeRepartition(table);

    return 0;
}
