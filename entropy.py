import matplotlib.pyplot as plt

# Listas para almacenar el tiempo y la entropía
tiempo = []
entropia = []

# Leer los datos del archivo entropy.txt
with open('entropy.txt', 'r') as file:
    for line in file:
        # Dividir la línea en valores individuales utilizando tabulaciones como delimitador
        values = line.strip().split('\t')
        
        # Verificar si hay suficientes valores en la línea
        if len(values) == 2:
            # Intentar convertir los valores a números flotantes
            try:
                t, s = map(float, values)
                tiempo.append(int(t))  # Convertir el tiempo a entero
                entropia.append(s)
            except ValueError:
                # Ignorar la línea si no se pueden convertir los valores a números flotantes
                pass

# Graficar la entropía en función del tiempo
plt.plot(tiempo, entropia)
plt.xlabel('Tiempo')
plt.ylabel('Entropía')
plt.title('Entropía en función del tiempo')
plt.grid(True)

# Guardar la gráfica en un archivo .png
plt.savefig('entropia_tiempo.png')


