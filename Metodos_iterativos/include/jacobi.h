#ifndef JACOBI_H
#define JACOBI_H

void jacobi(
    int n,
    double A[n][n],
    double b[n],
    double x[n],
    int maxIter,
    double tol,
    int *iteraciones
);

#endif
