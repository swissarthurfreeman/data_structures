/*************************************
*              TP5 Hachage           *
* Auteur: A.Freeman Date: 02/05/2020 *
**************************************/
#define M 10000
#include <stdio.h>
#include <string.h>

void afficheRepartition(TPassager table[M]) {
	printf("La repartition est : \n");
	for(int p = 0; p < M; p++) {
        if(table[p].siege == 0) {
            printf(".");
        } else {
            printf("x");
        }
    }
}

void calculeRepartition(TPassager table[M]) {
    int u = 0;
    for(int k = 0; k < M; k++) {
        if(table[k].siege == 0) {
            if(u != 0)
                printf("%d, ", u);
            u = 0;
        } else {
            u++;
        }
    }
}
