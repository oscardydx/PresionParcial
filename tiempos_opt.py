import matplotlib.pyplot as plt
import numpy as np

flagO0_data = np.genfromtxt("BanderaO0.txt", delimiter = "\t")

Nmol_O0 = flagO0_data[:5,0]
t1_O0 = flagO0_data[:5,2]

Nsteps_O0 = flagO0_data[5:,1]
t2_O0 = flagO0_data[5:,2]


flagO3_data = np.genfromtxt("BanderaO3.txt", delimiter = "\t")

Nmol_O3 = flagO3_data[:5,0]
t1_O3 = flagO3_data[:5,2]

Nsteps_O3 = flagO3_data[5:,1]
t2_O3 = flagO3_data[5:,2]

plt.figure()
plt.plot(Nmol_O0, t1_O0,'o', linestyle='-', markersize=3, label = 'Optimizacion -O0')
plt.plot(Nmol_O3, t1_O3,'o', linestyle='-', markersize=3, label = 'Optimizacion -O3')
plt.xlabel('Numero de particulas')
plt.ylabel('Tiempo de computo (s)')
plt.title('Tiempo de computo variando el numero de particulas')
plt.grid(True)
plt.legend()

# Save plot as a .png file
plt.savefig('tiempo_nmol.png')

plt.figure()
plt.plot(Nsteps_O0, t2_O0, 'o', linestyle='-', markersize=3, label = 'Optimizacion -O0')
plt.plot(Nsteps_O3, t2_O3,'o', linestyle='-', markersize=3, label = 'Optimizacion -O3')
plt.xlabel('Numero de pasos (tiempo)')
plt.ylabel('Tiempo de computo (s)')
plt.title('Tiempo de computo variando el numero de pasos')
plt.grid(True)
plt.legend()

# Save plot as a .png file
plt.savefig('tiempo_nsteps.png')