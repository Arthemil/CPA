#include <stdio.h>
#include <stdlib.h>
char * FILE_DIRLINKS	= "/Vrac/CPA-PageRank/alr21--dirLinks--enwiki-20071018.txt";
char * FILE_TO_NAME     = "/Vrac/CPA-PageRank/alr21--pageNum2Name--enwiki-20071018.txt";

char * FILE_TEST = "../testGraphe_clean.txt";


typedef struct Node Node;
struct Node{
	int num;
	int nb_voisins;
	int nb_entrants;
	Node ** voisins;
};


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
			liste = realloc(liste, max_node*(sizeof(Node)));
			int i;
			for (i = tmp;i<=max_node;i++)liste[i] = NULL; 
		}
		if(v>max_node-1){
			int tmp = max_node+1;
			max_node = v;
			liste = realloc(liste, max_node*(sizeof(Node)));
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
		
		
	}
	fclose(f);
	
	//affichage de test
	/*int i;
	
	for (i = 0; i <= max_node;i++){
		if(liste[i]==NULL)continue;
		printf("noeud %d:\n",liste[i]->num);
		printf("\tnb_voisins:%d\n",liste[i]->nb_voisins);
		unsigned int j;
		printf("voisins:");
		for(j = 0;j< liste[i]->nb_voisins;j++)printf("%d ",liste[i]->voisins[j]->num);
		printf("\n");
	}*/
	
	//liberation memoire
	/*for(i = 0 ; i<= max_node; i++){
		if(liste[i]==NULL)continue;
		free(liste[i]->voisins);
	}
	free(liste);*/
	(*nb_nodes) = max_node;
	return liste;
}



double * MatVectProd(Node ** adj,int n, double * P){

	double * VectTmp = calloc(n,sizeof(double));
	int i,j;
	
	for (i = 0; i <n; i++){
		if(adj[i]==NULL)continue;
		for(j = 0;j < adj[i]->nb_voisins;j++){
			VectTmp[adj[i]->voisins[j]->num] += (P[i] / (adj[i]->nb_voisins*1.0));
			 
		}
	}
	
	return VectTmp;
}



double * pageRank( Node** adj, double alpha , int t, int n){
	double * MatVect = malloc(n * sizeof(double));
	int init;
	int nb_noeuds=0;
	for(init = 0; init<n;init++){
		if(adj[init]!=NULL){
			nb_noeuds++;
		}
	}
	double * P = malloc(n * sizeof(double));
	for(init = 0; init < n; init++){
		MatVect[init] = 1.0/nb_noeuds;
		P[init] = 1.0/nb_noeuds;
	}
	
	
	int i;
	
	for(i=0; i < t; i++){
		P = MatVectProd(adj,n,P);
		
		int j;
		double cardP = 0.0;
		for(j = 0 ; j < n; j++){
			if(adj[j]==NULL){
				continue;
			}
			if(adj[j]->nb_voisins==0){
				P[j]=0.0;
				continue;
			}
			P[j]=(P[j]*(1.0-alpha))+(alpha*(1.0/nb_noeuds));//penser au cas P[j] == 0	 
			cardP+=P[j];
		}
		//Normalize2D
		for(j = 0;j<n;j++){
			if(adj[j]==NULL)continue;
			P[j] += (1.0-cardP)/nb_noeuds;
		}
		
	}
	free(MatVect);
	
	return P;
}


int main(){
	
	int max_node=13834639; /* plus haut noeud*/
	//int max_node=9;
	Node ** adj = create_adjacency_array(FILE_DIRLINKS,&max_node);
	printf("tableau done\n");
	double alpha = 0.15;
	int t = 20;
	double * P = pageRank(adj,alpha,t,max_node);
	printf("pageRank done\n");
	

	//5 meilleurs page Rank
	int best[5]={0,1,2,3,4};
	int less[5]={-1,-1,-1,-1,-1};
	int i,j;
	for(i = 0 ; i <= max_node;i++){
		int permutb = i;
		int tmpb;
		int permutl = i;
		int tmpl;
		for(j = 0 ; j < 5 ; j++){
			if(P[permutb]>P[best[j]]){
				tmpb = best[j];
				best[j] = permutb;
				permutb = tmpb;
			}
			
			if(P[permutl]!=0){
				if(less[j]==-1 ||  P[permutl]<P[less[j]]){
					tmpl = less[j];
					less[j] = permutl;
					permutl = tmpl;
				}
			}
		}
	}
	printf("fin de recherche 5 meilleurs\n");
	
	FILE * f = fopen(FILE_TO_NAME,"r");
	int u,tmp;
	char name[1024];
	int cpt_breaker=0;
	char ignore[1024];
	
	
	for(i = 0; i<5;i++)fgets(ignore,1024,f);
	while(fscanf(f,"%d %[^\n]\n", &u, &name) != EOF){
		for(tmp = 0;tmp < 5;tmp++){
			if(u == best[tmp]){
				printf("top :%d -> %s rank: %f id : %d \n",tmp+1,name, P[u], u); //tmp+1 pour commencer le classement a 1 et pas 0
				cpt_breaker++;
				break;
			}
		}
		if(cpt_breaker==5)break;
	}
	rewind(f);
	cpt_breaker = 0;
	for(i = 0; i<5;i++)fgets(ignore,1024,f);
	while(fscanf(f,"%d %[^\n]\n", &u, &name) != EOF){
		for(tmp = 0;tmp < 5;tmp++){
			if(u == less[tmp]){
				printf("bot :%d -> %s rank: %f id :%d\n",tmp+1,name,P[u],u); //tmp+1 pour commencer le classement a 1 et pas 0
				cpt_breaker++;
				break;
			}
		
		}
		if(cpt_breaker==5)break;
	}	
	fclose(f);
	
	printf("fin\n");
	//liberation memoire
	for(i = 0 ; i<= max_node; i++){
		if(adj[i]==NULL)continue;
		free(adj[i]->voisins);
	}
	free(adj);
	free(P);
	return 0;
}

