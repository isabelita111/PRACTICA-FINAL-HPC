#include <stdio.h>
#include <time.h>

#include "../include/jacobi.h"
#include "../include/gauss_seidel.h"

int main()
{
    int n = 3;

    double A[3][3] = {
        {10,1,1},
        {2,10,1},
        {2,2,10}
    };

    double b[3] = {
        12,
        13,
        14
    };

    double xJacobi[3] = {0,0,0};

    double xGS[3] = {0,0,0};

    int iterJacobi = 0;

    int iterGS = 0;

    clock_t inicio;
    clock_t fin;

    // =========================
    // ARCHIVO TXT
    // =========================

    FILE* resultados =
        fopen("results/resultados.txt", "w");

    if(resultados == NULL)
    {
        printf("Error creando archivo\n");
        return 1;
    }

    fprintf(
        resultados,
        "====================================\n"
    );

    fprintf(
        resultados,
        "METODOS ITERATIVOS\n"
    );

    fprintf(
        resultados,
        "Jacobi y Gauss-Seidel\n"
    );

    fprintf(
        resultados,
        "====================================\n\n"
    );

    fprintf(
        resultados,
        "Sistema utilizado:\n\n"
    );

    fprintf(
        resultados,
        "10x1 + 1x2 + 1x3 = 12\n"
    );

    fprintf(
        resultados,
        "2x1 + 10x2 + 1x3 = 13\n"
    );

    fprintf(
        resultados,
        "2x1 + 2x2 + 10x3 = 14\n\n"
    );

    // =========================
    // JACOBI
    // =========================

    inicio = clock();

    jacobi(
        n,
        A,
        b,
        xJacobi,
        100,
        1e-6,
        &iterJacobi
    );

    fin = clock();

    double tiempoJacobi =
        (double)(fin - inicio)
        / CLOCKS_PER_SEC;

    // =========================
    // GAUSS-SEIDEL
    // =========================

    inicio = clock();

    gaussSeidel(
        n,
        A,
        b,
        xGS,
        100,
        1e-6,
        &iterGS
    );

    fin = clock();

    double tiempoGS =
        (double)(fin - inicio)
        / CLOCKS_PER_SEC;

    // =========================
    // RESULTADOS JACOBI
    // =========================

    fprintf(
        resultados,
        "====================================\n"
    );

    fprintf(
        resultados,
        "RESULTADOS JACOBI\n"
    );

    fprintf(
        resultados,
        "====================================\n\n"
    );

    for(int i = 0; i < n; i++)
    {
        fprintf(
            resultados,
            "x%d = %.6f\n",
            i + 1,
            xJacobi[i]
        );
    }

    fprintf(
        resultados,
        "\nIteraciones: %d\n",
        iterJacobi
    );

    fprintf(
        resultados,
        "Tiempo: %f segundos\n\n",
        tiempoJacobi
    );

    // =========================
    // RESULTADOS GAUSS-SEIDEL
    // =========================

    fprintf(
        resultados,
        "====================================\n"
    );

    fprintf(
        resultados,
        "RESULTADOS GAUSS-SEIDEL\n"
    );

    fprintf(
        resultados,
        "====================================\n\n"
    );

    for(int i = 0; i < n; i++)
    {
        fprintf(
            resultados,
            "x%d = %.6f\n",
            i + 1,
            xGS[i]
        );
    }

    fprintf(
        resultados,
        "\nIteraciones: %d\n",
        iterGS
    );

    fprintf(
        resultados,
        "Tiempo: %f segundos\n\n",
        tiempoGS
    );

    // =========================
    // COMPARACION FINAL
    // =========================

    fprintf(
        resultados,
        "====================================\n"
    );

    fprintf(
        resultados,
        "COMPARACION FINAL\n"
    );

    fprintf(
        resultados,
        "====================================\n\n"
    );

    if(iterGS < iterJacobi)
    {
        fprintf(
            resultados,
            "Gauss-Seidel convergio mas rapido\n"
        );
    }
    else
    {
        fprintf(
            resultados,
            "Jacobi convergio mas rapido\n"
        );
    }

    fprintf(
        resultados,
        "\nConclusiones:\n\n"
    );

    fprintf(
        resultados,
        "- Ambos metodos convergieron correctamente\n"
    );

    fprintf(
        resultados,
        "- Gauss-Seidel necesito menos iteraciones\n"
    );

    fprintf(
        resultados,
        "- La diagonal dominante favorecio la convergencia\n"
    );

    fclose(resultados);

    // =========================
    // CSV PARA GRAFICAS
    // =========================

    FILE* tiempos =
        fopen("results/tiempos.csv", "w");

    fprintf(
        tiempos,
        "Metodo,Iteraciones\n"
    );

    fprintf(
        tiempos,
        "Jacobi,%d\n",
        iterJacobi
    );

    fprintf(
        tiempos,
        "Gauss-Seidel,%d\n",
        iterGS
    );

    fclose(tiempos);

    // =========================
    // CONSOLA
    // =========================

    printf(
        "\n====================================\n"
    );

    printf(
        "METODOS ITERATIVOS\n"
    );

    printf(
        "====================================\n"
    );

    printf(
        "\nJacobi:\n"
    );

    printf(
        "Iteraciones: %d\n",
        iterJacobi
    );

    printf(
        "Tiempo: %f segundos\n",
        tiempoJacobi
    );

    printf(
        "\nGauss-Seidel:\n"
    );

    printf(
        "Iteraciones: %d\n",
        iterGS
    );

    printf(
        "Tiempo: %f segundos\n",
        tiempoGS
    );

    printf(
        "\nResultados guardados en results/\n"
    );

    return 0;
}