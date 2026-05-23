¿Cuál fue el problema?
El objetivo fue resolver sistemas de ecuaciones lineales de la forma Ax = b, donde A es una matriz cuadrada de tamaño N×N. Este tipo de problema aparece en simulaciones científicas, ingeniería y procesamiento de datos, y se vuelve muy costoso computacionalmente cuando las matrices son grandes.
Para resolverlo se implementó la Eliminación Gaussiana con pivoteo parcial, primero de forma serial (un solo hilo) y luego de forma paralela usando OpenMP, con el fin de comparar el rendimiento de ambas versiones.

¿Qué se hizo?
Se implementaron dos versiones del mismo algoritmo:
1. Versión Serial
Recorre la matriz fila por fila de forma secuencial. Sirve como línea base para medir el tiempo de referencia.
2. Versión Paralela con OpenMP
El bucle externo (que selecciona el pivote) debe ser secuencial porque cada paso depende del anterior. Sin embargo, el bucle interno (que elimina los valores debajo del pivote) es independiente entre filas y se puede ejecutar en paralelo. Se usaron 4 hilos OpenMP para distribuir ese trabajo.
Ambas versiones incluyen pivoteo parcial, que intercambia filas para mejorar la estabilidad numérica, y al final se aplica sustitución hacia atrás para obtener la solución x.

¿Qué tipo de matrices se usaron?
Se generaron matrices diagonalmente dominantes de forma aleatoria con semilla fija (srand(42)), lo que garantiza:

Solución única: el sistema siempre tiene solución.
Estabilidad numérica: el pivote nunca es cero o muy cercano a cero, evitando errores de división.
Reproducibilidad: los mismos resultados en cualquier máquina.

Los tamaños evaluados fueron: N = 500, 1000, 2000 y 5000.

Resultados
NSerial (s)Paralelo (s)Speedup5000.03800.04000.950x10000.18200.22600.805x20002.14101.52301.406x500047.449031.27901.517x

El error entre la solución serial y paralela fue 0.00e+00 en todos los casos, lo que confirma que ambas versiones producen resultados idénticos.

¿Por qué el speedup es bajo para N pequeñas?
Para matrices pequeñas (500, 1000), el tiempo que tarda OpenMP en crear y sincronizar los hilos es mayor que el trabajo que se ahorra. A partir de N=2000 el paralelismo ya vale la pena, y la tendencia indica que seguiría mejorando con matrices más grandes.

Estructura del proyecto
LU-GMRES/
│
├── src/                    # Código fuente en C
│   ├── main.c              # Punto de entrada: mide tiempos y guarda resultados
│   ├── gaussian.c          # Implementación serial y paralela del algoritmo
│   └── matrix_utils.c      # Funciones auxiliares: crear, copiar y liberar matrices
│
├── include/                # Archivos de cabecera
│   ├── gaussian.h          # Declaraciones de las funciones gaussianas
│   └── matrix_utils.h      # Declaraciones de las funciones de matriz
│
├── plots/                  # Gráficas generadas
│   ├── graficas.py         # Script Python para generar las gráficas
│   ├── tiempos.png         # Gráfica: tiempo serial vs paralelo
│   └── speedup.png         # Gráfica: speedup por tamaño de matriz
│
├── results/                # Resultados numéricos (generados al correr el programa)
│   ├── tiempos.csv         # Tiempos de ejecución por tamaño de matriz
│   └── speedup.csv         # Speedup y error por tamaño de matriz
│
├── gaussian.exe            # Ejecutable compilado (Windows)
└── README.md               # Este archivo
