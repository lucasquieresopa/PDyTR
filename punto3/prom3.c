#include <stdio.h>
#include <math.h>

int main(){
	FILE *f = fopen("pingpong.txt", "r");

	double aux, val[6] = {0}; // arreglo de 6 pos, una por métrica
	int i = 0, j = 0;
    while(fscanf(f, "%lf", &aux) == 1){
    	val[i] += aux;
    	i++;
    	if((i % 6) == 0){
    		i = 0;
    		j++;
    	}	
    }
	fclose(f);
	// se calcula el promedio para cada una de las 6 métricas
	for(int i = 1; i<7; i++){
		int s = (int)(pow(10, i)+0.5);
		printf("Para %d : %lf\n", s, (val[i-1] / j));
	}
	
	
	return 0;

}
