#include <stdio.h>
#include <math.h>

#include "../include/jacobi.h"

void jacobi(
    int n,
    double A[n][n],
    double b[n],
    double x[n],
    int maxIter,
    double tol,
    int *iteraciones
)
{
    double xNuevo[n];

    for(int iter = 0; iter < maxIter; iter++)
    {
        for(int i = 0; i < n; i++)
        {
            double suma = 0.0;

            for(int j = 0; j < n; j++)
            {
                if(i != j)
                {
                    suma += A[i][j] * x[j];
                }
            }

            xNuevo[i] =
                (b[i] - suma) / A[i][i];
        }

        double error = 0.0;

        for(int i = 0; i < n; i++)
        {
            error += fabs(
                xNuevo[i] - x[i]
            );

            x[i] = xNuevo[i];
        }

        if(error < tol)
        {
            *iteraciones = iter + 1;
            return;
        }
    }

    *iteraciones = maxIter;
}