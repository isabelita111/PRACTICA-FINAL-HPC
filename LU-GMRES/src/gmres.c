#include <omp.h>
#include "gmres.h"

void gmresSimple(double** A, double* b, double* x, int n, int iteraciones) {

    double r[n];

    for (int i = 0; i < n; i++) {
        x[i] = 0.0;
    }

    for (int k = 0; k < iteraciones; k++) {

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {

            double suma = 0.0;

            for (int j = 0; j < n; j++) {
                suma += A[i][j] * x[j];
            }

            r[i] = b[i] - suma;
        }

        #pragma omp parallel for
        for (int i = 0; i < n; i++) {
            x[i] += 0.01 * r[i];
        }
    }
}