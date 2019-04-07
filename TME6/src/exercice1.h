#ifndef __include_fichier_h__
#define __include_fichier_h__

#include "cle.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct Node Node;
struct Node{
	int num;
	int nb_voisins;
	int nb_entrants;
	Node ** voisins;
};

typedef struct {
  int size;
  cle** a;
} tas;


Node ** create_adjacency_array(char * s,int  * nb_nodes);

cle* parse_cle(int node, int degree);

int eg(cle* a, cle* b);

int inf(cle* a, cle* b);

double lg (double x, double base);

tas * ConsIter_Tableau(cle **liste,int nb_nodes);

tas * Remonter(tas * T, int indice);

tas * SupprMin_Tableau(tas * T);

tas* create_heap(char* s, int  nb_nodes);

void k_core_decomposition(char* s, int  nb_nodes);

#endif /* #ifndef __include_fichier_h__ */

