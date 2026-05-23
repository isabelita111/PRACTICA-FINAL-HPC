#ifndef MATRIX_UTILS_H
#define MATRIX_UTILS_H

// Reserva memoria para una matriz n x n
double** crearMatriz(int n);

// Libera la memoria de una matriz n x n
void liberarMatriz(double** A, int n);

// Genera una matriz diagonalmente dominante y un vector b
void generarMatrizDominante(double** A, double* b, int n);

// Copia una matriz origen en destino
void copiarMatriz(double** origen, double** destino, int n);

// Copia un vector origen en destino
void copiarVector(double* origen, double* destino, int n);

// Calcula la norma euclidiana de la diferencia entre dos vectores
double normaVectores(double* x, double* y, int n);

#endif
