/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/

#define M 100000
#include <stdio.h>
#include <string.h>

typedef struct TPassager {
    char prenom[10];
    char nom[10];
    int id;
    int age;
    int siege;
} TPassager;

TPassager createPassager(int id, char nom[10], char prenom[10], int age, int siege) {
    TPassager newPassager;
    newPassager.id = id;
    newPassager.age = age;
    newPassager.siege = siege;
    strcpy(newPassager.nom, nom);
    strcpy(newPassager.prenom, prenom);
    return newPassager;
}

int puissance(int x, int y) {
    int base, exp;
    base = x ; exp = y;
    int res = 1;
    if(exp == 0)
        return 1;

    while(exp > 0) {
        res = res*base;
        exp = exp - 1;
    }
    return res % M;
}
