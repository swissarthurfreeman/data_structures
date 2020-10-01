/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "objects.h" //Contient objets et m�thodes associ�es aux passagers.
#include "codemot.h" //Contient le code permettant d'associer un int � une cha�ne de caract�res.
#include "affiche_resultats.h" //Contient les fonctions pour afficher la table de hachage.

int hashDouble(char nom[10], int i) {
    int a1 = 1;
    int a2 = 3; //Fonction de double hachage.
    return (a1*codeMot(nom) + a2*codeMot(nom)*i) % M; //Avec H1 et H2 �tant des fonctions simples.
}

int main() {
    //On configure les variables temporaires pour lire le fichier.
    char prenom[10], nom[10];
    int age, numSiege, id; //Variable temporelles pour naviguer sur les propri�t�s.
    FILE * fp;
    fp = fopen("passagers10000.txt", "r"); //On ouvre le fichier.
    TPassager courant; //Passager temporaire, red�fini � chaque it�ration.
    static TPassager table[M]; //Initialisation de la table. M est contenu dans objets.h et vas de 1000 � 10000 au choix.

    int index; //Index courant du tableau.

    //On parcourt toutes les lignes du fichier, en ins�rant dans le tableau.
    int collisions = 0, insertions = 0; //On comptera les collisions et insertions.
    while (fscanf(fp, "%d %s %s %d %d", &id, prenom, nom, &age, &numSiege) != EOF) {

        courant = createPassager(id, nom, prenom, age, numSiege); //On cr�e un passager.

        int i = 0; //i est la variable qui s'incr�mente lors de collisions.
        index = hashDouble(nom, i) % M; //On calcule i via la fonction de hachage.
        RETRY:if(table[index].siege != 0) { //Si on est � une case occup�e, on d�cale et on retente.
            i++; //On incr�mente donc i.
            if(i > M/10) { //Condition d'arr�t, si on fait 1000 essais pour une case, c'est bon quoi, y'a pas de place.
                goto EXIT;
            }
            index = hashDouble(nom, i) % M; //on recalcule l'index avec un nouveau d�calage.
            collisions++; //On incr�mente le nombre de collisions.

            if(index > M) { //Si on est en dehors du tableau, on recommence � 0.
                printf("Il n'y a pas de case disponible, on retourne � 0. \n");
                index = 0;
            }
            goto RETRY; //On r�essaye.
        } else if(table[index].siege == 0) { //Si on est � une case vide.
            insertions++; //On incr�mente le nombre d'insertions.
            table[index] = courant; //On ins�re � cet index.
        }
    }
    //On affiche le nombre d'insertions et collisions.
    EXIT:printf("Il y a eu %d, insertions et %d collisions pour le double hachage. \n", insertions, collisions);

    afficheRepartition(table); //On affiche les r�sultats esth�tiques.
    calculeRepartition(table); //Ces fonctions sont contenues dans affiche_resultats.h

    fclose(fp);
    return 0;
}
