typedef enum {
  false, true
} bool;

struct TContenu {
  char nom[20];
  char IATA[3];
  bool visite;
};

struct TVoisins {
  int indexNoeud;
  struct TVoisins *suivant; 
};

struct TNoeud {
 struct TContenu contenu;
 struct TVoisins *voisins;
};


//File comme queue.
struct TFile {
  struct TNoeud noeud;
  struct TFile *suivant;
};