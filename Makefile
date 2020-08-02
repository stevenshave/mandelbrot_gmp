mandelbrot_gmp: mandelbrot_gmp.o
	g++ -o mandelbrot_gmp mandelbrot_gmp.o -lgmpxx -lgmp -O3 -std=c++14 -march=native -funroll-all-loops

mandelbrot_gmp.o: mandelbrot_gmp.cpp linspace.hpp
	g++ -c mandelbrot_gmp.cpp -O3 -std=c++14 -march=native -funroll-all-loops

all: mandelbrot_gmp
	@echo "Done"

clean:
	rm -f *.o mandelbrot_gmp
