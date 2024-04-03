SHELL:=/bin/bash

all: entropia_tiempo.png tamaño_tiempo.png cuentas_tiempo.png tiempo_area.png

%.x: %.o entropy.o functions.o
	g++ $^ -o $@

test.x: test.o functions.o
	g++ $$(pkg-config --cflags) $$(pkg-config --libs-only-L catch2) $^ -o $@ -l Catch2Main -l Catch2

test: test.x
	./test.x

%.o: %.cpp
	g++ -c $<

%.txt: %.x
	./entropy.x

gprof: entropy.cpp functions.cpp
	g++ -Wall -pg -g entropy.cpp functions.cpp -o test_gprof
	./test_gprof
	gprof test_gprof gmon.out > gprof-report.txt

cachegrind: entropy.cpp functions.cpp
	g++ entropy.cpp functions.cpp -o cachegrind
	valgrind --tool=cachegrind ./cachegrind
	cg_annotate --auto=yes cachegrind.out.* > cachegrind-report.txt

memcheck: entropy.cpp functions.cpp
	g++ entropy.cpp functions.cpp -o memcheck
	valgrind --tool=memcheck --leak-check=yes ./memcheck


entropia_tiempo.png: entropy.py entropy.txt
	python entropy.py


tamaño_tiempo.png: entropy.py drop_size.txt
	python entropy.py

clean:
	rm -f *.o *.x *.out *.png *.txt cachegrind.out.* cachegrind test_gprof memcheck