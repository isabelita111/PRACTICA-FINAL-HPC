import matplotlib.pyplot as plt

# =========================
# DATOS
# =========================

pruebas = [1, 2, 3]

jacobi = [14, 10, 8]

gauss = [6, 5, 4]



plt.figure(figsize=(8,5))



plt.plot(
    pruebas,
    jacobi,
    marker='o',
    label='Jacobi'
)



plt.plot(
    pruebas,
    gauss,
    marker='o',
    label='Gauss-Seidel'
)



plt.title(
    "Jacobi vs Gauss-Seidel"
)


plt.xlabel(
    "Pruebas"
)

plt.ylabel(
    "Iteraciones"
)



plt.legend()



plt.grid(True)



plt.savefig(
    "plots/imagenes/comparacion_iteraciones.png"
)



plt.show()