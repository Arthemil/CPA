#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

char * FILE_TEST	= "../ressource/testGraphe_clean.txt";
char * FILE_EMAIL	= "/Vrac/TME_CPA_19-02-20/email-Eu-core-clean.txt";
char * FILE_AMAZON	= "/Vrac/TME_CPA_19-02-20/com-amazon.ungraph-clean.txt";
char * FILE_LJ		= "/Vrac/TME_CPA_19-02-20/com-lj.ungraph-clean.txt";
char * FILE_ORKUT	= "/Vrac/TME_CPA_19-02-20/com-orkut.ungraph-clean.txt";
char * FILE_FRIENDSTER	= "/Vrac/TME_CPA_19-02-20/com-friendster.ungraph.txt";

int NB_NODES_TEST	= 11;
int NB_NODES_EMAIL	= 986;
int NB_NODES_AMAZON	= 334863;
int NB_NODES_LJ		= 3997962;
int NB_NODES_ORKUT	= 3072441;
int NB_NODES_FRIENDSTER	= 65608366;


typedef struct Node Node;
struct Node{
	unsigned int num;
	unsigned int nb_neighbors;
	int marked;
	int degree;
	int nb_triplets;
	double local_cluster;
	long long int nb_local_triangles;
	Node ** neighbors;
};

int comp (const void * elem1, const void * elem2) {
    int f = (*(Node**)elem1)->num;
    int s = (*(Node**)elem2)->num;
    return f - s;
}


void create_adjacency_array(char * s, int * max_node_value, Node *** adj){
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int nb_nodes = (*max_node_value);
	Node ** list = calloc(nb_nodes,sizeof(Node*));
	int u,v;
	while(fscanf(f,"%d\t%d\n", &u, &v) != EOF){
		
		//increasing size of array to the max index value
		if(u>nb_nodes-1){			
			int tmp = nb_nodes+1;
			nb_nodes = u;
			list = realloc(list, (1+nb_nodes)*(sizeof(Node*)));
			int i;
			for (i = tmp;i<=nb_nodes;i++)list[i] = NULL; 
		}
		if(v>nb_nodes-1){
			int tmp = nb_nodes+1;
			nb_nodes = v;
			list = realloc(list, (1+nb_nodes)*(sizeof(Node*)));
			int i;
			for (i = tmp;i<=nb_nodes;i++)list[i] = NULL;
		}
		
		//if Node not yet in the array		
		if(list[u]==NULL){
			Node * newN 		= malloc(sizeof(Node));
			newN -> num 		= u;
			newN -> nb_neighbors 	= 0;
			newN -> neighbors 	= NULL;
			newN->marked 		= 0;
			newN->degree 		= 0;
			newN->nb_local_triangles= 0;
			newN->nb_triplets	= 0;
			newN->local_cluster	= 0;
			list[u] 		= newN;
		}
		if(list[v]==NULL){
			Node * newN 		= malloc(sizeof(Node));
			newN -> num 		= v;
			newN -> nb_neighbors 	= 0;
			newN -> neighbors 	= NULL;
			newN->marked 		= 0;
			newN->degree 		= 0;
			newN->nb_local_triangles= 0;
			newN->nb_triplets	= 0;
			newN->local_cluster	= 0;
			list[v] 		= newN;
		}
		list[u]->degree++;
		list[v]->degree++;
	}
	
	rewind(f);
	
	//DAG application
	while(fscanf(f,"%d\t%d\n", &u, &v) != EOF){
		if(list[v]->degree > list[u]->degree || ((list[v]->degree == list[u]->degree) && (u < v))){
		
			if(list[u] -> neighbors == NULL){//if array of neighbors = null
				list[u] -> neighbors = malloc(sizeof(Node*));
				list[u] -> neighbors[0] = list[v];
				list[u] -> nb_neighbors++;
			}else{

				list[u] -> neighbors = realloc(list[u] -> neighbors,((list[u] -> nb_neighbors)+1)*sizeof(Node*));
				list[u] -> neighbors[list[u] -> nb_neighbors] = list[v];
				list[u] -> nb_neighbors++;
			}
		}
		
		if(list[u]->degree > list[v]->degree || ((list[u]->degree == list[v]->degree) && (v < u))){
				
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
		
	}
	fclose(f);
	int i;
	
	
	
	for (i = 0; i <= nb_nodes;i++){
		if(list[i]==NULL)continue;
		if(list[i]->degree > 1) list[i]->nb_triplets = (list[i]->degree * (list[i]->degree - 1)) / 2; //calculating triplets
		
		if(list[i]->neighbors==NULL)continue;
		qsort (list[i]->neighbors, list[i]->nb_neighbors, sizeof(*list[i]->neighbors), comp); // sort the neighbors by their values
	}

	//display test
/*
	for (i = 0; i <= nb_nodes;i++){
		if(list[i]==NULL)continue;
		printf("noeud %d:\n",list[i]->num);
		printf("\tnb_neighbors:%d\n",list[i]->nb_neighbors);
		unsigned int j;
		printf("neighbors:");
		for(j = 0;j< list[i]->nb_neighbors;j++)printf("%d ",list[i]->neighbors[j]->num);
		printf("\n");
	}
*/
	
	//release memory
	/*for(i = 0 ; i<= nb_nodes; i++){
		if(list[i]==NULL)continue;
		free(list[i]->neighbors);
	}
	free(list);*/
	(*max_node_value) = nb_nodes;
	(*adj) = list;
}

//-------------------------------------------------------------------------------------------------------------------------------------------------------------------//



void Analyse(char * s,int * nb_nodes){
	Node ** G;
	long long int nb_triangles = 0;
	int max_node_value =0;
	create_adjacency_array(s,&max_node_value,&G);
	FILE * f = fopen(s,"r");
	int u,v;
	
	//counting triangles
	while(fscanf(f,"%d\t%d\n", &u, &v) != EOF){
		Node ** neighbors_u = G[u]->neighbors;
		Node ** neighbors_v = G[v]->neighbors;

		int bound_u = G[u]->nb_neighbors;
		int bound_v = G[v]->nb_neighbors;
		
		int i=0,j=0;
		
		if(bound_u == 0 || bound_v == 0)continue;
		
		while(i < bound_u  && j < bound_v ){
			if(neighbors_u[i]->num == neighbors_v[j]->num){
				nb_triangles++;
				G[u]->nb_local_triangles++;
				G[v]->nb_local_triangles++;
				G[neighbors_u[i]->num]->nb_local_triangles++;
				i++;j++;
			}
			
			else if(neighbors_u[i]->num > neighbors_v[j]->num){
				while(j < bound_v && neighbors_u[i]->num > neighbors_v[j]->num ){
					j++;
				}
			}
			
			else if(neighbors_u[i]->num < neighbors_v[j]->num){
				while( i < bound_u && neighbors_u[i]->num < neighbors_v[j]->num ){
					i++;
				}
			}
		}
	}
	fclose(f);
	
	int i;
	long long int s_triplets=0;
	double s_local_cluster=0;
	
	for (i = 0; i <= max_node_value;i++){
		if(G[i]==NULL)continue;
		if(G[i]->nb_triplets!=0 && G[i]->nb_local_triangles!=0)
			G[i]->local_cluster = (double)(G[i]->nb_local_triangles)/G[i]->nb_triplets;
			
		s_triplets += G[i]->nb_triplets;
		s_local_cluster+= G[i]->local_cluster;
			
		if(G[i]->neighbors==NULL)continue;
		free(G[i]->neighbors);//release memory
		
	}
	free(G);
	
	double transitivity = (3.0 * nb_triangles)/(double)s_triplets ;
	double average_cluster = s_local_cluster/(*nb_nodes);
	
	printf("file: %s\n",s);
	printf("\tnodes \t\t=%d\n", (*nb_nodes));
	printf("\ttriangles \t=%lld\n",nb_triangles);
	printf("\ttriplets  \t=%lld\n",s_triplets);
	printf("\ttransitivity\t=%lf\n",transitivity);
	printf("\taverage clustering coefficient\t=%lf\n",average_cluster);
}


int main(){
	struct timeval tv1,tv2;
   	long long time;
	
	//create_adjacency_array(FILE_TEST);
   	//FILE EMAIL----------------------------//
   	
   	printf("running for email\n");
   	gettimeofday(&tv1,NULL);
	Analyse(FILE_EMAIL,&NB_NODES_EMAIL);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("-----------------------------------------------\n");
   	
	//FILE AMAZON--------------------------//
	
	printf("running for amazon\n");
	gettimeofday(&tv1,NULL);
	Analyse(FILE_AMAZON,&NB_NODES_AMAZON);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("-----------------------------------------------\n");
	
	//FILE LJ------------------------------//
	
	printf("running for lj\n");
	gettimeofday(&tv1,NULL);
	Analyse(FILE_LJ,&NB_NODES_LJ);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("-----------------------------------------------\n");
	
	//FILE ORKUT---------------------------//
	printf("running for orkut\n");
	gettimeofday(&tv1,NULL);
	Analyse(FILE_ORKUT,&NB_NODES_ORKUT);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("-----------------------------------------------\n");
   	
   	//FILE FRIENDSTER------------------------//
/*
   	printf("running for friendster\n");
   	gettimeofday(&tv1,NULL);
	Analyse(FILE_FRIENDSTER,,&NB_NODES_FRIENDSTER);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("-----------------------------------------------\n");


*/	
	return 0 ;

}
