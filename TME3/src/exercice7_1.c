#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct Edge Edge; 
struct Edge {
	int u;
	int v;
};

char * FILE_TEST	= "../ressource/testGraphe_clean.txt";
char * FILE_EMAIL	= "/Vrac/TME_CPA_19-02-20/email-Eu-core-clean.txt";
char * FILE_AMAZON	= "/Vrac/TME_CPA_19-02-20/com-amazon.ungraph-clean.txt";
char * FILE_LJ		= "/Vrac/TME_CPA_19-02-20/com-lj.ungraph-clean.txt";
char * FILE_ORKUT	= "/Vrac/TME_CPA_19-02-20/com-orkut.ungraph-clean.txt";
char * FILE_FRIENDSTER	= "/Vrac/TME_CPA_19-02-20/com-friendster.ungraph.txt";

int NB_EDGES_EMAIL 		= 16064;
int NB_EDGES_AMAZON		= 925872;
int NB_EDGES_LJ 		= 34681189;
int NB_EDGES_ORKUT 		= 117185083;
int NB_EDGES_FRIENDSTER 	= 1806067135;

void stock(char * s,int nb_edges){
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int u,v;
	
	Edge **list = calloc(nb_edges,sizeof(Edge*));
	int i = 0;
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
		Edge * e = malloc(sizeof(Edge));
		e->u = u;
		e->v = v;
		list[i] = e;
		i++;
	}
	fclose(f);
	
	/*int i;
	for(i =0;i<nb_edges;i++){
		printf("%d %d\n",list[i]->u,list[i]->v);
	}*/

	free(list);
}

int main(){
	struct timeval tv1,tv2;
   	long long time;
	
   	//FILE EMAIL----------------------------//
   	
   	printf("running for email\n");
   	gettimeofday(&tv1,NULL);
	stock(FILE_EMAIL,NB_EDGES_EMAIL);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
   	printf("------------------------------\n");
   	
	//FILE AMAZON--------------------------//
	
	printf("running for amazon\n");
	gettimeofday(&tv1,NULL);
	stock(FILE_AMAZON,NB_EDGES_AMAZON);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("------------------------------\n");
	
	//FILE LJ------------------------------//
	
	printf("running for lj\n");
	gettimeofday(&tv1,NULL);
	stock(FILE_LJ,NB_EDGES_LJ);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
	
	//FILE ORKUT---------------------------//
	printf("running for orkut\n");
	gettimeofday(&tv1,NULL);
	stock(FILE_ORKUT,NB_EDGES_ORKUT);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
   	
   	//FILE FRIENDSTER------------------------//
/*	
   	printf("running for friendster\n");
   	gettimeofday(&tv1,NULL);
	stock(FILE_FRIENDSTER,NB_EDGES_FRIENDSTER);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
*/
	return 0;
}

