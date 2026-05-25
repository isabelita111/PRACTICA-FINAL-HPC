import pandas as pd
import matplotlib.pyplot as plt

datos = pd.read_csv("results/tiempos.csv")

lu = datos[datos["metodo"] == "LU"]
serial = datos[datos["metodo"] == "GMRES_SERIAL"]
openmp = datos[datos["metodo"] == "GMRES_OPENMP"]

# Comparacion LU vs GMRES

plt.figure(figsize=(8,5))

plt.plot(lu["n"], lu["tiempo"], marker='o', label="LU")
plt.plot(serial["n"], serial["tiempo"], marker='o', label="GMRES")

plt.xlabel("Tamano matriz")
plt.ylabel("Tiempo")
plt.title("LU vs GMRES")
plt.legend()

plt.savefig("plots/imagenes/lu_vs_gmres.png")

# OpenMP

plt.figure(figsize=(8,5))

plt.plot(openmp["n"], openmp["tiempo"], marker='o', label="GMRES OpenMP")

plt.xlabel("Tamano matriz")
plt.ylabel("Tiempo")
plt.title("GMRES con OpenMP")

plt.legend()

plt.savefig("plots/imagenes/openmp.png")

plt.show()