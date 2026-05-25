# LU y GMRES con OpenMP

Práctica Final

---

## ¿Cuál fue el problema?

El objetivo fue resolver sistemas de ecuaciones lineales de la forma **Ax = b**, donde A es una matriz cuadrada de tamaño N×N. Este tipo de problemas aparece en simulaciones científicas, física computacional, ingeniería y procesamiento de datos, y se vuelve costoso computacionalmente cuando las matrices son grandes.

Para resolverlo se implementaron dos enfoques distintos:

- **LU Decomposition** como método tradicional/directo.
- **GMRES** como método iterativo.

Además, se utilizó **OpenMP** para paralelizar partes del método iterativo y comparar el rendimiento entre la versión serial y la paralela.

---

## ¿Qué se hizo?

Se implementaron tres pruebas principales:

### 1. LU Decomposition

Este método descompone la matriz A en dos matrices:

- L → triangular inferior
- U → triangular superior

Después se resuelve el sistema usando sustitución hacia adelante y sustitución hacia atrás.

Este método es preciso, pero el costo computacional aumenta rápidamente cuando el tamaño de la matriz crece.

---

### 2. GMRES Serial

Se implementó una versión simplificada de GMRES usando iteraciones sucesivas para aproximar la solución.

En cada iteración:

- se calcula el residual:
  
  r = b - Ax

- luego se actualiza la solución aproximada x.

Este método utiliza menos memoria que LU y es más adecuado para sistemas grandes.

---

### 3. GMRES Paralelo con OpenMP

Se paralizaron los bucles más costosos usando OpenMP.

Se utilizaron **4 hilos**, principalmente en:

- multiplicación matriz-vector,
- cálculo del residual,
- actualización de la solución.

A diferencia de LU, muchas operaciones dentro de GMRES son independientes y pueden ejecutarse en paralelo más fácilmente.

---

## ¿Qué tipo de matrices se usaron?

Se generaron matrices **diagonalmente dominantes** de forma aleatoria con semilla fija (`srand(42)`), lo que garantiza:

- **Solución única**
- **Mayor estabilidad numérica**
- **Resultados reproducibles**

Los tamaños evaluados fueron:

- N = 500
- N = 1000
- N = 2000

---

## Resultados

| N    | LU (s) | GMRES Serial (s) | GMRES OpenMP (s) |
|------|--------|------------------|------------------|
| 500  | --     | --               | --               |
| 1000 | --     | --               | --               |
| 2000 | --     | --               | --               |

> Los tiempos reales se generan automáticamente al ejecutar el programa.

---

## Observaciones

- LU produce resultados precisos, pero el tiempo de ejecución aumenta bastante con matrices grandes.
- GMRES requiere varias iteraciones, pero utiliza menos recursos.
- OpenMP mejora el rendimiento del método iterativo al distribuir trabajo entre varios hilos.
- Para tamaños pequeños, la mejora paralela puede ser baja debido al costo de sincronización de los hilos.

---

## Estructura del proyecto

```text
LU-GMRES/
│
├── src/
│   ├── lu.c                    # Implementación de LU
│   ├── gmres.c                 # Implementación simplificada de GMRES
│   ├── matrix_utils.c          # Funciones auxiliares para matrices
│   ├── benchmark.c             # Guardar tiempos y resultados
│   └── main.c                  # Ejecuta las pruebas principales
│
├── include/
│   ├── lu.h
│   ├── gmres.h
│   ├── matrix_utils.h
│   └── benchmark.h
│
├── data/
│   ├── matrices_pequenas/
│   ├── matrices_medianas/
│   └── matrices_grandes/
│
├── results/
│   ├── tiempos.csv             # Tiempos de ejecución
│   ├── speedup.csv             # Speedup paralelo
│   └── iteraciones.csv         # Iteraciones de GMRES
│
├── plots/
│   ├── graficas.py             # Generación de gráficas
│   └── imagenes/
│
├── Makefile                    # Compilación automática
└── README.md