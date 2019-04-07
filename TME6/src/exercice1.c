#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "exercice1.h"
#include "cle.h"

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

//------------------------------------Tableau d'adjacence--------------------------------------------------//

Node ** create_adjacency_array(char * s,int  * nb_nodes){
	int max_node = *nb_nodes;
	Node ** liste = calloc(max_node,sizeof(Node*));
	FILE * f = fopen(s,"r");
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
//-------------------------------------------------FONCTION POUR LE TAS -----------------------------------//
cle* parse_cle(int node, int degree) {
  cle* res = (cle*)malloc(sizeof(cle));
  res->node = node;
  res->degree = degree;
  res->core = -1;
  res->voisins = NULL;
  res->nb_voisins = 0;
  res->emplacement = 0;
 // res->core_value = 0;
  return res;
}

int eg(cle* a, cle* b) { 
  return (a->nb_voisins == b->nb_voisins);

}

int inf(cle* a, cle* b) {
  return (a->nb_voisins) < (b->nb_voisins);
}


double lg (double x, double base){
   return log (x) / log (base);
}

tas * ConsIter_Tableau(cle **liste,int nb_nodes){
    tas * T =  malloc(sizeof(tas));
    T->size=nb_nodes;
    T->a = malloc(sizeof(cle*)*nb_nodes);
    int i;
    
    for(i = 0 ; i<nb_nodes;i++){
    	T->a[i] = liste[i];
    }
    
    int nbfeuilles = pow(2,(int)(lg(T->size,2))); 
    int nbfeuillesoccupees = T->size - nbfeuilles + 1;
    i = T->size - 1 - nbfeuillesoccupees;
    int maxi = T->size - 1;
    
    while(i != -1){
        if(2*i + 1 > maxi){     //passer le dernier etage
            i -= 1;
            continue;
            
        
        }else if(2*i+2 > maxi){     //le noeud n'a qu'un fils (a gauche)
            	if(inf(T->a[i*2 + 1],T->a[i])){
            		
                	cle * tmpC = T->a[i];
                	T->a[i] = T->a[i*2 + 1];
                	T->a[i*2+1] = tmpC;
                	
                	int tmpE = T->a[i]->emplacement	;
                	T->a[i]->emplacement=T->a[i*2+1]->emplacement;
                	T->a[i*2+1]->emplacement=tmpE;
                }
            
        }else{                 								//le noeud a deux fils
            int pere = i ;
            int newI;
            while(pere <= maxi){
                if(pere*2 + 1> maxi){ //on est sur une feuille
                    break;
                    
                }else if(pere*2 + 2 >maxi){ //on est sur un noeud qui n'a qu'un fils gauche
                    if(inf(T->a[pere*2 + 1],T->a[pere])){
                        cle * tmp = T->a[pere];
                    	T->a[pere]=T->a[pere*2 + 1];
                    	T->a[pere*2 + 1]=tmp;
                    	
                    	int tmpE = T->a[pere]->emplacement;
                	T->a[pere]->emplacement=T->a[pere*2+1]->emplacement;
                	T->a[pere*2+1]->emplacement=tmpE;
                    }
                    break;
                    
                }else{
                    if(inf(T->a[pere*2 +1],T->a[2*pere+2])){
                        newI=2*pere+1;
                    }else{
                        newI=2*pere + 2;
                    
                    }if(inf(T->a[newI],T->a[pere])){
                    	cle * tmp = T->a[pere];
                    	T->a[pere]=T->a[newI];
                    	T->a[newI]=tmp;
                    	
                    	int tmpE = T->a[pere]->emplacement;
                	T->a[pere]->emplacement=T->a[newI]->emplacement;
                	T->a[newI]->emplacement=tmpE;
                    	
                        pere=newI;
                    }else{
                        break;
                    }
        	}
            }
        	
        }
        i -= 1;
    }
    return T;
}

tas * Remonter(tas * T, int indice){
	
	int i = indice;
	
	while(1){
		int pere=(i-1)/2;
		if(pere<0)break;
		
		if(inf(T->a[i],T->a[pere])){
			cle * tmp = T->a[pere];
                    	T->a[pere]=T->a[i];
                    	T->a[i]=tmp;

                    	int tmpE = T->a[pere]->emplacement;
                	T->a[pere]->emplacement=T->a[i]->emplacement;
                	T->a[i]->emplacement=tmpE;
                	i = pere;
                }
                else{
                	break;
                }
	}
	return T;
}

tas * SupprMin_Tableau(tas * T){ //O(log(n))
    if(T->size==0){                                      
        return T;
    }                                 
    T->a[0] = T->a[T->size - 1] ;   //remplacement de la cle min par la derniere cle ajoutee
    T->a[0]->emplacement = 0;
    T->size--;       //suppression de la derniere feuille pleine
    if(T->size==0){                                      
        return NULL	;
    }
    
    int i = 0;   
    int newI;                                        
    while(1){
        if((2*i+1)>T->size-1){
            break;
        }
        if(2*i + 2 == T->size){
            newI = 2*i + 1;  //derniere case du tableau                        
        }else{
            if(inf(T->a[2*i+1],T->a[2*i+2])){ 
                newI = 2*i+1;    //recuperation de l'indice du fils gauche
            }else{
                newI = 2*i+2;   //recuperation de l'indice du fils droit
            }
        }
        if(inf(T->a[newI],T->a[i])){                          
            cle * tmp = T->a[i];
            T->a[i]=T->a[newI];
            T->a[newI]=tmp; 
            
            int tmpE = T->a[i]->emplacement;
            T->a[i]->emplacement=T->a[newI]->emplacement;
            T->a[newI]->emplacement=tmpE;
            
            
            i = newI;                               
        }else{
            break;   //le tableau est trie, plus besoin d'iterer    
        }
    }                         
    return T;
}


tas* create_heap(char* s, int  nb_nodes){
	FILE * f = fopen(s,"r");
	if(f==NULL){
		printf("File ERROR\n");
		return NULL;
	}
	int max_node = -1;
	cle** liste = malloc(nb_nodes*sizeof( cle*));
	int * ajoute = calloc(nb_nodes,sizeof(int));
	int * emplacement=calloc(nb_nodes,sizeof(int));
	int u,v;
	int nb_ajouts = 0;
	while(fscanf(f,"%d %d\n", &u, &v) != EOF){
		if(u > max_node-1){
			int tmp = max_node +1;
			max_node=u;
			int i;
			ajoute = realloc(ajoute, (1+max_node)*(sizeof(int)));
			for (i = tmp;i<=max_node;i++)ajoute[i] = -1;
			emplacement = realloc(emplacement, (1+max_node)*(sizeof(int)));
			for (i = tmp;i<=max_node;i++)emplacement[i] = -1;
		}
		if(v > max_node-1){
			int tmp = max_node +1;
			max_node = v;
			int i;
			ajoute = realloc(ajoute, (1+max_node)*(sizeof(int)));
			for (i = tmp;i<=max_node;i++)ajoute[i] = -1;
			emplacement = realloc(emplacement, (1+max_node)*(sizeof(int)));
			for (i = tmp;i<=max_node;i++)emplacement[i] = -1;
		}
		//ajout des elements dans le tas, sans les placer
		if(ajoute[u]==-1){
			liste[nb_ajouts]=parse_cle(u,1);
			liste[nb_ajouts]->voisins=NULL;
			
			ajoute[u]=1; //u a ete ajoute
			emplacement[u]=nb_ajouts;
			liste[nb_ajouts]->emplacement = nb_ajouts;					//VOUS AVEZ VRAIMENT LE COURAGE DE VOIR CE CODE ?
			nb_ajouts++;									// franchement bravo...
													//
		}
		if(ajoute[v]==-1){
			liste[nb_ajouts]=parse_cle(v,1);
			ajoute[v]=1; // v a ete ajoute
			liste[nb_ajouts]->voisins=NULL;
			emplacement[v]=nb_ajouts;
			liste[nb_ajouts]->emplacement = nb_ajouts;
			nb_ajouts++;
			
		}
		if(liste[emplacement[u]]->voisins==NULL){
			liste[emplacement[u]]->voisins=calloc(1,sizeof(cle*));
			liste[emplacement[u]]->voisins[0]=liste[emplacement[v]];
			liste[emplacement[u]]->nb_voisins++;
			
		}else{
			liste[emplacement[u]]->voisins=realloc(liste[emplacement[u]]->voisins,(liste[emplacement[u]]->degree+1)*sizeof(cle*));
			liste[emplacement[u]]->voisins[liste[emplacement[u]]->degree]=liste[emplacement[v]];
			liste[emplacement[u]]->degree++;
			liste[emplacement[u]]->nb_voisins++;
			
		}
		if(liste[emplacement[v]]->voisins==NULL){
			liste[emplacement[v]]->voisins=calloc(1,sizeof(cle*));
			liste[emplacement[v]]->voisins[0]=liste[emplacement[u]];
			liste[emplacement[v]]->nb_voisins++;
		}else{
			
			liste[emplacement[v]]->voisins=realloc(liste[emplacement[v]]->voisins,(liste[emplacement[v]]->degree+1)*sizeof(cle*));
			liste[emplacement[v]]->voisins[liste[emplacement[v]]->degree]=liste[emplacement[u]];
			liste[emplacement[v]]->degree++;
			liste[emplacement[v]]->nb_voisins++;
		}
	}
	fclose(f);
	
	//int i;
	//for(i=0;i<nb_ajouts;i++)printf("liste[i]->node = %d\tliste[i]->emplacement=%d\n",liste[i]->node,liste[i]->emplacement);
	tas * T=ConsIter_Tableau(liste,nb_nodes);
	
	return T;
}

//---------------------------------------------------------------------K-CORE DECOMPOSITION------------------------------------------------//
void k_core_decomposition(char* s, int  nb_nodes){
	tas * T=create_heap(s, nb_nodes);
	int max_node_value=nb_nodes;
	Node ** adj = create_adjacency_array(s,&max_node_value);
	int nb_edges = 0;
	int i = T->size -1;
	int c = 0;
	
	int * N = malloc(nb_nodes*sizeof(int));
	int nb_nodes_graph = 0;
	while(T->size!=0){
		cle* v = T->a[0];
		
		N[i] = v->node; 
		int j;
		if(c<(v->nb_voisins)){
			c = (v->nb_voisins);
		}
		SupprMin_Tableau(T);
		nb_nodes_graph++;
		
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

int main(){
	k_core_decomposition(FILE_EMAIL,NODE_EMAIL);
	k_core_decomposition(FILE_AMAZON,NODE_AMAZON);
	k_core_decomposition(FILE_LJ,NODE_LJ);
	k_core_decomposition(FILE_ORKUT,NODE_ORKUT);
//	k_core_decomposition(FILE_FRIENDSTER,NODE_FRIENDSTER);
	k_core_decomposition(FILE_TEST,NODE_TEST);
	
	return 0;
}

