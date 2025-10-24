import numpy as np
import matplotlib.pyplot as plt

# -----------------------------
# CONFIGURACIÓN DEL USUARIO
# -----------------------------
archivo_csv = "/home/fidel/ConstruccionRobotsMoviles/Practicas/Practica01/SensoresDistancia/datosSensorDerecho.csv"  # ruta a tu CSV
grado_polinomio = 6  # <--- Cambia solo este valor

# -----------------------------
# Cargar datos
# -----------------------------
data = np.loadtxt(archivo_csv, delimiter=",", skiprows=1)
distancia = data[:, 0]
voltaje = data[:, 1]

# -----------------------------
# Ajuste polinomial
# -----------------------------
coef = np.polyfit(voltaje, distancia, grado_polinomio)
polinomio = np.poly1d(coef)  # facilita calcular valores y graficar

# Imprimir ecuación
ecuacion = " + ".join(
    [f"{coef[i]:.4f}*V^{grado_polinomio - i}" for i in range(len(coef) - 1)]
)
ecuacion += f" + {coef[-1]:.4f}"
print(f"Modelo polinomial grado {grado_polinomio}: d = {ecuacion}")

# -----------------------------
# Calcular predicciones y R²
# -----------------------------
distancia_pred = polinomio(voltaje)
ss_res = np.sum((distancia - distancia_pred) ** 2)
ss_tot = np.sum((distancia - np.mean(distancia)) ** 2)
r2 = 1 - (ss_res / ss_tot)
print(f"Coeficiente de determinación R² = {r2:.4f}")

# -----------------------------
# Graficar
# -----------------------------
plt.scatter(voltaje, distancia, color="blue", label="Datos medidos")
voltaje_fit = np.linspace(min(voltaje), max(voltaje), 300)
plt.plot(
    voltaje_fit,
    polinomio(voltaje_fit),
    "r--",
    label=f"Ajuste polinomial grado {grado_polinomio}",
)
plt.xlabel("Voltaje (V)")
plt.ylabel("Distancia (cm)")
plt.title("Calibración Sensor IR")
plt.legend()
plt.grid(True)
plt.show()
