#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

char * FILE_TEST	= "../ressource/testGraph_clean.txt";
char * FILE_EMAIL	= "/Vrac/TME_CPA_19-02-20/email-Eu-core-clean.txt";
char * FILE_AMAZON	= "/Vrac/TME_CPA_19-02-20/com-amazon.ungraph-clean.txt";
char * FILE_LJ		= "/Vrac/TME_CPA_19-02-20/com-lj.ungraph-clean.txt";
char * FILE_ORKUT	= "/Vrac/TME_CPA_19-02-20/com-orkut.ungraph-clean.txt";
char * FILE_FRIENDSTER	= "/Vrac/TME_CPA_19-02-20/com-friendster.ungraph.txt";

int NODE_TEST		= 9;
int NODE_EMAIL		= 986;
int NODE_AMAZON		= 334863;
int NODE_LJ		= 3997962;
int NODE_ORKUT		= 3072441;
int NODE_FRIENDSTER	= 65608366;

typedef struct Node Node;
struct Node{
	unsigned int num;
	unsigned int nb_neighbors;
	int marked;
	Node ** neighbors;
};

typedef struct Elem Elem; 
struct Elem {
	unsigned int node;
	Elem * next;
};

typedef struct FIFO FIFO; 
struct FIFO {
	Elem * first;
	Elem * last;
};

void create_adjacency_array(char * s,int  * nb_nodes, Node *** adj){
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int max_node_value = *nb_nodes;
	Node ** list = calloc(max_node_value,sizeof(Node*));
	int u,v;
	while(fscanf(f,"%d\t%d\n", &u, &v) != EOF){
	
		//increasing size of array to the max index value
		if(u>max_node_value-1){			
			int tmp = max_node_value+1;
			max_node_value = u;
			list = realloc(list, (1+max_node_value)*(sizeof(Node*)));
			int i;
			for (i = tmp;i<=max_node_value;i++)list[i] = NULL; 
		}
		if(v>max_node_value-1){
			int tmp = max_node_value+1;
			max_node_value = v;
			list = realloc(list, (1+max_node_value)*(sizeof(Node*)));
			int i;
			for (i = tmp;i<=max_node_value;i++)list[i] = NULL;
		}
		//if Node not yet in the array			
		if(list[u]==NULL){
			Node * newN = malloc(sizeof(Node));
			newN -> num = u;
			newN -> nb_neighbors = 0;
			newN -> neighbors = NULL;
			newN->marked = 0;
			list[u] = newN;
		}
		if(list[v]==NULL){
			Node * newN = malloc(sizeof(Node));
			newN -> num = v;
			newN -> nb_neighbors = 0;
			newN -> neighbors = NULL;
			newN->marked = 0;
			list[v] = newN;
		}
		
		if(list[u] -> neighbors == NULL){//if array of neighbors = null
			list[u] -> neighbors = malloc(sizeof(Node*));
			list[u] -> neighbors[0] = list[v];
			list[u] -> nb_neighbors++;
		}else{
			list[u] -> neighbors = realloc(list[u] -> neighbors,((list[u] -> nb_neighbors)+1)*sizeof(Node*));
			list[u] -> neighbors[list[u] -> nb_neighbors] = list[v];
			list[u] -> nb_neighbors++;
		}
		if(list[v] -> neighbors == NULL){//if array of neighbors = null
			list[v] -> neighbors = malloc(sizeof(Node*));
			list[v] -> neighbors[0] = list[u];
			list[v] -> nb_neighbors++;
		}else{
			list[v] -> neighbors = realloc(list[v] -> neighbors,((list[v] -> nb_neighbors)+1)*sizeof(Node*));
			list[v] -> neighbors[list[v] -> nb_neighbors] = list[u];
			list[v] -> nb_neighbors++;
		}
		
	}
	fclose(f);
	
	//display test
/*	
	int i;
	for (i = 0; i <= max_node_value;i++){
		if(list[i]==NULL)continue;
		printf("noeud %d:\n",list[i]->num);
		printf("\tnb_neighbors:%d\n",list[i]->nb_neighbors);
		unsigned int j;
		printf("neighbors:");
		for(j = 0;j< list[i]->nb_neighbors;j++)printf("%d ",list[i]->neighbors[j]->num);
		printf("\n");
	}
	
*/
	(*nb_nodes) = max_node_value;
	(*adj) = list;
}


//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//

int Max_Connected(Node ***G,int * max_node_v){
	Node ** adj=*G;
	int max_node_value = *max_node_v ;
	
	int i;
	int max_connected = 0;
	
	for(i = 0 ; i <= max_node_value; i++){
		if(adj[i] == NULL || adj[i]->marked)continue;
		FIFO * Fifo = malloc(sizeof(FIFO)); 
		Elem * e = malloc(sizeof(Elem));
		e ->node = adj[i]->num;
		e ->next = NULL;
		
		adj[i]->marked = 1;
		
		Fifo -> first = e;
		Fifo -> last = e;
		int nb_connected = 1;
		
		while(Fifo->first!= NULL){
			Elem * u  = Fifo->first;
			int degree = adj[u->node] -> nb_neighbors;
			int j;
			for(j=0;j<degree;j++){
				Node * v = adj[adj[u->node]->neighbors[j]->num];
				if(!v->marked){ // if the neighbor is unmarked
					v->marked = 1;
					nb_connected++;
					
					Elem * NewE = malloc(sizeof(Elem));
					NewE->node = adj[u->node]->neighbors[j]->num;
					NewE->next = NULL;
					
					//stack
					Fifo -> last -> next = NewE;
					Fifo -> last = NewE;
				}
			} 
			Fifo -> first = Fifo -> first -> next;//unstack
			free(u);
			
		}
		free(Fifo);
		if(nb_connected > max_connected) max_connected = nb_connected;
	}
	
	
	//release memory
/*
	for(i = 0 ; i<= max_node_value; i++){
		if(adj[i]==NULL)continue;
		free(adj[i]->neighbors);
	}
	free(adj);
*/
	
	return max_connected;
}

void reinit_mark(Node ***adj,int * max_node_value){
	int i;
	for(i=0;i<=*max_node_value;i++){
		if((*adj)[i]==NULL)continue;
		(*adj)[i]->marked=0;
	}
}


void Analyse(char * file,int * nb_nodes){
	Node ** adj;
	int max_node_value = *nb_nodes ;
	create_adjacency_array(file,&max_node_value,&adj);

	int max_connected = Max_Connected(&adj,&max_node_value);
	reinit_mark(&adj,&max_node_value);
	
	int i;
	Node * S;
	
	//First BFS
	FIFO * Fifo = malloc(sizeof(FIFO)); 
	
	Elem * e = malloc(sizeof(Elem));
	e ->node = adj[max_node_value]->num;
	e ->next = NULL;
	
	adj[max_node_value]->marked = 1;
	
	Fifo -> first = e;
	Fifo -> last = e;
	
	while(Fifo->first!= NULL){
		Elem * u  = Fifo->first;
		int degree = adj[u->node] -> nb_neighbors;
		int j;
		for(j=0;j<degree;j++){
			Node * v = adj[adj[u->node]->neighbors[j]->num];
			if(!v->marked){ // if the neighbor is unmarked
				
				v->marked = 1;
				
				Elem * NewE = malloc(sizeof(Elem));
				NewE->node = adj[u->node]->neighbors[j]->num;
				NewE->next = NULL;
				
				//stack
				Fifo -> last -> next = NewE;
				Fifo -> last = NewE;
				
				S=adj[adj[u->node]->neighbors[j]->num];//last Node seen
			}
		} 
		Fifo -> first = Fifo -> first -> next;	//unstack
		free(u);
	}
	free(Fifo);

	reinit_mark(&adj,&max_node_value);
	
	int * Dist = malloc(sizeof(int)*(1+max_node_value));
	
	for(i=0;i<=max_node_value;i++)if(adj[i]!=NULL)Dist[i]=0;
	int bound = 0;

	FIFO * Fifo2 = malloc(sizeof(FIFO)); 
	Elem * e2 = malloc(sizeof(Elem));
	e2 ->node = S->num;
	e2 ->next = NULL;
	S->marked = 1;

	Fifo2 -> first = e2;
	Fifo2 -> last = e2;
	
	//second BFS using Dijkstra
	while(Fifo2->first!= NULL){
		Elem * u  = Fifo2->first;
		int degree = adj[u->node] -> nb_neighbors;
		int j;
		for(j=0;j<degree;j++){
			Node * v = adj[adj[u->node]->neighbors[j]->num];
			if(!v->marked){ // if the neighbor is unmarked
				v->marked = 1;
				Elem * NewE = malloc(sizeof(Elem));
				NewE->node = adj[u->node]->neighbors[j]->num;
				NewE->next = NULL;
				
				//stack
				Fifo2 -> last -> next = NewE;
				Fifo2 -> last = NewE;
			
				Dist[v->num] = Dist[u->node] + 1;
				if(bound< Dist[v->num])bound = Dist[v->num];
			}
		} 
		Fifo2 -> first = Fifo2 -> first -> next; //unstack
		free(u);	
	}
	free(Fifo2);
	
	//release memory
	for(i = 0 ; i<= max_node_value; i++){
		if(adj[i]==NULL)continue;
		free(adj[i]->neighbors);
	}
	free(adj);
	printf("file: %s\nnumber of node connected = %d\n\tratio = %f%%\n",file,max_connected,100.0*(max_connected/(*nb_nodes)));
	printf("\tbound : %d\n",bound);
	printf("-----------------------------------\n");
}





int main(){

	Analyse(FILE_EMAIL,&NODE_EMAIL);
	
	Analyse(FILE_AMAZON,&NODE_AMAZON);

	Analyse(FILE_LJ,&NODE_LJ);

	Analyse(FILE_ORKUT,&NODE_ORKUT);

//	Analyse(FILE_FRIENDSTER,&NODE_FRIENDSTER);
	
	return 0 ;

}
