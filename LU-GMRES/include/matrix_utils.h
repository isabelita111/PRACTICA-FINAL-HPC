#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

double** crearMatriz(int n);

void liberarMatriz(double** A, int n);

void generarMatrizDominante(double** A, double* b, int n);

void copiarMatriz(double** origen, double** destino, int n);

void copiarVector(double* origen, double* destino, int n);

double normaVectores(double* x, double* y, int n);

#endif