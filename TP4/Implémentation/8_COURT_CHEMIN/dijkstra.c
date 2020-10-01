//Ce programmme ce sert de la matrice d'adjacence pour se représenter le graphe.
#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h>

//Nombre de noeuds du graphe. (global)
#define V 8 
#define INFINI INT_MAX

typedef enum {
  false, true
} bool;
  
// Fonction qui permet de trouver l'index auquel le noeud à distance minimale non 
//inclu dans P est. (en trouvant un minimum dans un set implémenté via un tableau de précense)
int minDistance(int distance[], bool P[]) { 
    //On intialise la distance minimale (infinie).
    int minimum = INFINI; 
    int minimum_index;
    //Pour chaque noeud, on suppose qu'il est le minimum, et on regarde le suivant,
    //si le suivant est plus petit on mets à jour, sinon, on continue.
    for (int v = 0; v < V; v++) {
      //Si le noeud n'est pas dans P et sa distance plus petite ou égale infini.
      if (P[v] == false && distance[v] <= minimum) { 
          minimum = distance[v]; //On règle min comme la distance de ce noeud.  
          minimum_index = v; //On choisit cet index
      } //On recommence pour tous les noeuds, comme cela le plus petit gagne.
    }
    return minimum_index; //On renvoie ainsi le plus petit. (l'index de celui-ci)
}
  
//Fonction pour afficher la distance à la source.
void afficherResultat(int distances[]) { 
    printf("Noeud, distance à la source \n");
    for (int i = 0; i < V; i++) {
        printf("%d, %d\n", i, distances[i]);
    }
} 
  
//Fonction de parcours de plus court chemin via matrice d'adjacence. (graph est la matrice)
void dijkstra(int graphe[V][V], int src) { 
    int distances[V]; ////dist[i] sera la distance la plus courte de la source (int) au noeud i.
    bool P[V]; //P[i] sera vraie si le noeud i est est dans P.
    // On initialise toutes les distances à infini et on initialise P, tableaude boulleans de taille 8. (pour le nombre de noeuds)
    for (int k = 0; k < V; k++) {
        distances[k] = INFINI; //P est un set, il est donc naturel d'utiliser un tableau de précense. 
        P[k] = false; 
    }
    distances[src] = 0; //Distance source-source = 0. 
  
    //On cherche le plus court chemin pour chaque noeud.
    for (int count = 0; count < V - 1; count++) { 
      //On applique dijkstra, on prends le noeud de distance minimale parmis les noeuds
      //adjacents à P non visités.
      int u = minDistance(distances, P); 
  
      //On marque le noeud comme dans P.
      P[u] = true; 
  
      //On mets à jour les distances de tous ses voisins. 
      for (int v = 0; v < V; v++) {
        //On mets à jour dist[v] seulement si pas dans P et qu'un lien existe de u à v, et que 
        //le poids de u plus le poids de u à v est plus petit que la distance de v. (dist[v])
        if (!P[v] && graphe[u][v] && distances[u] != INFINI && distances[u] + graphe[u][v] < distances[v]) { 
            distances[v] = distances[u] + graphe[u][v]; //distance = distance du sommet + poids entre u et v.
        }
      }
    } 
    //On affihe le tableau construit.
    afficherResultat(distances); 
} 
  

int main() { 
    //                   A0 A1 A2   A3  A4 A5   A6 A7
    int graphe[V][V] = { { 0, 0, 0, 709, 54, 0, 114, 0 },
                        { 0, 0, 0, 0, 101, 0, 0, 0 }, 
                        { 0, 0, 0, 0, 60, 0, 0, 46 }, 
                        { 709, 0, 0, 0, 720, 769, 0, 0}, 
                        { 54, 101, 60, 720, 0, 0, 0, 60},
                        { 398, 0, 0, 769, 418, 0, 0, 0}, 
                        { 0, 0, 0, 0, 0, 0, 0, 97 }, 
                        { 90, 0, 0, 726, 60, 0, 0, 0} }; 
    dijkstra(graphe, 0); //On commence au noeud 0, donc londres. 
    return 0; 
} 