/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/
#include <stdio.h>
#include <string.h>

int codeChar(char c) {
    return (int) c;
}

unsigned int codeMot(char mot[10]) {
    int res = 0;
    for(int i = 0; i < 10; i++) {
        res = res + codeChar(mot[i])*puissance(26,i);
    }
    return res;
}
