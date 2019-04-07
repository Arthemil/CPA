#ifndef CLE_H_
#define CLE_H_


typedef struct cle cle;
struct cle{
  int node;
  int degree;
  int core;
  int nb_voisins;
  //int* voisins;
  int emplacement;
  cle**voisins;
};


cle * parse_cle(int node, int degree);

int eg(cle* a, cle* b);

int inf(cle* a, cle* b);

void print(cle * c);

#endif /* CLE_H_ */
