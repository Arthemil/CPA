#include <stdio.h>
#include <stdlib.h>

char * FILE_TEST_D	= "../ressource/Degrees/testGraphe_degree.txt";
char * FILE_EMAIL_D	= "../ressource/Degrees/email_degree.txt";
char * FILE_AMAZON_D	= "../ressource/Degrees/amazon_degree.txt ";
char * FILE_LJ_D	= "../ressource/Degrees/lj_degree.txt";
char * FILE_ORKUT_D	= "../ressource/Degrees/orkut_degree.txt";
char * FILE_FRIENDSTER_D= "/Vrac/TME_CPA_19-02-20/com-friendster.ungraph.txt";

char * FILE_TEST_DD	= "../ressource/Degrees/Distribution/testGraphe_degree_distribution.txt";
char * FILE_EMAIL_DD	= "../ressource/Degrees/Distribution/email_degree_distribution.txt";
char * FILE_AMAZON_DD	= "../ressource/Degrees/Distribution/amazon_degree_distribution.txt";
char * FILE_LJ_DD	= "../ressource/Degrees/Distribution/lj_degree_distribution.txt";
char * FILE_ORKUT_DD	= "../ressource/Degrees/Distribution/orkut_degree_distribution.txt";
char * FILE_FRIENDSTER_DD="../ressource/Degrees/Distribution/friendster_degree_distribution.txt";

void DegreesDistribution(char * s,char * d){
	
	int max_degree = 0;
	
	FILE *f = fopen(s, "r");
	FILE *fw= fopen(d, "w");
	if(f==NULL||fw==NULL){
		printf("File ERROR\n");
		return;
	}
	int u,v;
	int * degreesDistribution = calloc(max_degree,sizeof(int));
	
	while(fscanf(f,"%d %d\n" ,&u,&v) != EOF){
		//increasing size of list to the max index value
		if(v>max_degree){
			int tmp = max_degree+1;
			max_degree = v;
			degreesDistribution = realloc(degreesDistribution, (1+max_degree)*sizeof(int));
			int i;
			for (i = tmp;i<=max_degree;i++)degreesDistribution[i] = 0;
		}
		degreesDistribution[v]++ ;
	}
	fclose(f);
	int i;
	for(i = 0; i <= max_degree; i++){
		if(degreesDistribution[i] == 0)continue;
		fprintf(fw,"%d  %d\n",i,degreesDistribution[i]);
	}
	
	fclose(fw);
	free(degreesDistribution);
	
	printf("writing done for %s\n",s);
}

void DegreesDistributionFriendster(char * s,char * d){
	int max_node_value = 0;
	
	FILE *f = fopen(s, "r");
	FILE *fw= fopen(d, "w");
	if(f==NULL||fw==NULL){
		printf("File ERROR\n");
		return;
	}
	int u,v;
	int * degrees = calloc(max_node_value,sizeof(int));
	
	
	printf("begin read\n");
	while(fscanf(f,"%d %d\n", &u, &v) != EOF){
		
		//increasing size of list to the max index value
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
	
	int * degreesDistribution = malloc(max_node_value*sizeof(int));
	
	int i;
	printf("calculating degreesDistribution\n");
	for(i = 0; i<= max_node_value; i++){
		if(degrees[i]==0)continue;
		degreesDistribution[degrees[i]]++;
		
	}
	free(degrees);
	
	printf("writing in file\n");
	for(i = 0; i <= max_node_value; i++){
		if(degreesDistribution[i] == 0)continue;
		fprintf(fw,"%d  %d\n",i,degreesDistribution[i]);
	}
	printf("writing done for %s\n",s);
	
	fclose(fw);
	free(degreesDistribution);
}


int main(){
	
	
	DegreesDistribution(FILE_TEST_D, FILE_TEST_DD);
	DegreesDistribution(FILE_EMAIL_D, FILE_EMAIL_DD);
	DegreesDistribution(FILE_AMAZON_D, FILE_AMAZON_DD);
	DegreesDistribution(FILE_LJ_D, FILE_LJ_DD);
	DegreesDistribution(FILE_ORKUT_D, FILE_ORKUT_DD);
//	DegreesDistributionFriendster(FILE_FRIENDSTER_D, FILE_FRIENDSTER_DD);
	return 0;
}




