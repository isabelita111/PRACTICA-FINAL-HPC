#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#include "matrix_utils.h"
#include "lu.h"
#include "gmres.h"
#include "benchmark.h"

int main() {

    int tamanos[] = {500, 1000, 2000};

    FILE* archivo = fopen("results/tiempos.csv", "w");

    fprintf(archivo, "metodo,n,threads,tiempo\n");

    fclose(archivo);

    for (int t = 0; t < 3; t++) {

        int n = tamanos[t];

        double** A = crearMatriz(n);

        double* b = (double*) malloc(n * sizeof(double));

        double* x_lu = (double*) malloc(n * sizeof(double));

        double* x_gmres = (double*) malloc(n * sizeof(double));

        generarMatrizDominante(A, b, n);

        double inicio;
        double fin;

        // LU

        inicio = omp_get_wtime();

        resolverLU(A, b, x_lu, n);

        fin = omp_get_wtime();

        printf("\nLU n=%d tiempo=%f\n", n, fin - inicio);

        guardarTiempo("LU", n, 1, fin - inicio);

        // GMRES SERIAL

        omp_set_num_threads(1);

        inicio = omp_get_wtime();

        gmresSimple(A, b, x_gmres, n, 500);

        fin = omp_get_wtime();

        printf("GMRES serial n=%d tiempo=%f\n", n, fin - inicio);

        guardarTiempo("GMRES_SERIAL", n, 1, fin - inicio);

        // GMRES OPENMP

        omp_set_num_threads(4);

        inicio = omp_get_wtime();

        gmresSimple(A, b, x_gmres, n, 500);

        fin = omp_get_wtime();

        printf("GMRES OpenMP n=%d tiempo=%f\n", n, fin - inicio);

        guardarTiempo("GMRES_OPENMP", n, 4, fin - inicio);

        liberarMatriz(A, n);

        free(b);
        free(x_lu);
        free(x_gmres);
    }

    return 0;
}