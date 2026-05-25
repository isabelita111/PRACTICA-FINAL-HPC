#include <stdio.h>
#include "benchmark.h"

void guardarTiempo(char* metodo, int n, int threads, double tiempo) {

    FILE* archivo = fopen("results/tiempos.csv", "a");

    fprintf(archivo, "%s,%d,%d,%f\n",
            metodo,
            n,
            threads,
            tiempo);

    fclose(archivo);
}