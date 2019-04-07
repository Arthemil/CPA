#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
char * FILE_TEST	= "../ressource/testGraphe_clean.txt";
char * FILE_YOUTUBE 	= "../com_youtube_ungraph/data.txt";
int NODE_TEST = 11;
int NODE_YOUTUBE = 1134890;

typedef struct Node Node;
struct Node{
	int num;
	int label;
	int nb_neighbors;
	Node ** neighbors;
};

Node ** create_adjacency_array(char * s,int * nb_nodes){
	FILE * f = fopen(s,"r");
	if(f==NULL){
		printf("File ERROR\n");
		return NULL;
	}
	int max_node_value = 0;
	Node ** list = calloc(max_node_value,sizeof(Node*));
	int label = 0;
	int u,v;
	char ignore[1024];
	int i;
	
	for(i = 0; i<4;i++)fgets(ignore,1024,f);
	while(fscanf(f,"%d\t%d\n", &u, &v) != EOF){
		//increasing size of array to the max index value
		if(u>max_node_value-1){			
			int tmp = max_node_value+1;
			max_node_value = u;
			list = realloc(list, (1+max_node_value)*(sizeof(Node)));
			int i;
			for (i = tmp;i<=max_node_value;i++)list[i] = NULL; 
		}
		if(v>max_node_value-1){
			int tmp = max_node_value+1;
			max_node_value = v;
			list = realloc(list, (1+max_node_value)*(sizeof(Node)));
			int i;
			for (i = tmp;i<=max_node_value;i++)list[i] = NULL;
		}
		//if Node not yet in the array			
		if(list[u]==NULL){
			Node * newN = malloc(sizeof(Node));
			newN -> num = u;
			newN -> label = u+1;
			newN -> nb_neighbors = 0;
			newN -> neighbors = NULL;
			list[u] = newN;
			label++;
		}
		if(list[v]==NULL){
			Node * newN = malloc(sizeof(Node));
			newN -> num = v;
			newN -> label = v+1;
			newN -> nb_neighbors = 0;
			newN -> neighbors = NULL;
			list[v] = newN;
			label++;
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
	for (i = 0; i <= max_node_value;i++){
		if(list[i]==NULL)continue;
		printf("node %d:\n",list[i]->num);
		printf("\tlabel :%d\n\tnb_neighbors:%d\n",list[i]->label,list[i]->nb_neighbors);
		unsigned int j;
		printf("neighbors:");
		for(j = 0;j< list[i]->nb_neighbors;j++)printf("%d ",list[i]->neighbors[j]->num);
		printf("\n");
	}
*/
	
	(*nb_nodes) = max_node_value;
	return list;
}



int labelPropagation(Node ***adja,int * max_n){
	int max_node_value = *max_n;
	Node ** adj =*adja;
	//max_node_value updated
	int i;
	time_t t;
	int test = 1;
	int cond = 0;
	while(test){
	
		//shuffle
		srand((unsigned) time(&t));
		for(i = 0; i < max_node_value;i++){
			int j = rand()%(max_node_value-i) +i+1;
			Node * tmp = adj[i];
			adj[i]=adj[j];
			adj[j]=tmp;
		} 

 		int * num_label=malloc((2+max_node_value)*sizeof(int));
		int * frequency=malloc((1+max_node_value)*sizeof(int));
 		for(i = 0;i <= max_node_value;i++){
			if(adj[i]==NULL)continue;
			
			int j;
			int nb_max_freq = 0;
			int new_label = adj[i]->label;
			for(j = 0; j< adj[i]->nb_neighbors;j++){
				
				frequency[adj[i]->neighbors[j]->label]++;
				num_label[adj[i]->neighbors[j]->num]=adj[i]->neighbors[j]->label;
				
				if(frequency[adj[i]->neighbors[j]->label]>nb_max_freq){
					nb_max_freq=frequency[adj[i]->neighbors[j]->label];
					new_label=num_label[adj[i]->neighbors[j]->num];
				}
			}
			
			if(adj[i]->label != new_label){
				cond++;
				adj[i]->label = new_label;
			}
			for(j = 0; j< adj[i]->nb_neighbors;j++){
				
				frequency[adj[i]->neighbors[j]->label]=0;
				num_label[adj[i]->neighbors[j]->num]=0;
			}
			
			
 		}	
 		free(num_label);
		free(frequency);
 		if(cond==0)test=0;//if the labels has not changed , stop the spread
 		cond = 0; // reinit out-conditon
 		
 		
 		
 		//display test
/* 		
 		printf("----------------------------------------------------------------\n");
 		for (i = 0; i <= max_node_value;i++){
			if(adj[i]==NULL)continue;
			printf("node %d:\n",adj[i]->num);
			printf("\tlabel :%d\n\tnb_neighbors:%d\n",adj[i]->label,adj[i]->nb_neighbors);
			unsigned int j;
			printf("neighbors:");
			for(j = 0;j< adj[i]->nb_neighbors;j++)printf("%d ",adj[i]->neighbors[j]->num);
			printf("\n");
		}
*/
	}
	//printf("END SPREAD");	

	int nb_communities = 0;
	int nb_labels=max_node_value+1;
	int * labels = malloc(nb_labels*sizeof(int));
	for(i = 0; i <nb_labels;i++)labels[i]=0;
	
	for(i = 0 ; i<= nb_labels; i++){
		if(adj[i]==NULL)continue;
		labels[adj[i]->label]++;
	}
	
	
	//-------------------write in files-----------------------//
	
	FILE *f_size1 = fopen("../ressource/Youtube_size_community0_250000.txt","w");
	FILE *f_size2 = fopen("../ressource/Youtube_size_community250000_500000.txt","w");
	FILE *f_size3 = fopen("../ressource/Youtube_size_community500000_750000.txt","w");
	FILE *f_size4 = fopen("../ressource/Youtube_size_community750000_1000000.txt","w");
	FILE *f_size5 = fopen("../ressource/Youtube_size_community1000000_end.txt","w");
	
	
	for(i = 0 ; i <=nb_labels; i++){
		
		if(labels[i]!=0){
			nb_communities++;
			
			if(i<250000){
				fprintf(f_size1,"%d\t%d\n",i,labels[i]);
			}else if(i<500000){
				fprintf(f_size2,"%d\t%d\n",i,labels[i]);
			}else if(i<750000){
				fprintf(f_size3,"%d\t%d\n",i,labels[i]);
			}else if(i<1000000){
				fprintf(f_size4,"%d\t%d\n",i,labels[i]);
			}else{
				fprintf(f_size5,"%d\t%d\n",i,labels[i]);
			}
		}
	}
	
	fclose(f_size1);
	fclose(f_size2);
	fclose(f_size3);
	fclose(f_size4);
	fclose(f_size5);
	
	
	
	
	
	return nb_communities;
}

void reinit(Node ***adj,int * max_node_value){
	int i;
	for(i=0;i<=*max_node_value;i++){
		if((*adj)[i]==NULL)continue;
		(*adj)[i]->label=(*adj)[i]->num+1;
	}
}
int main(){
	int max_node_value = NODE_YOUTUBE;
	Node ** adj =create_adjacency_array(FILE_YOUTUBE,&max_node_value);
	int i;
	int nb_iter = 100;
	//FILE *f_100run = fopen("../ressource/Youtube_communities_1000.txt","a");
	for(i=1;i<=nb_iter;i++){
		int nb_com = labelPropagation(&adj,&max_node_value);
	//	fprintf(f_100run,"%d\t%d\n",i,nb_com);
		reinit(&adj,&max_node_value);
		printf("iteration :%d nb_com= %d\n",i,nb_com);
	}
	//fclose(f_100run);
	return 0;
}
