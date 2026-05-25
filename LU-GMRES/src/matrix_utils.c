#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_utils.h"

double** crearMatriz(int n) {

    double** A = (double**) malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        A[i] = (double*) calloc(n, sizeof(double));
    }

    return A;
}

void liberarMatriz(double** A, int n) {

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }

    free(A);
}

void generarMatrizDominante(double** A, double* b, int n) {

    srand(42);

    for (int i = 0; i < n; i++) {

        double suma = 0.0;

        for (int j = 0; j < n; j++) {

            if (i != j) {

                A[i][j] = ((double) rand() / RAND_MAX) * 2.0 - 1.0;

                suma += fabs(A[i][j]);
            }
        }

        A[i][i] = suma + 1.0;

        b[i] = ((double) rand() / RAND_MAX) * 10.0;
    }
}

void copiarMatriz(double** origen, double** destino, int n) {

    for (int i = 0; i < n; i++) {

        for (int j = 0; j < n; j++) {
            destino[i][j] = origen[i][j];
        }
    }
}

void copiarVector(double* origen, double* destino, int n) {

    for (int i = 0; i < n; i++) {
        destino[i] = origen[i];
    }
}

double normaVectores(double* x, double* y, int n) {

    double suma = 0.0;

    for (int i = 0; i < n; i++) {

        double diff = x[i] - y[i];

        suma += diff * diff;
    }

    return sqrt(suma);
}