#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H

void gaussSeidel(
    int n,
    double A[n][n],
    double b[n],
    double x[n],
    int maxIter,
    double tol,
    int *iteraciones
);

#endif