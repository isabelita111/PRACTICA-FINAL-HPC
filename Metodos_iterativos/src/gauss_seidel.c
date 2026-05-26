#include <stdio.h>
#include <math.h>

#include "../include/gauss_seidel.h"

void gaussSeidel(
    int n,
    double A[n][n],
    double b[n],
    double x[n],
    int maxIter,
    double tol,
    int *iteraciones
)
{
    for(int iter = 0; iter < maxIter; iter++)
    {
        double error = 0.0;

        for(int i = 0; i < n; i++)
        {
            double anterior = x[i];

            double suma = 0.0;

            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    suma += A[i][j] * x[j];
                }
            }

            x[i] =
                (b[i] - suma) / A[i][i];

            error += fabs(
                x[i] - anterior
            );
        }

        if(error < tol)
        {
            *iteraciones = iter + 1;
            return;
        }
    }

    *iteraciones = maxIter;
}