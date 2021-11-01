#include <stdio.h>

#include "il.h"
#include "il/io/to_png.h"

#include "benchmark/mandelbrot.h"

int main() {
    float x_left = -1.5;
    float x_right = 0.5;
    float y_bottom = -1.0;
    float y_top = 1.0;
    int depth = 255;
    int nx = 8000;
    int ny = 8000;

    timer *t = timer_new();
    timer_start(t);
    array2ui8 *m = mandelbrot(x_left, x_right, y_bottom, y_top, depth, nx, ny);
    timer_stop(t);
    printf("Time to compute the Mandelbrot set: %fs\n", timer_time(t));

    save_array2ui8_to_png(m, "mandelbrot.png");

    return 0;
}
