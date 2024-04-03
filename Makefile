SHELL:=/bin/bash

all: entropia_tiempo.png tamaño_tiempo.png cuentas_tiempo.png tiempo_area.png

%.x: %.o entropy.o functions.o
	g++ $^ -o $@

test.x: test.o functions.o input.txt
	g++ $$(pkg-config --cflags) $$(pkg-config --libs-only-L catch2) $^ -o $@ -l Catch2Main -l Catch2

test: test.x
	./test.x

%.o: %.cpp
	g++ -c $<

%.txt: %.x
	./entropy.x

gprof: entropy.cpp functions.cpp input.txt
	g++ -Wall -pg -g entropy.cpp functions.cpp -o test_gprof
	./test_gprof
	gprof test_gprof gmon.out > gprof-report.txt

cachegrind: entropy.cpp functions.cpp input.txt
	g++ entropy.cpp functions.cpp -o cachegrind
	valgrind --tool=cachegrind ./cachegrind
	cg_annotate --auto=yes cachegrind.out.* > cachegrind-report.txt

memcheck: entropy.cpp functions.cpp input.txt
	g++ entropy.cpp functions.cpp -o memcheck
	valgrind --tool=memcheck --leak-check=yes ./memcheck

tiempos: entropy_prueba.cpp functions.cpp 
	g++ -O0 entropy_prueba.cpp functions.cpp -o script_O0
	for nmol in 200 500 1000; do echo "nmol: $$nmol"; ./script_O0 $$nmol 20000 O0; done 
	for step in 20000 50000 100000; do echo "step: $$step"; ./script_O0 1000 $$step O0; done 
	g++ -O3 entropy_prueba.cpp functions.cpp -o script_O3
	for nmol in 200 500 1000; do echo "nmol: $$nmol"; ./script_O3 $$nmol 20000 O3; done 
	for step in 20000 50000 100000; do echo "step: $$step"; ./script_O3 1000 $$step O3; done 

entropia_tiempo.png: entropy.py entropy.txt
	python entropy.py


tamaño_tiempo.png: entropy.py drop_size.txt
	python entropy.py

clean:
	rm -f *.o *.x *.out *.png cachegrind.out.* cachegrind test_gprof memcheck counts.txt drop_size.txt entropy.txt fits.txt latsize.txt gprof-report.txt cachegrind-report.txt
	rm -f scriptO0_Nmol.txt scriptO0_Step.txt scriptO3_Nmol.txt scriptO3_Step.txt script_O0 script_O3 BanderaO0.txt BanderaO3.txt