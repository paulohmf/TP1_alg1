  
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int main(int argc, char *argv[]){
	if(argc <= 2){
		printf("necessário mais parametros\n");
		return 0;
	}

	int N = atoi(argv[1]);
	int M = atoi(argv[2]);
	int num_jogadores = 11; 
	printf("%d %d\n%d\n",N,M,num_jogadores);

	srand(time(NULL));

	for(int i=0;i<N;i++){
		for(int j=0; j<M;j++){
			int pulo = rand()%10;
			printf("%d ", pulo);
		}
		printf(" \n");
	}
	printf("\n");

	for(int i=0;i<num_jogadores;i++){
		int pos_n = rand()%N;
		int pos_m = rand()%M;
		printf("%d %d\n",pos_n,pos_m);
	}
	return 0;

}

/* SCRIPT

TIMEFORMAT="%U"
for i in {10..100000..50}; do for j in {1..100..1}; do TIME=`./rand ${i} | { time ./tp1 > /dev/null; }` TIME=${TIME//\\n//}; echo "${i} ${i} ${TIME}"; done; done &> tempos.txt


*/