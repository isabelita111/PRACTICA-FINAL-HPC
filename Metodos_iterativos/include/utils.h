#ifndef UTILS_H
#define UTILS_H

void imprimirVector(
    int n,
    double x[n]
);

void imprimirMatriz(
    int n,
    double A[n][n]
);

int esDiagonalDominante(
    int n,
    double A[n][n]
);

double calcularError(
    int n,
    double x1[n],
    double x2[n]
);

#endif