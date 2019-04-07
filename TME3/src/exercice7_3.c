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


typedef struct Node Node;
struct Node{
	unsigned int num;
	unsigned int nb_neighbors;
	int marked;
	Node ** neighbors;
};


void create_adjacency_array(char * s){
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int max_Node_value =0;
	Node ** list = calloc(max_Node_value,sizeof(Node*));
	int u,v;
	while(fscanf(f,"%d\t%d\n", &u, &v) != EOF){
	
		//increasing size of array to the max index value
		if(u>max_Node_value-1){			
			int tmp = max_Node_value+1;
			max_Node_value = u;
			list = realloc(list, (1+max_Node_value)*(sizeof(Node*)));
			int i;
			for (i = tmp;i<=max_Node_value;i++)list[i] = NULL; 
		}
		if(v>max_Node_value-1){
			int tmp = max_Node_value+1;
			max_Node_value = v;
			list = realloc(list, (1+max_Node_value)*(sizeof(Node*)));
			int i;
			for (i = tmp;i<=max_Node_value;i++)list[i] = NULL;
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
	int i;	
	//display test
/*
	for (i = 0; i <= max_Node_value;i++){
		if(list[i]==NULL)continue;
		printf("vertice %d:\n",list[i]->num);
		printf("\tnb_neighbors:%d\n",list[i]->nb_neighbors);
		
		unsigned int j;
		printf("neighbors:");
		for(j = 0;j< list[i]->nb_neighbors;j++)printf("%d ",list[i]->neighbors[j]->num);
		printf("\n\n");
	}
*/	
	//free memory
	for(i = 0 ; i<= max_Node_value; i++){
		if(list[i]==NULL)continue;
		free(list[i]->neighbors);
	}
	free(list);
}


int main(){
	struct timeval tv1,tv2;
   	long long time;
	
	//create_adjacency_array(FILE_TEST);
   	//FILE EMAIL----------------------------//
   	
   	printf("running for email\n");
   	gettimeofday(&tv1,NULL);
	create_adjacency_array(FILE_EMAIL);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
   	printf("------------------------------\n");
   	
	//FILE AMAZON--------------------------//
	
	printf("running for amazon\n");
	gettimeofday(&tv1,NULL);
	create_adjacency_array(FILE_AMAZON);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("------------------------------\n");
	
	//FILE LJ------------------------------//
	
	printf("running for lj\n");
	gettimeofday(&tv1,NULL);
	create_adjacency_array(FILE_LJ);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
	
	//FILE ORKUT---------------------------//
	printf("running for orkut\n");
	gettimeofday(&tv1,NULL);
	create_adjacency_array(FILE_ORKUT);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
   	
   	//FILE FRIENDSTER------------------------//
/*
   	printf("running for friendster\n");
   	gettimeofday(&tv1,NULL);
	create_adjacency_array(FILE_FRIENDSTER);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");


*/
	return 0;
}




