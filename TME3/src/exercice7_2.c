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

typedef struct Line Line; 
struct Line {
	int * list;
};

void stock(char * s){

	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int u,v;
	int max_node_value = 0;
	int i;
	//getting max node value for matrice
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
		if(u>max_node_value)max_node_value=u;
		if(v>max_node_value)max_node_value=v;
	}
	max_node_value++;
/*	
	long long unsigned int Go = 1073741824; //nb bytes in one Go;
	long long unsigned int nb_bytes = max_node_value*max_node_value*sizeof(int);
	nb_bytes+=max_node_value*8;//bytes of a pointer
	
	printf("%llu bytes needed\n",nb_bytes);
	if(nb_bytes>Go){
		printf("more than 8 Go needed\n");
		return;
	}
	
*/	
	//line * column
	Line * matrice = (Line*)malloc(max_node_value*sizeof(Line));
	for(i=0;i<max_node_value;i++)matrice[i].list=malloc(max_node_value*sizeof(int));
	
	rewind(f);
	
	//matrice creation
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
		matrice[u].list[v] = 1;
		matrice[v].list[u] = 1;
	}
	fclose(f);
	
/*
	for(i = 0; i <max_node_value;i++)printf("%d  ",i);
	printf("\n");
	for(i =0;i<max_node_value;i++){
		int j;
		for(j=0;j<max_node_value;j++){
			printf("%d  ",matrice[i].list[j]);
		}
		printf("\n");
	}
	printf("\n");
*/
	
	//free memory
	for(i=0;i<max_node_value;i++)free(matrice[i].list);
	free(matrice);
}

int main(){
	struct timeval tv1,tv2;
   	long long time;
	
	//stock(FILE_TEST);
	
   	//FILE EMAIL----------------------------//
   	printf("running for email\n");
   	gettimeofday(&tv1,NULL);
	stock(FILE_EMAIL);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
   	printf("------------------------------\n");
   	
	//FILE AMAZON--------------------------//
	
	printf("running for amazon\n");
	gettimeofday(&tv1,NULL);
	stock(FILE_AMAZON);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("------------------------------\n");
/*	
	//FILE LJ------------------------------//
	
	printf("running for lj\n");
	gettimeofday(&tv1,NULL);
	stock(FILE_LJ);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
	
	//FILE ORKUT---------------------------//
	printf("running for orkut\n");
	gettimeofday(&tv1,NULL);
	stock(FILE_ORKUT);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
  	
   	//FILE FRIENDSTER------------------------//
   	
   	printf("running for friendster\n");
   	gettimeofday(&tv1,NULL);
	stock(FILE_FRIENDSTER);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	printf("cpu time=%lld s\n",time);
   	printf("------------------------------\n");
*/
	return 0;
}

