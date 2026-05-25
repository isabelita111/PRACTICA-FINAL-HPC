#include <stdlib.h>
#include "lu.h"

void resolverLU(double** A, double* b, double* x, int n) {

    double** L = (double**) malloc(n * sizeof(double*));
    double** U = (double**) malloc(n * sizeof(double*));

    for (int i = 0; i < n; i++) {
        L[i] = (double*) calloc(n, sizeof(double));
        U[i] = (double*) calloc(n, sizeof(double));
    }

    for (int i = 0; i < n; i++) {

        for (int k = i; k < n; k++) {

            double suma = 0;

            for (int j = 0; j < i; j++) {
                suma += L[i][j] * U[j][k];
            }

            U[i][k] = A[i][k] - suma;
        }

        for (int k = i; k < n; k++) {

            if (i == k) {
                L[i][i] = 1;
            }

            else {

                double suma = 0;

                for (int j = 0; j < i; j++) {
                    suma += L[k][j] * U[j][i];
                }

                L[k][i] = (A[k][i] - suma) / U[i][i];
            }
        }
    }

    double* y = (double*) malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) {

        y[i] = b[i];

        for (int j = 0; j < i; j++) {
            y[i] -= L[i][j] * y[j];
        }
    }

    for (int i = n - 1; i >= 0; i--) {

        x[i] = y[i];

        for (int j = i + 1; j < n; j++) {
            x[i] -= U[i][j] * x[j];
        }

        x[i] /= U[i][i];
    }

    free(y);

    for (int i = 0; i < n; i++) {
        free(L[i]);
        free(U[i]);
    }

    free(L);
    free(U);
}