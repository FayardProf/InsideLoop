#include "mandelbrot.h"
#include "il/color/color.h"

array2ui8 *mandelbrot(float x_left, float x_right, float y_bottom, float y_top, int depth, int nx, int ny) {
    float dx = (x_right - x_left) / nx;
    float dy = (y_top - y_bottom) / ny;
    array2ui8 *m = array2ui8_new();
    array2ui8_resize(m, ny, nx);
    for (int ky = 0; ky < ny; ky++) {
        float y = y_top - ky * dy;
#pragma omp simd
        for (int kx = 0; kx < nx; kx++) {
            float x = x_left + kx * dx;
            float z_re = 0.0;
            float z_im = 0.0;
            int count = 0;
            while (count < depth) {
                if (z_re * z_re + z_im * z_im > 4.0) {
                    break;
                }
                float old_z_re = z_re;
                z_re = z_re * z_re - z_im * z_im + x;
                z_im = 2 * old_z_re * z_im + y;
                count++;
            }
            array2ui8_set(m, ky, kx, (uint8_t) (255 * (((float) count) / depth)));
        }
    }
    return m;
}

array3ui8 *mandelbrot_color(float x_left, float x_right, float y_bottom, float y_top, int max_iter, int nx, int ny) {
    float dx = (x_right - x_left) / nx;
    float dy = (y_top - y_bottom) / ny;
    array3ui8 *m = array3ui8_new();
    array3ui8_resize(m, 3, ny, nx);
    for (int ky = 0; ky < ny; ky++) {
        float y = y_top - ky * dy;
        for (int kx = 0; kx < nx; kx++) {
            float x = x_left + kx * dx;
            float z_re = 0.0;
            float z_im = 0.0;
            int count = 0;
            while (count < max_iter) {
                if (z_re * z_re + z_im * z_im > 4.0) {
                    break;
                }
                float old_z_re = z_re;
                z_re = z_re * z_re - z_im * z_im + x;
                z_im = 2 * old_z_re * z_im + y;
                count++;
            }
            hsvf color;
            color.h = (360.0f * count) / max_iter;
            color.s = 1.0f;
            color.v = count < max_iter ? 1.0f : 0.0f;
            rgbf rgb = rgbf_from_hsvf(color);
            array3ui8_set(m, 0, ky, kx, (int8_t) (255.0f * rgb.r));
            array3ui8_set(m, 1, ky, kx, (int8_t) (255.0f * rgb.g));
            array3ui8_set(m, 2, ky, kx, (int8_t) (255.0f * rgb.b));
        }
    }
    return m;
}