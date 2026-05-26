#include <stdio.h>
#include <math.h>

#include "../include/utils.h"

void imprimirVector(
    int n,
    double x[n]
)
{
    for(int i = 0; i < n; i++)
    {
        printf(
            "x%d = %.6f\n",
            i + 1,
            x[i]
        );
    }
}

void imprimirMatriz(
    int n,
    double A[n][n]
)
{
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%.2f ", A[i][j]);
        }

        printf("\n");
    }
}

int esDiagonalDominante(
    int n,
    double A[n][n]
)
{
    for(int i = 0; i < n; i++)
    {
        double suma = 0.0;

        for(int j = 0; j < n; j++)
        {
            if(i != j)
            {
                suma += fabs(A[i][j]);
            }
        }

        if(fabs(A[i][i]) <= suma)
        {
            return 0;
        }
    }

    return 1;
}

double calcularError(
    int n,
    double x1[n],
    double x2[n]
)
{
    double error = 0.0;

    for(int i = 0; i < n; i++)
    {
        error += fabs(x1[i] - x2[i]);
    }

    return error;
}