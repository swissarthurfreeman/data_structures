struct TPersonne {
  int unsigned age; //Propriétés d'une personne.
  int unsigned sex;
};

//Fonction pour créer une personne.
struct TPersonne createPersonne(int unsigned age, int unsigned sex) {
  struct TPersonne personne;
  personne.age = age;
  personne.sex = sex;
  return personne;
}

struct TFile {
  struct TPersonne contenu; //Le contenu est une personne.
  struct TFile* suivant; //TChaine contient un pointeur sur une autre case.  
};

 
void createFile(struct TFile *debut, int n, struct TFile *newEnd) {
  //Du moment que n est plus grand ou égal à 0, on crée des éléments en chaîne.
  if(n >= 0) {
    debut->suivant = malloc(sizeof(*debut)); //On alloue la mémoire requise. (évite des erreurs de segmentation)
    debut->contenu = createPersonne(rand() % 100, rand() % 2); //On crée le contenu.
    //debut->contenu = createPersonne(18,1);
    //Si on a finit de créer notre liste, on fait pointer le dernier éléments
    //sur newEnd, qui peut être NULL si c'est la première.
    if(n == 0) {
      debut->suivant = newEnd; //Quand on rajoute des gens, on le fait pointer sur le debut de l'anciennefile.
    }
    //On rappele la fonction récursive, avec le prochain élément et on décrémente n.
    createFile(debut->suivant, n-1, newEnd);
  } else {
    return; //Si n est négatif, on arrête de boucler, car on a crée ce qu'on voulait.
  }
}

//Fonction qui permet de rajouter des gens à la file.
//Renvoie un nouveau pointeur qui pointe sur le début de la nouvelle file.
struct TFile* add(struct TFile *debut, int n) {
  struct TFile* newStart; //newStart est le pointeur de la nouvelle file.
  newStart = malloc(sizeof(*newStart)); //On l'alloue.
  //On crée une nouvelle file ce pointeur, de n éléments
  createFile(newStart, n, debut); //et le pointeur final pointera sur début qui est l'ancienne file.
  return newStart;
}

int getFileLength(struct TFile *debut, int n) {
  if(debut->suivant == NULL) {
    //printf("\n Right before return: %i", n-1);
    return n;
  } else {
    //printf("\n%i", n);
    if (debut->contenu.age < 100) {
      getFileLength(debut->suivant, n+1);
    } else {
      return n;
    }
  }
}

//Fonction qui supprime les n derniers éléments de la chaîne.
void removeAllFrom(struct TFile *location, int position, int i) {
	//On parcours la chaîne récursivement jusqu'à la position souhaitée.
    if(position+1 == i) {
        struct TFile* tmp; //On crée une variable temporaire.
        while (location != NULL) { //Du moment qu'on est pas sur un pointeur null.
            tmp = location; 
            location = location->suivant; //On se décale au suivant.
            free(tmp); //On libère le pointeur sur lequel on était.
        }
        return; 
    } else {
    	//Si on est aps au bon index, on avance sur la chaîne i est l'index courant.
    	//Position est l'index souhaité.
      removeAllFrom(location->suivant, position, i + 1);
    }
}

void removeLast(struct TFile *debut, int n) {
  int length;
  length = getFileLength(debut, 0);
  removeAllFrom(debut, length-n, 0);
}
