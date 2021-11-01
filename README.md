# InsideLoop

To plot the mandelbrot set:
- `gcc -std=c99 -O3 -DNDEBUG -I. -lpng main.c benchmark/mandelbrot.c il/io/to_png.c -o main`
- `clang -std=c99 -O3 -DNDEBUG -I. -lpng main.c benchmark/mandelbrot.c il/io/to_png.c -o main`
- `icc -std=c99 -O3 -DNDEBUG -xHost -qopenmp-simd -I. -L/usr/local/lib -lpng main.c benchmark/mandelbrot.c il/io/to_png.c -o main`
You should get a time of 20s with gcc and clang and 5s with icc as this compiler is able to vectorize the code with OpenMP.