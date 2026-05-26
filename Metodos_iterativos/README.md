# Métodos Iterativos: Jacobi y Gauss-Seidel

Práctica Final

---

## ¿Cuál fue el problema?

El objetivo fue resolver sistemas de ecuaciones lineales de la forma **Ax = b**, donde A es una matriz cuadrada de tamaño N×N. Este tipo de problemas aparece en análisis numérico, computación científica, ingeniería y simulaciones matemáticas, especialmente cuando los sistemas son grandes y requieren métodos eficientes para aproximar soluciones.

Para resolver el problema se implementaron dos métodos iterativos distintos:

- **Jacobi**
- **Gauss-Seidel**

Además, se realizó una comparación entre ambos métodos analizando:

- convergencia,
- tiempos de ejecución,
- número de iteraciones,
- eficiencia computacional.

---

## ¿Qué se hizo?

Se implementaron dos pruebas principales utilizando métodos iterativos para aproximar la solución del sistema lineal.

### 1. Método de Jacobi

El método de Jacobi calcula una nueva aproximación utilizando únicamente los valores obtenidos en la iteración anterior.

En cada iteración:

- se calcula el nuevo valor de cada variable,
- se construye un nuevo vector solución,
- se calcula el error,
- y se verifica si el método converge.

Este método es sencillo de implementar, aunque normalmente necesita más iteraciones para alcanzar la solución.

---

### 2. Método de Gauss-Seidel

El método de Gauss-Seidel también resuelve el sistema de manera iterativa, pero utiliza inmediatamente los valores nuevos calculados durante la iteración actual.

Esto permite:

- reducir el número de iteraciones,
- acelerar la convergencia,
- mejorar el rendimiento.

A diferencia de Jacobi, este método aprovecha la información más reciente en cada paso del cálculo.

---

## ¿Qué tipo de matrices se usaron?

Se utilizaron matrices **diagonalmente dominantes**, ya que este tipo de matrices favorece la convergencia de los métodos iterativos.

Esto garantiza:

- mayor estabilidad numérica,
- convergencia correcta,
- soluciones más precisas.

La matriz utilizada fue:

```text
| 10   1   1 |
|  2  10   1 |
|  2   2  10 |
