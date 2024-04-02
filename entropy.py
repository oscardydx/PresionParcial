import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score

# Get entropy data
Entropy_data = np.genfromtxt("entropy.txt", delimiter = "\t")

# Array to store time and entropy
time1 = Entropy_data[:,0]
entropy = Entropy_data[:,1]

max_entropy = 4;

equilibrium_time = np.where((entropy >= max_entropy))[0][0]


# Plotting entropy as a function of time
plt.figure()
plt.plot(time1, entropy)
plt.xlabel('Tiempo')
plt.ylabel('Entropía')
plt.title('Entropía en función del tiempo')
plt.grid(True)

# Save plot as a .png file
plt.savefig('Entropía_tiempo.png')


# Get drop size data
Drop_size_data = np.genfromtxt("drop_size.txt", delimiter = "\t")

# Array to store time and drop size
time2 = Drop_size_data[:,0]
drop_size = Drop_size_data[:,1]

# Time and drop size array for fit (before equilibrium)
time_fit = time2[:equilibrium_time + 1]
drop_size2 = drop_size[:equilibrium_time + 1]

# Square root function to fit
def root_func(t, A, b):
    return A * np.sqrt(t) + b

# Curve fit
drop_size_fit, drop_size_cov = curve_fit(root_func, time_fit, drop_size2)

# Get fit parameter
A_fit, b_fit = drop_size_fit

# Drop size fit
drop_size_fit_curve = root_func(time_fit, *drop_size_fit)

r_squared2 = r2_score(drop_size2, drop_size_fit_curve)


# Plotting drop size as a function of time
plt.figure()
plt.plot(time2, drop_size, label='Datos')
plt.plot(time_fit, drop_size_fit_curve, 'r--', label='Ajuste: $R^2$=%5.3f' % (r_squared2))
plt.xlabel('Tiempo')
plt.ylabel('Tamaño de gota')
plt.title('Tamaño de gota en el tiempo')
plt.grid(True)
plt.legend()

# Save plot as a .png file
plt.savefig('tamaño_tiempo.png')


# Get leak data
Leak_data = np.genfromtxt("counts.txt", delimiter = "\t")

# Array to store time and particle count
time3 = Leak_data[:,0]
counts = Leak_data[:,1]

# Exponencial function to fit
def exponential_func(t, A, tau):
    return A * np.exp(-t / tau)

# Curve fit
leak_fit, leak_cov = curve_fit(exponential_func, time3, counts)

# Get fit parameters
A_fit, tau_fit = leak_fit

# Particle count fit
count_fit = exponential_func(time3, *leak_fit)
#R^2
r_squared3 = r2_score(counts, count_fit)

# Plotting particle count as a function of time
plt.figure()
plt.plot(time3 , counts, label='Simulacion')
plt.plot(time3, count_fit, 'r--', label='Ajuste exponencial: $R^2$=%5.3f' % (r_squared3))
plt.xlabel('Tiempo')
plt.ylabel('# de párticulas')
plt.title('# de párticulas en el tiempo')
plt.legend()
plt.grid(True)

# Save plot as a .png file
plt.savefig('counts.png')
