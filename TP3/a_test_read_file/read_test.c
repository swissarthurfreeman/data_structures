#include <stdio.h>
#include <stdlib.h>
struct TPersonne {
    char nom[10];
    char prenom[10]
};


int main () {
   char str1[10], str2[10], str3[10];
   int year;
   FILE * fp;
   fp = fopen ("file.txt", "r");
   while (fscanf(fp, "%s %s %s %d", str1, str2, str3, &year) != EOF) {
       printf("Read String1 |%s|\n", str1 );
       printf("Read String2 |%s|\n", str2 );
       printf("Read String3 |%s|\n", str3 );
       printf("Read Integer |%d|\n", year );
   }

   fclose(fp);

   return(0);
}
