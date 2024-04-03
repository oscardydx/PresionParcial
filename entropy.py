import matplotlib.pyplot as plt
import numpy as np
from scipy.optimize import curve_fit
from sklearn.metrics import r2_score

# Maximum entropy for 64 states
max_entropy = 4;

# Get entropy data
Entropy_data = np.genfromtxt("entropy.txt", delimiter = "\t")

# Array to store time and entropy
time1 = Entropy_data[:,0]
entropy = Entropy_data[:,1]

# Plotting entropy as a function of time
plt.figure()
plt.plot(time1, entropy, label = 'Datos simulación')
plt.xlabel('Tiempo')
plt.ylabel('Entropía')
plt.title('Entropía en función del tiempo')
plt.grid(True)

# Save plot as a .png file
plt.savefig('entropia_tiempo.png')


#####################################
# Get drop size data
Drop_size_data = np.genfromtxt("drop_size.txt", delimiter = "\t")

# Array to store time and drop size
time2 = Drop_size_data[:,0]
drop_size = Drop_size_data[:,1]



# Plotting drop size as a function of time
plt.figure()
plt.plot(time2, drop_size, label='Datos simulación')
plt.xlabel('Tiempo')
plt.ylabel('Tamaño de la gota')
plt.title('Tamaño de la gota en el tiempo')
plt.grid(True)
plt.legend()

#Chek index
Index = np.where((entropy >= max_entropy))[0]

if len(Index > 0):
    # Time for max entropy
    equilibrium_time = Index[0]

    # Time and drop size array for fit (before equilibrium)
    time_fit = time2[:equilibrium_time + 1]
    drop_size2 = drop_size[:equilibrium_time + 1]

    # Square root function to fit
    def root_func(t, a, c):
        return a * np.sqrt(t) + c

    # Curve fit
    drop_size_fit, drop_size_cov = curve_fit(root_func, time_fit, drop_size2)

    # Get fit parameter
    a_fit, c_fit = drop_size_fit

    # Drop size fit
    drop_size_fit_curve = root_func(time_fit, *drop_size_fit)

    r_squared2 = r2_score(drop_size2, drop_size_fit_curve)

    plt.plot(time_fit, drop_size_fit_curve, 'r--', label='Ajuste: $R^2$=%5.3f' % (r_squared2))
    plt.legend()
else:
    print("No se alcanza el equilibrio ajustar parametros para mejor simulacion")

# Save plot as a .png file
plt.savefig('tamaño_tiempo.png')


#####################################
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
plt.plot(time3 , counts, label='Datos simulación')
plt.plot(time3, count_fit, 'r--', label=f'Ajuste exponencial ($\\tau$ = {tau_fit:.0f}): $R^2$={r_squared3:.3f}')
plt.xlabel('Tiempo')
plt.ylabel('# de párticulas')
plt.title('# de párticulas en el tiempo')
plt.legend()
plt.grid(True)

# Save plot as a .png file
plt.savefig('cuentas_tiempo.png')


#####################################

try:
    Latsize_data = np.genfromtxt("latsize.txt", delimiter="\t")
    if len(Latsize_data) == 0:
        print("No se alcanza el tiempo de equilibrio para los parametros dados.")

        plt.figure()
        plt.xlabel('Área del contenedor')
        plt.ylabel('Tiempo de equilibrio')
        plt.title('Tiempo de equilibrio para diferentes contenedores')
        plt.grid(True)
        plt.savefig('tiempo_area.png')
    else:
        # Continuar con el resto del código
        # Separate data into arrays
        latsize = Latsize_data[:,0]
        equilibrium_times_arr = Latsize_data[:,1]

        # Linear function to fit
        def linear_func(Size, m, b):
            return m * Size + b

        # Curve fit
        equilibrium_fit, _ = curve_fit(linear_func, latsize, equilibrium_times_arr)

        # Get fit parameters
        m_fit, b_fit = equilibrium_fit

        # Equilibrium time fit
        equilibrium_fit_curve = linear_func(latsize, *equilibrium_fit)

        # Calculate R^2
        r_squared4 = r2_score(equilibrium_times_arr, equilibrium_fit_curve)

        # Plot equilibrium time as a function of container area
        plt.figure()
        plt.plot(latsize , equilibrium_times_arr, 'o', markersize=3, label='Datos simulación')
        plt.plot(latsize, equilibrium_fit_curve, 'r--', label='Ajuste lineal: $R^2$=%5.3f' % (r_squared4))
        plt.xlabel('Área del contenedor')
        plt.ylabel('Tiempo de equilibrio')
        plt.title('Tiempo de equilibrio para diferentes contenedores')
        plt.legend()
        plt.grid(True)
        # Save plot as a .png file
        plt.savefig('tiempo_area.png')
except Exception as e:
    # Manejar cualquier otro tipo de excepción que ocurra durante la ejecución del código
    print("Error:", e)

