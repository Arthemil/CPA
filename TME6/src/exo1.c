#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "tas_array.h"
#include "cle.h"

char * FILE_TEST	= "./ressource/testGraphe_clean.txt";
char * FILE_EMAIL	= "/Vrac/TME_CPA_19-02-20/email-Eu-core-clean.txt";
char * FILE_AMAZON	= "/Vrac/TME_CPA_19-02-20/com-amazon.ungraph-clean.txt";
char * FILE_LJ		= "/Vrac/TME_CPA_19-02-20/com-lj.ungraph-clean.txt";
char * FILE_ORKUT	= "/Vrac/TME_CPA_19-02-20/com-orkut.ungraph-clean.txt";

int NODE_TEST	= 10;
int NODE_EMAIL	= 986;
int NODE_AMAZON	= 334863;
int NODE_LJ	= 3997962;
int NODE_ORKUT	= 3072441;


tas* create_heap(char* s, int  * nb_nodes, int ** newList){
	printf("ok in\n");
	int max_node = -1;
	int* liste = calloc(0,sizeof( int));
	tas* heap = mktas();
	FILE * f = fopen(s,"r");
	int u,v;
	int nb_ajouts = 0;
	int i;
	//liste[0]=-1; //initialize list
	while(fscanf(f,"%d %d\n", &u, &v) != EOF){
		//printf("ok\n");
		if(u > max_node-1){
			int tmp = max_node +1;
			max_node=u;
			int i;
			liste = realloc(liste, (1+max_node)*(sizeof(int)));
			for (i = tmp;i<=max_node;i++)liste[i] = -1; 
		}
		if(v > max_node-1){
			int tmp = max_node +1;
			max_node = v;
			int i;
			liste = realloc(liste, (1+max_node)*(sizeof(int)));
			for (i = tmp;i<=max_node;i++)liste[i] = -1;
		}
		//ajout des elements dans le tas, sans les placer
		if(liste[u]==-1){
			ajout(heap, parse_cle(u, 1), liste);
			liste[u]=nb_ajouts; // garder l'emplacement dans le tas
			nb_ajouts++;
	//test		
			//heap->a[liste[u]]->degree ++;
			heap->a[liste[u]]->voisins = calloc(1,sizeof(int));
			heap->a[liste[u]]->voisins[0] = v;
			
		}else{
			
			//le degre du noeud de numero stocké dans la case u du listeleau
			heap->a[liste[u]]->voisins = realloc(heap->a[liste[u]]->voisins, (heap->a[liste[u]]->degree+1)*sizeof(int));
			heap->a[liste[u]]->voisins[heap->a[liste[u]]->degree] = v;
			heap->a[liste[u]]->degree ++;
		}
		if(liste[v]==-1){
			ajout(heap, parse_cle(v, 1), liste);
			liste[v]=nb_ajouts;
			nb_ajouts++;
		//test
			//heap->a[liste[v]]->degree ++;
			heap->a[liste[v]]->voisins = calloc(1,sizeof(int));
			heap->a[liste[v]]->voisins[0] = u;

		}else{
			//le degre du noeud de numero stocké dans la case v du listeleau
			heap->a[liste[v]]->voisins = realloc(heap->a[liste[v]]->voisins, (1+heap->a[liste[v]]->degree)*sizeof(int));
			heap->a[liste[v]]->voisins[heap->a[liste[v]]->degree] = u;
			heap->a[liste[v]]->degree ++;
		}
		
		
	
	}
	//printf("heu\n");
	for(i=0; i<= max_node; i++){
		//if(liste[i]==-1)continue;
		
		//printf("liste[i]=%d, i = %d\n",liste[i], i);
		printf("a[%d]=node %d,degree %d\n",i,heap->a[i]->node,heap->a[i]->degree);
		//printf("\t%d\t%d\t degree = %d\n", heap->a[liste[i]]->node,liste[i],heap->a[liste[i]]->degree);
	}
	//Organisation du tas
	//heap = consiter(heap->a, max_node, liste);
	printf("nb_ajout =%d\n",nb_ajouts);
	(*newList)=liste;
	return heap;
	
	
}


int k_core_decomposition(tas * heap, int* liste ){
	int i = heap->size;
	int c = 0;
	int* N = (int*)malloc(sizeof(int)*i);
	while(!empty(heap)){
		//printf("aaa\n");
		cle* v = heap->a[0];
		printf("bbbb\n");
		int j;
		printf("v->node = %d v->degree = %d",v->node,v->degree);
		printf("a\n");
		
		for(j=0;j<(v->degree); j++){
			//printf("ccccc\n");
			
			printf("v->node = %d\n",v->node);
			printf("v->voisins[j]=%d\n",v->voisins[j]);
			if(liste[ v->voisins[j] ]==-1)continue;
			printf("dddddd liste[ v->voisins[j] ]=%d\n",liste[v->voisins[j]]);
			printf("heap->a[liste[ v->voisins[j] ]]->node = %d",heap->a[liste[ v->voisins[j] ]]->node);
			heap->a[liste[ v->voisins[j] ]]->degree--;
			printf("eeeeeee\n");
			v->degree--;
			int k;
			printf("ffffffffffffffffff\n");
			for(k=0; k<(heap->a[liste[v->voisins[j]]]->degree); k++){	
						
				if(heap->a[liste[v->voisins[j]]]->voisins[k] == v->node){
					heap->a[liste[v->voisins[j]]]->voisins[k] = -1;
				} 
			}
			printf("ok\n");
		}
		if(c<(v->degree)){
			c = (v->degree);
		}
		printf("c= %d v = %d\n",c,v->node);
		supprmin(heap, liste);
		N[v->node]=i;
		i=i-1;
	}
	return c;
}








int main(){
	int* liste ;
	tas* heap = create_heap(FILE_EMAIL, &NODE_EMAIL, &liste);
	int c = k_core_decomposition(heap, liste);
	
	printf("K-core = %d\n", c);

	return 0;



}

