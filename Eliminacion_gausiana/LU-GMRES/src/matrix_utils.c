#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matrix_utils.h"

// PUNTO A - Reservar memoria para una matriz n x n
double** crearMatriz(int n) {
    double** A = (double**) malloc(n * sizeof(double*));
    if (A == NULL) {
        printf("Error: no se pudo asignar memoria para las filas\n");
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        A[i] = (double*) calloc(n, sizeof(double));
        if (A[i] == NULL) {
            printf("Error: no se pudo asignar memoria para la fila %d\n", i);
            return NULL;
        }
    }
    return A;
}

// Liberar memoria de una matriz n x n
void liberarMatriz(double** A, int n) {
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
}

// Genera una matriz diagonalmente dominante y vector b con semilla fija
void generarMatrizDominante(double** A, double* b, int n) {
    srand(42);
    for (int i = 0; i < n; i++) {
        double suma_fila = 0.0;
        for (int j = 0; j < n; j++) {
            if (i != j) {
                A[i][j] = ((double)rand() / RAND_MAX) * 2.0 - 1.0; // valores en [-1, 1]
                suma_fila += fabs(A[i][j]);
            }
        }
        // Diagonal dominante: garantiza solucion unica y estabilidad numerica
        A[i][i] = suma_fila + ((double)rand() / RAND_MAX) + 1.0;
        b[i]    = ((double)rand() / RAND_MAX) * 10.0;
    }
}

// Copia una matriz origen en destino
void copiarMatriz(double** origen, double** destino, int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            destino[i][j] = origen[i][j];
}

// Copia un vector origen en destino
void copiarVector(double* origen, double* destino, int n) {
    for (int i = 0; i < n; i++)
        destino[i] = origen[i];
}

// Norma euclidiana de la diferencia entre dos vectores
double normaVectores(double* x, double* y, int n) {
    double suma = 0.0;
    for (int i = 0; i < n; i++) {
        double diff = x[i] - y[i];
        suma += diff * diff;
    }
    return sqrt(suma);
}
