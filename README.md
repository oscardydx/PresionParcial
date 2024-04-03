# PresionParcial
Trabajo academico computacional con el fin de estudiar la entropía.

# Ejecución

Programa normal: 
  make
  
Testing:
  make test

Reporte gprof:
 make gprof

Reporte cachegrind:
  make cachegrind

Valgrind:
  make memcheck

Tiempo en función del tamaño del sistema:
  make tiempos

Limpiar
  make clean

# Archivos
entropy.cpp: 
  funcion main, se lleva acabo la simulación

declarations.h: 
  declaración de funciones e incldes

particle.h: 
  declaración objeto particle

functions.cpp: 
  Implementación de las funciones para la simulación

test.cpp: 
  tests con catch2

entrpoy_prueba.cpp: 
  copia de entropy.cpp para medir el tiempo de ejecución con diferentes parametros

entropy.py: 
  gráficas y ajustes de los resultados principales de la simulación

tiempos_opt.py:
  gráficas del tiempo de computo a partir de los datos de entropy_prueba.cpp

