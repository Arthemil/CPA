#include <stdlib.h>
#include <stdio.h>
#include "cle.h"


//fonctionne, ne pas toucher
cle* parse_cle(int node, int degree) {
  cle* res = (cle*)malloc(sizeof(cle));
  res->node = node;
  res->degree = degree;
  res->core = -1;
  res->voisins = NULL;
  return res;
}

int eg(cle* a, cle* b) { 
  return (a->nb_voisins == b->nb_voisins);

}

int inf(cle* a, cle* b) {
  return (a->nb_voisins) < (b->nb_voisins);
}

void print(cle * c){
  printf("node %d of degree %d\n", c->node, c->degree); 
}
