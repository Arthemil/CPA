#include <stdio.h>
#include <stdlib.h>

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
char * FILE_FRIENDSTER_D= "../ressource/Degrees/friendster_degree.txt";

void CountDegree(char * s,char * d){
	FILE * f = fopen(s,"r");
	if(f==NULL){
		printf("File ERROR\n");
		return;
	}	
	int max_node_value = 0;
	
	int * degrees =calloc(max_node_value,sizeof(int));
	int u,v;
	
	printf("begin read\n");
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
	
		//increasing size of array to the max index(node) value
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
	fclose(f);
	printf("end read\n");
	
	FILE *fw = fopen(d,"w");
	int i;
	
	//writing in file
	printf("writing in file\n");
	for(i = 0; i <= max_node_value ; i++){
	
		if(degrees[i] == 0)continue;
		fprintf(fw,"%d  %d\n",i,degrees[i]);
	}
	
	fclose(fw);
	free(degrees);
	
	printf("writing done for %s\n",s);
	printf("------------------------------------\n");
}

int main(){
	
	
	CountDegree(FILE_TEST, FILE_TEST_D);
	CountDegree(FILE_EMAIL, FILE_EMAIL_D);
	CountDegree(FILE_AMAZON, FILE_AMAZON_D);
	CountDegree(FILE_LJ, FILE_LJ_D);
	CountDegree(FILE_ORKUT, FILE_ORKUT_D);
	CountDegree(FILE_FRIENDSTER, FILE_FRIENDSTER_D);

	return 0;
}
