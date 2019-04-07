#include <stdlib.h>
#include <stdio.h>

char * FILE_TEST	= "../ressource/testGraphe_clean.txt";
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

int EDGES_EMAIL 	= 16064;
int EDGES_AMAZON	= 925872;
int EDGES_LJ 		= 34681189;
int EDGES_ORKUT 	= 117185083;
int EDGES_FRIENDSTER 	= 1806067135;

typedef struct Node Node;
struct Node{
	int num;
	int nb_voisins;
	int nb_entrants;
	Node ** voisins;
};

typedef struct Cle_R Cle_R; 
struct Cle_R {
	double r;
	int node;
};

typedef struct Edge Edge; 
struct Edge {
	int u;
	int v;
};

int comp (const void * elem1, const void * elem2) {
    double f = (*(Cle_R**)elem1)->r;
    double s = (*(Cle_R**)elem2)->r;
    if(s - f > 0)return 1;
    if(s - f < 0)return -1;
    return 0;
}


Edge ** stock(char * s,int nb_edges){
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return NULL;
	}
	int u,v;
	Edge **list = malloc(nb_edges*sizeof(Edge*));
	int i = 0;
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
		Edge * e = malloc(sizeof(Edge));
		e->u = u;
		e->v = v;
		list[i] = e;
		i++;
	}
	fclose(f);
	return list;
}

//------------------------------------Tableau d'adjacence--------------------------------------------------//

Node ** create_adjacency_array(char * s,int  * nb_nodes){
	FILE * f = fopen(s,"r");
	if(f==NULL){
		printf("File ERROR\n");
		return NULL;
	}
	int max_node = *nb_nodes;
	Node ** liste = calloc(max_node,sizeof(Node*));
	int u,v;
	while(fscanf(f,"%d %d\n", &u, &v) != EOF){
	
		//si le numero du noeud est superieur au nombre de noeuds
		if(u>max_node-1){			
			int tmp = max_node+1;
			max_node = u;
			liste = realloc(liste, (1+max_node)*(sizeof(Node)));
			int i;
			for (i = tmp;i<=max_node;i++)liste[i] = NULL; 
		}
		if(v>max_node-1){
			int tmp = max_node+1;
			max_node = v;
			liste = realloc(liste, (1+max_node)*(sizeof(Node)));
			int i;
			for (i = tmp;i<=max_node;i++)liste[i] = NULL;
		}
		
		//si le noeud n'exite pas encore dans la liste		
		if(liste[u]==NULL){
			Node * newN = malloc(sizeof(Node));
			newN -> num = u;
			newN -> nb_voisins = 0;
			newN -> voisins = NULL;
			newN -> nb_entrants = 0;
			liste[u] = newN;
		}
		if(liste[v]==NULL){
			Node * newN = malloc(sizeof(Node));
			newN -> num = v;
			newN -> nb_voisins = 0;
			newN -> voisins = NULL;
			newN -> nb_entrants = 0;
			liste[v] = newN;
		}
		
		
		if(liste[u] -> voisins == NULL){//si la liste des voisins de ce noeud est null
			liste[u] -> voisins = malloc(sizeof(Node*));
			liste[u] -> voisins[0] = liste[v];
			liste[u] -> nb_voisins++;
			liste[v] -> nb_entrants++;
		}else{				
			liste[u] -> voisins = realloc(liste[u] -> voisins,((liste[u] -> nb_voisins)+1)*sizeof(Node*));
			liste[u] -> voisins[liste[u] -> nb_voisins] = liste[v];
			liste[u] -> nb_voisins++;
			liste[v] -> nb_entrants++;
		}
		
		if(liste[v] -> voisins == NULL){//si la liste des voisins de ce noeud est null
			liste[v] -> voisins = malloc(sizeof(Node*));
			liste[v] -> voisins[0] = liste[u];
			liste[v] -> nb_voisins++;
			liste[u] -> nb_entrants++;
		}else{				
			liste[v] -> voisins = realloc(liste[v] -> voisins,((liste[v] -> nb_voisins)+1)*sizeof(Node*));
			liste[v] -> voisins[liste[v] -> nb_voisins] = liste[u];
			liste[v] -> nb_voisins++;
			liste[u] -> nb_entrants++;
		}
		
		
	}
	fclose(f);
	
	//display test
/*
	int i;
	for (i = 0; i <= max_node;i++){
		if(liste[i]==NULL)continue;
		printf("noeud %d:\n",liste[i]->num);
		printf("\tnb_voisins:%d\n",liste[i]->nb_voisins);
		unsigned int j;
		printf("voisins:");
		for(j = 0;j< liste[i]->nb_voisins;j++)printf("%d ",liste[i]->voisins[j]->num);
		printf("\n");
	}
*/	
	//release memory
	/*for(i = 0 ; i<= max_node; i++){
		if(liste[i]==NULL)continue;
		free(liste[i]->voisins);
	}
	free(liste);*/
	(*nb_nodes) = max_node;
	return liste;
}


//---------------------------------------------------------------------K-CORE DECOMPOSITION WITH MKSCORE------------------------------------------------//
void mkscore(char* s, int  nb_nodes,int EDGES,int t){
	
	int max_node_value = nb_nodes;
	Node ** adj = create_adjacency_array(s, &max_node_value);
	int i = 0;
	printf("end adj\n");
	Cle_R **R = malloc(max_node_value*sizeof(Cle_R*));
	for(i = 0 ;i <= max_node_value; i++){
		Cle_R *cle = malloc(sizeof(Cle_R));
		cle->node = i;
		cle->r = 0.0;
		R[i] = cle;
	}
	printf("end cle\n");
	//-----MKSCORE---------
	int round;
	Edge ** E_list = stock(s,EDGES);
	for(round = 0 ; round < t; round++){
		printf("round = %d\n",round);
		for(i = 0;i < EDGES; i++){
			Edge * e = E_list[i];
			if(R[e->u]->r <= R[e->v]->r){
				(R[e->u]->r)++;
			}else{
				(R[e->v]->r)++;
			}
		}
	}
	printf("end round\n");
	
	Cle_R **R2 = malloc(nb_nodes*sizeof(Cle_R*));
	for(i = 0 ;i < nb_nodes; i++){
		Cle_R *cle = malloc(sizeof(Cle_R));
		cle->node = 0;
		cle->r = 0.0;
		R2[i] = cle;
	}
	
	int i_r2=0;
	for(i=0;i<=max_node_value;i++){
		if(adj[i]==NULL)continue;
		R2[i_r2]->r = R[i]->r/t*1.0;
		R2[i_r2]->node = R[i]->node;
		i_r2++;
	}
	
	
	qsort(R2,nb_nodes, sizeof(*R2), comp);
	
	int i_n = 0;
	int * N = malloc(nb_nodes*sizeof(int));
	
	for(i=0;i<nb_nodes;i++){
		N[i_n]=R2[i]->node;
		i_n++;
	}
	
	
	printf("end R to N\n");
	int i_densest 			= 0;
	double densest 			= 0;
	int nb_nodes_subgraph 		= 0;
	int nb_edges_subgraph		= 0;
	double E_density_subgraph 	= 0;
	
	int *Exist = malloc((max_node_value)*sizeof(int));
	for(i=0;i<=max_node_value;i++)Exist[i]=0;
	printf("begin k-core decomp\n");
	for(i=0; i < nb_nodes ; i++){
		Exist[N[i]]=1;
		nb_nodes_subgraph++;
		
		if(i==0)continue;
		
		int j;
		for(j = 0; j < adj[N[i]]->nb_voisins; j++){
		
			if(!Exist[adj[N[i]]->voisins[j]->num])continue;
			nb_edges_subgraph++;
		}
		
		double densest_tmp =(1.0*nb_edges_subgraph /(nb_nodes_subgraph));
		
		if(densest_tmp > densest){
			densest = densest_tmp;
			i_densest = nb_nodes_subgraph;
			E_density_subgraph = (nb_edges_subgraph*2.0)/(nb_nodes_subgraph*(nb_nodes_subgraph-1));
		}	
	}
	
	printf("file : %s\n",s);
	printf("nb_nodes: %d\t nb_edges:%d\n",nb_nodes_subgraph,nb_edges_subgraph);
	printf("densest core:\n");	
	printf("\taverage degree density:\t%lf\n",densest);
	printf("\tedge density:\t%lf\n",E_density_subgraph);
	printf("\tsize:\t%d\n",i_densest);
	printf("\thighest density score:\t%lf\n",R2[0]->r);
	printf("---------------------------\n");
	

}

int main(){

	mkscore(FILE_EMAIL,NODE_EMAIL,EDGES_EMAIL,10);
//	mkscore(FILE_EMAIL,NODE_EMAIL,EDGES_EMAIL,100);
//	mkscore(FILE_EMAIL,NODE_EMAIL,EDGES_EMAIL,1000);
	printf("-------------------------------------------\n");
	mkscore(FILE_AMAZON,NODE_AMAZON,EDGES_AMAZON,10);
//	mkscore(FILE_AMAZON,NODE_AMAZON,EDGES_AMAZON,100);
//	mkscore(FILE_AMAZON,NODE_AMAZON,EDGES_AMAZON,1000);

	printf("-------------------------------------------\n");
	mkscore(FILE_LJ,NODE_LJ,EDGES_LJ,10);
//	mkscore(FILE_LJ,NODE_LJ,EDGES_LJ,100);
//	mkscore(FILE_LJ,NODE_LJ,EDGES_LJ,1000);
	printf("-------------------------------------------\n");
	mkscore(FILE_ORKUT,NODE_ORKUT,EDGES_ORKUT,10);
//	mkscore(FILE_ORKUT,NODE_ORKUT,EDGES_ORKUT,100);
//	mkscore(FILE_ORKUT,NODE_ORKUT,EDGES_ORKUT,1000);
//	mkscore(FILE_FRIENDSTER,NODE_FRIENDSTER);
	
	return 0;
}

