#!/usr/bin/env python3
import serial
import threading
import sys
import readline

# Parámetros: puerto y baud
if len(sys.argv) < 3:
    print("Uso: python3 monitor_serial.py <PUERTO> <BAUD>")
    sys.exit(1)

PORT = sys.argv[1]
BAUD = int(sys.argv[2])


# ======================
# Función para leer del Arduino
# ======================
def read_from_serial(ser):
    while True:
        try:
            line = ser.readline().decode("utf-8", errors="ignore").rstrip()
            if line:
                # Borra la línea actual de entrada, imprime el mensaje y vuelve a mostrar el prompt
                sys.stdout.write(
                    "\r" + " " * (len(readline.get_line_buffer()) + 2) + "\r"
                )
                print(line)
                sys.stdout.write("> " + readline.get_line_buffer())
                sys.stdout.flush()
        except:
            break


# ======================
# Abrir puerto serial
# ======================
try:
    ser = serial.Serial(PORT, BAUD, timeout=0.1)
except serial.SerialException:
    print(f"No se pudo abrir {PORT}")
    sys.exit(1)

# ======================
# Hilo de lectura
# ======================
thread = threading.Thread(target=read_from_serial, args=(ser,), daemon=True)
thread.start()

# ======================
# Loop principal para escribir
# ======================
try:
    while True:
        cmd = input("> ")
        ser.write((cmd + "\n").encode("utf-8"))
except KeyboardInterrupt:
    print("\nCerrando monitor serial...")
    ser.close()
    sys.exit(0)
