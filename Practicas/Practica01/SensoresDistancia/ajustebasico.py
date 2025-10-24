import numpy as np
import matplotlib.pyplot as plt

# Cargar datos desde CSV (ignorando el encabezado)
data = np.loadtxt(
    "/home/fidel/ConstruccionRobotsMoviles/Practicas/Practica01/SensoresDistancia/datosSensorDerecho.csv",
    delimiter=",",
    skiprows=1,
)

distancia = data[:, 0]
voltaje = data[:, 1]

# Calcular el inverso del voltaje
invV = 1 / voltaje

# Ajuste lineal: d = m*(1/V) + c
coef = np.polyfit(invV, distancia, 1)
m, c = coef
print(f"Modelo: d = {m:.4f}*(1/V) + {c:.4f}")

# Calcular predicciones
distancia_pred = m * invV + c

# Calcular R² (bondad de ajuste)
ss_res = np.sum((distancia - distancia_pred) ** 2)
ss_tot = np.sum((distancia - np.mean(distancia)) ** 2)
r2 = 1 - (ss_res / ss_tot)
print(f"Coeficiente de determinación R² = {r2:.4f}")

# Graficar
plt.scatter(voltaje, distancia, color="blue", label="Datos medidos")
voltaje_fit = np.linspace(min(voltaje), max(voltaje), 200)
distancia_fit = m * (1 / voltaje_fit) + c
plt.plot(voltaje_fit, distancia_fit, "r-", label="Ajuste 1/V")

plt.xlabel("Voltaje (V)")
plt.ylabel("Distancia (cm)")
plt.title("Calibración sensor Sharp GP2Y0A41SK0F")
plt.legend()
plt.grid(True)
plt.show()
