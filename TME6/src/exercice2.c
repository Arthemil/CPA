#include <stdio.h>
#include <stdlib.h>
#include "exercice2.h"

char * FILE_NET = "../ressource/scholar/net.txt";
char * FILE_ID  = "../ressource/scholar/ID.txt";

char * FILE_HIST= "../ressource/net_core_degree.txt";
void k_core_decomposition2(char* s, int  nb_nodes){
	if(s==NULL)return;
	tas * T=create_heap(s, nb_nodes);
	
	int max_node_value=nb_nodes;
	Node ** adj = create_adjacency_array(s,&max_node_value);
	
	int nb_edges = 0;
	int i = T->size -1;
	int c = 0;
	
	int * N = malloc(nb_nodes*sizeof(int));
	int nb_nodes_graph = 0;
	
	FILE * f = fopen(FILE_HIST,"w");
	while(T->size!=0){
		cle* v = T->a[0];
		
		N[i] = v->node; 
		int j;
		if(c<(v->nb_voisins)){
			c = (v->nb_voisins);
		}
		SupprMin_Tableau(T);
		nb_nodes_graph++;
		
		
		//---------------POUR EXERCICE 2 ----------------------//
		
		fprintf(f,"%d\t%d\n",v->degree,c);
		//-----------------------------------------------------//
		
		for(j=0;j<(v->degree); j++){
			
			if(v->voisins[j]==NULL)continue;
			
			v->voisins[j]->nb_voisins--;
			Remonter(T,v->voisins[j]->emplacement);
			int k;
			for(k=0; k<(v->voisins[j]->degree); k++){	
				if(v->voisins[j]->voisins[k] == v){
					v->voisins[j]->voisins[k]=NULL;
					nb_edges++;
					break;
				} 
			}
		}
		i = i - 1;
	}
	
	fclose(f);
	int i_densest 			= 0;
	double densest 			= 0;
	int nb_node_subgraph 		= 0;
	int nb_edges_subgraph		= 0;
	double E_density_subgraph 	= 0;

	int *Exist = calloc(max_node_value,sizeof(int));

	for(i=0; i < nb_nodes ; i++){
		Exist[N[i]]=1;
		nb_node_subgraph++;
		if(i==0)continue;
		int j;
		for(j = 0; j < adj[N[i]]->nb_voisins;j++){
			if(!Exist[adj[N[i]]->voisins[j]->num])continue;
			nb_edges_subgraph++;
		}
		
		double densest_tmp =((double)nb_edges_subgraph /(nb_node_subgraph));
		
		if(densest_tmp>densest){
			densest = densest_tmp;
			i_densest= nb_node_subgraph;
			E_density_subgraph = ((double)(nb_edges_subgraph*2.0))/(nb_node_subgraph*(nb_node_subgraph-1));
		}	
	}
	
	printf("file : %s\n",s);
	printf("\tK-core = %d\n", c);
	printf("nb_nodes: %d\t nb_edges:%d\n",nb_nodes,nb_edges);
	printf("densest core:\n");	
	printf("\taverage degree density:\t%lf\n",densest);
	printf("\tedge density:\t%lf\n",E_density_subgraph);
	printf("\tsize:\t%d\n",i_densest);
	
	printf("---------------------\n");
}

long long int count(char * s){
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return 0;
	}
	int max_node_value = 1;
	
	long long int nb_nodes = 0;
	
	int * nodes = calloc(max_node_value,sizeof(int));
	int u,v;
	while(fscanf(f,"%d\t%d" ,&u,&v) != EOF){
		//increasing the size of array to the max index value
		if(u>max_node_value){			
			int tmp = max_node_value+1;
			max_node_value = u;
			nodes = realloc(nodes, (1+max_node_value)*sizeof(int));
			int i;
			for (i = tmp;i<=max_node_value;i++)nodes[i] = 0; 
		}
		if(v>max_node_value){
			int tmp = max_node_value+1;
			max_node_value = v;
			nodes = realloc(nodes, (1+max_node_value)*sizeof(int));
			int i;
			for (i = tmp;i<=max_node_value;i++)nodes[i] = 0;
		}
		
		if(!nodes[u]){//if the node doesn't exist yet
			nodes[u]=1;
			nb_nodes++;
		}
		if(!nodes[v]){
			nodes[v]=1;
			nb_nodes++;
		}
		
	}
	free(nodes);
	
	fclose(f);
	return nb_nodes;
}


int main(){
	int nb_nodes = count(FILE_NET);
	
	k_core_decomposition2(FILE_NET,nb_nodes);
	return 0;
	
}
