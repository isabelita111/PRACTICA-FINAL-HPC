#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "gaussian.h"
#include "matrix_utils.h"

// Tamanios de matrices a evaluar
static const int TAMANIOS[]   = {500, 1000, 2000, 5000};
static const int NUM_TAMANIOS = 4;
static const int NUM_HILOS    = 4; // cambiar segun los nucleos disponibles

int main(void) {
    printf("=============================================================\n");
    printf("  Eliminacion Gaussiana: Serial vs Paralelo (OpenMP)\n");
    printf("  Tamanios: 500, 1000, 2000, 5000\n");
    printf("  Hilos OpenMP: %d\n", NUM_HILOS);
    printf("=============================================================\n\n");

    // Arreglos para guardar resultados
    int    tamanio[NUM_TAMANIOS];
    double tiempo_serial[NUM_TAMANIOS];
    double tiempo_paralelo[NUM_TAMANIOS];
    double speedup[NUM_TAMANIOS];
    double error[NUM_TAMANIOS];

    for (int t = 0; t < NUM_TAMANIOS; t++) {
        int n = TAMANIOS[t];
        printf("Ejecutando N = %d ...\n", n);

        // Crear matriz y vector originales
        double** A = crearMatriz(n);
        double*  b = (double*) malloc(n * sizeof(double));
        generarMatrizDominante(A, b, n);

        double* x_serial   = (double*) malloc(n * sizeof(double));
        double* x_paralelo = (double*) malloc(n * sizeof(double));

        // Corrida serial
        double t0 = omp_get_wtime();
        gaussianSerial(A, b, x_serial, n);
        double t1 = omp_get_wtime();
        tiempo_serial[t] = t1 - t0;

        // Corrida paralela
        omp_set_num_threads(NUM_HILOS);
        double t2 = omp_get_wtime();
        gaussianParalelo(A, b, x_paralelo, n);
        double t3 = omp_get_wtime();
        tiempo_paralelo[t] = t3 - t2;

        // Calcular metricas
        speedup[t]   = (tiempo_paralelo[t] > 0.0) ? (tiempo_serial[t] / tiempo_paralelo[t]) : 0.0;
        error[t]     = normaVectores(x_serial, x_paralelo, n);
        tamanio[t]   = n;

        printf("  N=%5d | Serial: %8.4f s | Paralelo: %8.4f s | Speedup: %6.3fx | Error: %.2e\n\n",
               n, tiempo_serial[t], tiempo_paralelo[t], speedup[t], error[t]);

        liberarMatriz(A, n);
        free(b);
        free(x_serial);
        free(x_paralelo);
    }

    // Resumen final
    printf("=============================================================\n");
    printf("Resumen de Speedup:\n");
    printf("%-10s %-12s %-12s %-10s\n", "N", "Serial(s)", "Paralelo(s)", "Speedup");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < NUM_TAMANIOS; i++) {
        printf("%-10d %-12.4f %-12.4f %-10.3f\n",
               tamanio[i], tiempo_serial[i], tiempo_paralelo[i], speedup[i]);
    }

    // Guardar CSV de tiempos
    FILE* ft = fopen("results/tiempos.csv", "w");
    if (ft == NULL) {
        printf("Error: no se pudo abrir results/tiempos.csv\n");
    } else {
        fprintf(ft, "matrix_size,time_serial,time_parallel\n");
        for (int i = 0; i < NUM_TAMANIOS; i++) {
            fprintf(ft, "%d,%.6f,%.6f\n", tamanio[i], tiempo_serial[i], tiempo_paralelo[i]);
        }
        fclose(ft);
    }

    // Guardar CSV de speedup
    FILE* fs = fopen("results/speedup.csv", "w");
    if (fs == NULL) {
        printf("Error: no se pudo abrir results/speedup.csv\n");
    } else {
        fprintf(fs, "matrix_size,speedup,error\n");
        for (int i = 0; i < NUM_TAMANIOS; i++) {
            fprintf(fs, "%d,%.6f,%.2e\n", tamanio[i], speedup[i], error[i]);
        }
        fclose(fs);
    }

    printf("\nResultados guardados en:\n  results/tiempos.csv\n  results/speedup.csv\n");

    return 0;
}
