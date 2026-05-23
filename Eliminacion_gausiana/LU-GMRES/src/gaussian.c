#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include "gaussian.h"
#include "matrix_utils.h"

// Sustitucion hacia atras: resuelve U*x = b
void sustitucionAtras(double** U, double* b, double* x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
}

// Eliminacion gaussiana serial con pivoteo parcial
void gaussianSerial(double** A, double* b, double* x, int n) {
    // Copias locales para no modificar los datos originales
    double** U = crearMatriz(n);
    double*  c = (double*) malloc(n * sizeof(double));
    copiarMatriz(A, U, n);
    copiarVector(b, c, n);

    for (int k = 0; k < n; k++) {
        // Pivoteo parcial: buscar la fila con mayor valor absoluto en columna k
        int    fila_max = k;
        double val_max  = fabs(U[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(U[i][k]) > val_max) {
                val_max  = fabs(U[i][k]);
                fila_max = i;
            }
        }
        // Intercambiar filas si es necesario
        if (fila_max != k) {
            double* tmp = U[k];
            U[k]        = U[fila_max];
            U[fila_max] = tmp;
            double tmp_b = c[k];
            c[k]         = c[fila_max];
            c[fila_max]  = tmp_b;
        }

        if (fabs(U[k][k]) < 1e-12) {
            printf("Advertencia: pivote cercano a cero en fila %d (serial)\n", k);
            continue;
        }

        // Eliminar columna k en las filas inferiores
        for (int i = k + 1; i < n; i++) {
            double factor = U[i][k] / U[k][k];
            for (int j = k; j < n; j++) {
                U[i][j] -= factor * U[k][j];
            }
            c[i] -= factor * c[k];
        }
    }

    sustitucionAtras(U, c, x, n);

    liberarMatriz(U, n);
    free(c);
}

// Eliminacion gaussiana paralela con OpenMP
// El bucle externo (pivote k) es secuencial por dependencia de datos.
// El bucle interno (filas i > k) es independiente y se paraleliza.
void gaussianParalelo(double** A, double* b, double* x, int n) {
    double** U = crearMatriz(n);
    double*  c = (double*) malloc(n * sizeof(double));
    copiarMatriz(A, U, n);
    copiarVector(b, c, n);

    for (int k = 0; k < n; k++) {
        // Pivoteo parcial (secuencial - depende de pasos anteriores)
        int    fila_max = k;
        double val_max  = fabs(U[k][k]);
        for (int i = k + 1; i < n; i++) {
            if (fabs(U[i][k]) > val_max) {
                val_max  = fabs(U[i][k]);
                fila_max = i;
            }
        }
        if (fila_max != k) {
            double* tmp = U[k];
            U[k]        = U[fila_max];
            U[fila_max] = tmp;
            double tmp_b = c[k];
            c[k]         = c[fila_max];
            c[fila_max]  = tmp_b;
        }

        if (fabs(U[k][k]) < 1e-12) {
            printf("Advertencia: pivote cercano a cero en fila %d (paralelo)\n", k);
            continue;
        }

        // Paralelizar la eliminacion de las filas inferiores al pivote
        #pragma omp parallel for schedule(static)
        for (int i = k + 1; i < n; i++) {
            double factor = U[i][k] / U[k][k];
            for (int j = k; j < n; j++) {
                U[i][j] -= factor * U[k][j];
            }
            c[i] -= factor * c[k];
        }
    }

    sustitucionAtras(U, c, x, n);

    liberarMatriz(U, n);
    free(c);
}
