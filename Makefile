mandelbrot_gmp: mandelbrot_gmp.o
	g++ -g -o mandelbrot_gmp mandelbrot_gmp.o -lgmpxx -lgmp -O3 -std=c++14 -march=native -funroll-all-loops -fopenmp -lz

mandelbrot_gmp.o: mandelbrot_gmp.cpp linspace.hpp
	g++ -g -c mandelbrot_gmp.cpp -O3 -std=c++14 -march=native -funroll-all-loops -fopenmp -lz

buddhabrot: buddhabrot.o
	g++ -g -o buddhabrot buddhabrot.o -lgmpxx -lgmp -O3 -std=c++14 -march=native -funroll-all-loops -fopenmp -lz

buddhabrot.o: buddhabrot.cpp linspace.hpp
	g++ -g -c buddhabrot.cpp -O3 -std=c++14 -march=native -funroll-all-loops -fopenmp -lz

all: mandelbrot_gmp buddhabrot
	@echo "Done"

clean:
	rm -f *.o mandelbrot_gmp buddhabrot
