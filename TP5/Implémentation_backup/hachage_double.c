/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h" //Contient objets et méthodes associées aux passagers.
#include "codemot.h" //Contient le code permettant d'associer un int à une chaîne de caractères.
#include "affiche_resultats.h" //Contient les fonctions pour afficher la table de hachage.

int hashDouble(char nom[10], int i) {
    int a1 = 1;
    int a2 = 3; //Fonction de double hachage.
    return (a1*codeMot(nom) + a2*codeMot(nom)*i) % M; //Avec H1 et H2 étant des fonctions simples.
}

int main() {
    //On configure les variables temporaires pour lire le fichier.
    char prenom[10], nom[10];
    int age, numSiege, id; //Variable temporelles pour naviguer sur les propriétés.
    FILE * fp;
    fp = fopen("passagers10000.txt", "r"); //On ouvre le fichier.
    TPassager courant; //Passager temporaire, redéfini à chaque itération.
    static TPassager table[M]; //Initialisation de la table. M est contenu dans objets.h et vas de 1000 à 10000 au choix.

    int index; //Index courant du tableau.

    //On parcourt toutes les lignes du fichier, en insérant dans le tableau.
    int collisions = 0, insertions = 0; //On comptera les collisions et insertions.
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {

        courant = createPassager(id, nom, prenom, age, numSiege); //On crée un passager.

        int i = 0; //i est la variable qui s'incrémente lors de collisions.
        index = hashDouble(nom, i) % M; //On calcule i via la fonction de hachage.
        RETRY:if(table[index].siege != 0) { //Si on est à une case occupée, on décale et on retente.
            i++; //On incrémente donc i.
            if(i > M/10) { //Condition d'arrêt, si on fait 1000 essais pour une case, c'est bon quoi, y'a pas de place.
                goto EXIT;
            }
            index = hashDouble(nom, i) % M; //on recalcule l'index avec un nouveau décalage.
            collisions++; //On incrémente le nombre de collisions.

            if(index > M) { //Si on est en dehors du tableau, on recommence à 0.
                printf("Il n'y a pas de case disponible, on retourne à 0. \n");
                index = 0;
            }
            goto RETRY; //On réessaye.
        } else if(table[index].siege == 0) { //Si on est à une case vide.
            insertions++; //On incrémente le nombre d'insertions.
            table[index] = courant; //On insère à cet index.
        }
    }
    //On affiche le nombre d'insertions et collisions.
    EXIT:printf("Il y a eu %d, insertions et %d collisions pour le double hachage. \n", insertions, collisions);

    afficheRepartition(table); //On affiche les résultats esthétiques.
    calculeRepartition(table); //Ces fonctions sont contenues dans affiche_resultats.h

    fclose(fp);
    return 0;
}
