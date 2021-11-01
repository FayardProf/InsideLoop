#ifndef IL_MANDELBROT_H
#define IL_MANDELBROT_H

#include "il.h"

// float x_left = -1.5;
// float x_right = 0.5;
// float y_bottom = -1.0;
// float y_top = 1.0;
// int depth = 255;
// int nx = 8000;
// int ny = 8000;
// array2ui8 *m = mandelbrot(x_left, x_right, y_bottom, y_top, depth, nx, ny);
// save_array2ui8_to_png(m, "mandelbrot.png");

array2ui8 *mandelbrot(float x_left, float x_right, float y_bottom, float y_top, int depth, int nx, int ny);
array3ui8 *mandelbrot_color(float x_left, float x_right, float y_bottom, float y_top, int depth, int nx, int ny);

#endif //IL_MANDELBROT_H
