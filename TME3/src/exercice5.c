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

char * FILE_TEST_D	= "../ressource/Degrees/testGraphe_degree.txt";
char * FILE_EMAIL_D	= "../ressource/Degrees/email_degree.txt";
char * FILE_AMAZON_D	= "../ressource/Degrees/amazon_degree.txt ";
char * FILE_LJ_D	= "../ressource/Degrees/lj_degree.txt";
char * FILE_ORKUT_D	= "../ressource/Degrees/orkut_degree.txt";

void Qsum(char * s, char * d){
	int max_node_value = 0;
	FILE *fclean = fopen(s, "r");
	FILE *fdegrees = fopen(d,"r");
	if(fclean==NULL||fdegrees==NULL){
		printf("File ERROR\n");
		return;
	}
	int u,v;
	
	int * degrees =calloc(max_node_value,sizeof(int));
	long long int Qsum=0;
	
	//copy of degrees for each nodes in array
	while(fscanf(fdegrees,"%d %d\n", &u, &v) != EOF){
		if(u>max_node_value){			
			int tmp = max_node_value+1;
			max_node_value = u;
			degrees = realloc(degrees, (1+max_node_value)*sizeof(int));
			int i;
			for (i = tmp;i<=max_node_value;i++)degrees[i] = 0; 
		}
		degrees[u]=v;
	}
	fclose(fdegrees);
	while(fscanf(fclean,"%d %d\n", &u, &v) != EOF){
		Qsum += degrees[u] * degrees[v];
	}
	
	fclose(fclean);
	free(degrees);
	printf("file : %s\n",s);
	printf("\t Q quantity= %lld\n", Qsum);
}

void QsumFriendster(char * s){
	int max_node_value =0;
	FILE *f = fopen(s, "r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}
	int u,v;
	int * degrees =calloc(max_node_value,sizeof(int));
	long long int Qsum = 0;
	
	//copy of degrees for each nodes in list
	while(fscanf(f,"%d %d\n", &u, &v) != EOF){
		if(u>max_node_value){			
			int tmp = max_node_value+1;
			max_node_value = u;
			degrees = realloc(degrees, (1+max_node_value)*sizeof(int));
			int i;
			for (i = tmp;i<=max_node_value;i++)degrees[i] = 0; 
		}
		if(v>max_node_value){
			int tmp = max_node_value+1;
			max_node_value = v;
			degrees = realloc(degrees, (1+max_node_value)*sizeof(int));
			int i;
			for (i = tmp;i<=max_node_value;i++)degrees[i] = 0;
		}
		degrees[u]++ ;
		degrees[v]++ ;
	}
	rewind(f);
	
	while(fscanf(f,"%d %d\n", &u, &v) != EOF){
		Qsum += degrees[u] * degrees[v];
	}
	
	fclose(f);
	free(degrees);
	
	printf("file : %s\n",s);
	printf("\t Q quantity= %lld\n", Qsum);
}
int main(){
	struct timeval tv1,tv2;
   	long long time;
   	
   	//FILE TEST---------------------------//
/*	
	gettimeofday(&tv1,NULL);
	Qsum(FILE_TEST, FILE_TEST_D);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("---------------------------------\n");
*/
	//FILE EMAIL---------------------------//
	
   	gettimeofday(&tv1,NULL);
	Qsum(FILE_EMAIL, FILE_EMAIL_D);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("---------------------------------\n");
	
	//FILE AMAZON---------------------------//
	
	gettimeofday(&tv1,NULL);
	Qsum(FILE_AMAZON, FILE_AMAZON_D);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);	
	printf("---------------------------------\n");
	
	//FILE LJ---------------------------//
	
	gettimeofday(&tv1,NULL);
	Qsum(FILE_LJ, FILE_LJ_D);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
	printf("---------------------------------\n");
	
	//FILE ORKUT---------------------------//
	
	gettimeofday(&tv1,NULL);
	Qsum(FILE_ORKUT, FILE_ORKUT_D);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	
   	printf("cpu time=%lld s\n",time);
   	printf("---------------------------------\n");
   	
   	//FILE FRIENDSTER---------------------------//
/*   	
   	gettimeofday(&tv1,NULL);
	QsumFriendster(FILE_FRIENDSTER);
	gettimeofday(&tv2,NULL);
	
   	time=(tv2.tv_sec-tv1.tv_sec);
   	printf("cpu time=%lld s\n",time);	
*/	
	return 0;
}


