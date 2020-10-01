#include <stdio.h>
#include <string.h>
#define MAX_TAILLE 10
#define true 1
#define false 0

//Structure qui gère les catégories. Booléens contenus dans stdbool.h.
struct TCategorie {
  char name[25];
  int tache_A;
  int tache_B;
};

//Structure qui gère la pile, statique.
struct TPile {
  unsigned int sommet;
  struct TCategorie assiettes[MAX_TAILLE];
};

//Fonction qui permet l'ajout d'un élément au sommet de la pile.
//Il faut lui passer des pointeurs! C ne modifie pas la variable dans le main, elle la copie 
//à l'intérieur de la fonction et la modifie la!
void add(struct TPile *Pile, struct TCategorie element) {

  Pile->sommet = Pile->sommet + 1; //On rajoute un élément dans la pile.

  if (Pile->sommet < MAX_TAILLE) { //Si la taille limite n'est pas dépassée.
    Pile->assiettes[Pile->sommet] = element; //On empile.
    
  } else if (Pile->sommet == 10) { //Si on est au max.
    Pile->assiettes[Pile->sommet] = element; //On empile, mais on emet un warning.
    printf("La pile est remplie!");
  } else {
    printf("Error, stack overflow."); //On déclenche une erreur de débordement de pile.
  }

}

//Fonction qui permet de réduire la taille de la pile
//En se "débarassant" du dernier élément.
void pop(struct TPile Pile) {
  Pile.sommet = Pile.sommet - 1;
}

struct TCategorie create(char name[25], int paramA, int paramB) {
  struct TCategorie categorie;
  strcpy(categorie.name, name);
  categorie.tache_A = paramA;
  categorie.tache_B = paramB;
  return categorie;
}

//Checklist prends une référence mémoire à la pile en paramètre.
void checkList(struct TPile *pile) {

  int isGood; //Initialement on suppose que tout est en ordre.
  isGood = 1;
  if ((pile->assiettes[pile->sommet].tache_A == 1) && //Si la catégorie courante est bonne.
     (pile->assiettes[pile->sommet].tache_B == 1) &&
     (pile->sommet >= 1))
  {
    pile->sommet = pile->sommet - 1; //On "dépile" en déplaçant le pointeur.
    goto RECURSION; //On recommence, le label est en fin de fonction.
    
  } else if (pile->sommet >= 1){ //Si il y a une erreur et qu'on est toujours dans la pile.
    printf("Error at sub-category, please update. \n");
    isGood = 0; //On mets isGood à 0 pour signaler l'erreur.
  } else if (pile->sommet == 0) {
    
    pile = NULL;
    printf("\nAll systems go, prepare for take off.\n");

    return; //return permet de cesser la récusion.
  }

  //Si il y a une erreur.
  if (isGood == 0) {
    char A[20]; //On lit ce que l'utilisateur écrit.
    char B[20]; //Je me suis servi du code trouvé sur les sites mis en commentaires pour la lecture d'inputs.
    printf("Please update %s, (1 or 0 for true or false) \n", pile->assiettes[pile->sommet].name);
    fputs("Task A: ", stdout); //source = https://www.daniweb.com/programming/software-development/tutorials/45806/user-input-strings-and-numbers-c
    fflush(stdout); /* http://c-faq.com/stdio/fflush.html */
    fgets(A, sizeof A, stdin);

    int number;
    if ( sscanf(A, "%d", &number) == 1 )
    {
      pile->assiettes[pile->sommet].tache_A = number;
    }
    
    fputs("Task B: ", stdout); 
    fflush(stdout); 
    fgets(B, sizeof B, stdin);
    
    int number2;
    if ( sscanf(B, "%d", &number2) == 1 )
    {
      pile->assiettes[pile->sommet].tache_B = number2;
    }
  }
  RECURSION:checkList(pile); //On recommence, toujours avec la pile.
}

//To do: Implémenter la lecture de fichier texte.
int main(void) {

  struct TCategorie pilote,co_pilote, aile_droite, aile_gauche;
  pilote = create("pilote", true, true);
  co_pilote = create("co_pilote", true, true);
  aile_droite = create("aile_droite", false, true);
  aile_gauche = create("aile_gauche", true, true);
 
  struct TPile pile;

  struct TPile *emplacementPile;

  emplacementPile = &pile;

  pile.sommet = 0;
  
  //On empile nos sous-catégories.
  add(emplacementPile, aile_gauche);
  add(emplacementPile, aile_droite);
  add(emplacementPile, co_pilote);
  add(emplacementPile, pilote);

  printf("Nb sous-catégories: %i \n", pile.sommet);

  checkList(emplacementPile);
  return 0;
}