# InsideLoop

To plot the mandelbrot set:
- `gcc -std=c99 -O3 -DNDEBUG -I. -lpng main.c benchmark/mandelbrot.c il/io/ilpng.c il/color/color.c -o main`
- `clang -std=c99 -O3 -DNDEBUG -I. -lpng main.c benchmark/mandelbrot.c  il/io/ilpng.c il/color/color.c  -o main`