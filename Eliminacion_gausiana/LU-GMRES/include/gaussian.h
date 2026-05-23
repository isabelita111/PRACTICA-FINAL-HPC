#ifndef GAUSSIAN_H
#define GAUSSIAN_H

// Sustitucion hacia atras: resuelve U*x = b
void sustitucionAtras(double** U, double* b, double* x, int n);

// Eliminacion gaussiana serial con pivoteo parcial
void gaussianSerial(double** A, double* b, double* x, int n);

// Eliminacion gaussiana paralela con OpenMP
void gaussianParalelo(double** A, double* b, double* x, int n);

#endif
