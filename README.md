# InsideLoop

To plot the mandelbrot set:
clang -O3 -DNDEBUG -I. -lpng main.c benchmark/mandelbrot.c il/io/to_png.c -o main
icc -std=c99 -O3 -DNDEBUG -xHost -qopenmp-simd -I. -L/usr/local/lib -lpng main.c benchmark/mandelbrot.c il/io/to_png.c -o main