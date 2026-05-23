import pandas as pd
import matplotlib.pyplot as plt
import os

# Crear carpeta de graficas si no existe
os.makedirs("plots", exist_ok=True)

# Leer datos
tiempos  = pd.read_csv("results/tiempos.csv")
speedup  = pd.read_csv("results/speedup.csv")

# Grafica 1: Tiempos serial vs paralelo
plt.figure(figsize=(8, 5))
plt.plot(tiempos["matrix_size"], tiempos["time_serial"],   marker="o", label="Serial")
plt.plot(tiempos["matrix_size"], tiempos["time_parallel"], marker="s", label="Paralelo")
plt.xlabel("Tamanio de la matriz (N)")
plt.ylabel("Tiempo (segundos)")
plt.title("Tiempo de ejecucion: Serial vs Paralelo")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("plots/tiempos.png")
plt.close()
print("Grafica guardada: plots/tiempos.png")

# Grafica 2: Speedup
plt.figure(figsize=(8, 5))
plt.plot(speedup["matrix_size"], speedup["speedup"], marker="o", color="green", label="Speedup")
plt.axhline(y=1, color="gray", linestyle="--", label="Speedup = 1 (sin mejora)")
plt.xlabel("Tamanio de la matriz (N)")
plt.ylabel("Speedup")
plt.title("Speedup: Paralelo vs Serial")
plt.legend()
plt.grid(True)
plt.tight_layout()
plt.savefig("plots/speedup.png")
plt.close()
print("Grafica guardada: plots/speedup.png")