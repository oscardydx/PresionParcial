import matplotlib.pyplot as plt
import numpy as np

# Get entropy data
Entropy_data = np.genfromtxt("entropy.txt", delimiter = "\t")

# Array to store time and entropy
time = Entropy_data[:,0]
entropy = Entropy_data[:,1]

# Plotting entropy as a function of time
plt.figure()
plt.plot(time, entropy)
plt.xlabel('Tiempo')
plt.ylabel('Entropía')
plt.title('Entropía en función del tiempo')
plt.grid(True)

# Save plot as a .png file
plt.savefig('Entropía_tiempo.png')


# Get drop size data
Drop_size_data = np.genfromtxt("drop_size.txt", delimiter = "\t")

# Array to store time and drop size
time = Drop_size_data[:,0]
drop_size = Drop_size_data[:,1]

# Plotting drop size as a function of time
plt.figure()
plt.plot(time , drop_size)
plt.xlabel('Tiempo')
plt.ylabel('tamaño de gota')
plt.title('Tamaño de gota en el tiempo')
plt.grid(True)

# Save plot as a .png file
plt.savefig('tamaño_tiempo.png')


# Get leak data
Leak_data = np.genfromtxt("counts.txt", delimiter = "\t")

# Array to store time and particle count
time = Leak_data[:,0]
counts = Leak_data[:,1]

# Plotting drop size as a function of time
plt.figure()
plt.plot(time , counts)
plt.xlabel('Tiempo')
plt.ylabel('# de párticulas')
plt.title('# de párticulas en el tiempo')
plt.grid(True)

# Save plot as a .png file
plt.savefig('counts.png')
