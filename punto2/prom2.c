#include <stdio.h>
#include <math.h>

int main() {
    FILE *rf = fopen("read_time.txt", "r");
    FILE *wf = fopen("write_time.txt", "r");
    FILE *prom_file = fopen("prom_file.txt", "a");

    double aux, rt[6] = {0}, wt[6] = {0}; // arreglo de 6 pos, una por métrica
    int j_read = 0, j_write = 0;

    // READ
    int i = 0;
    while(fscanf(rf, "%lf", &aux) == 1){
    	rt[i] += aux;
    	i++;
    	if((i % 6) == 0){
    		i = 0;
    		j_read++;
    	}	
    }
    // WRITE
    i = 0;
    while(fscanf(wf, "%lf", &aux) == 1){
    	wt[i] += aux;
    	i++;
    	if((i % 6) == 0){
    		i = 0;
    		j_write++;
    	}	
    }
    
    


    fclose(rf);
    fclose(wf);

    // Se calcula el promedio para cada una de las 6 métricas
    printf("RESULTADOS DEL READ: \n");
    for (int i = 0; i < 6; i++) {
    	int s = (int)(pow(10, i)+0.5);
        printf("Para métrica %d : %lf\n", s, (rt[i] / j_read));
    }

    printf("\nRESULTADOS DEL WRITE: \n");
    for (int i = 0; i < 6; i++) {
   		int s = (int)(pow(10, i)+0.5);
        fprintf(prom_file, "%lf\n", (wt[i] / j_write));
        printf("Para métrica %d : %lf\n", s, (wt[i] / j_write));
    }
    fclose(prom_file);
    return 0;
}
