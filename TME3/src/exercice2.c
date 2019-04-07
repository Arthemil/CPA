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

void count(char * s){
	FILE * f = fopen(s,"r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int max_node_value = 0;
	
	long long int nb_nodes = 0;
	long long int nb_edges = 0;
	
	int * nodes = calloc(max_node_value,sizeof(int));
	int u,v;
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
	
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
		nb_edges++;
		
	}
	free(nodes);
	
	fclose(f);
	
	printf("file : %s\n",s);
	printf("\tnodes\t=%lld\n",nb_nodes);
	printf("\tedges\t=%lld\n",nb_edges);
}



int main(){
	struct timeval tv1,tv2;
   	long long time;
	count(FILE_TEST);
   	//FILE EMAIL----------------------------//
   	
   	gettimeofday(&tv1,NULL);
	count(FILE_EMAIL);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
   	printf("------------------------------\n");
   	
	//FILE AMAZON--------------------------//
	
	gettimeofday(&tv1,NULL);
	count(FILE_AMAZON);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("------------------------------\n");
	
	//FILE LJ------------------------------//
	
	gettimeofday(&tv1,NULL);
	count(FILE_LJ);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
	
	//FILE ORKUT---------------------------//
	
	gettimeofday(&tv1,NULL);
	count(FILE_ORKUT);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
   	
   	//FILE FRIENDSTER------------------------//
   	
   	gettimeofday(&tv1,NULL);
	count(FILE_FRIENDSTER);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");

	return 0;
}


