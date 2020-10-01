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
    return (codeMot(nom) + a1*i + a2*puissance(i, 2)) % M; //La fonction puissance renvoie d�j� un modulo M. (�vite les overflow au passage)
}

int main() {
    //On configure les variables temporaires pour lire le fichier.
    char prenom[10], nom[10];
    int age, numSiege, id;
    FILE * fp;
    fp = fopen("passagers.txt", "r"); //On ouvre le fichier.

    static TPassager table[M]; //On d�clare la table.
    TPassager courant; //On d�clare le passager "it�rateur"

    int index;
    //On parcourt toutes les lignes du fichier, en ins�rant dans le tableau.
    int collisions = 0, insertions = 0; //On compte le nombre d'insertions.
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {
        courant = createPassager(id, nom, prenom, age, numSiege); //On cr�e un passager � chaque it�ration.
        int i = 0; //facteur de d�calage.
        index = hashQuad(nom, i); //On calcule l'index dans la table.
        RETRY:if(table[index].siege != 0) { //Si on est � une case occup�e, on d�cale et on retente.
            i++;
            if(i > M/10) { //Si on a tent� 1000 d�calages, on s'arr�te.
                goto EXIT;
            }
            index = hashQuad(nom, i); //On d�cale l'index de i, jusqu'� trouver de la place.
            collisions++; //On incr�mente le nombre de collisions.

            if(index > M) { //Si on d�borde, on retourne � 0.
                printf("Il n'y a pas de case disponible, on retourne � 0. \n");
                index = 0;
            }
            goto RETRY;
        } else {
            insertions++; //Si on a de la place...
            table[index] = courant; //...on ins�re � cet index.
        }
    }
    EXIT:printf("Il y a eu %d, insertions et %d collisions pour la methode quadratique. \n", insertions, collisions);
    fclose(fp);

    //afficheRepartition(table);
    calculeRepartition(table);

    return 0;
}
