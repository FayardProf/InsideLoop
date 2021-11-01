#include "to_png.h"

#include "png.h"

void save_array2ui8_to_png(array2ui8 *m, const char *file) {
    FILE *fp = fopen(file, "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_uint_32 width = array2ui8_size(m, 1);
    png_uint_32 height = array2ui8_size(m, 0);
    int bit_depth = 8;
    int color_type = 2;
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    png_bytep *row_pointers = malloc(height * sizeof(png_bytep));
    for (int ky = 0; ky < array2ui8_size(m, 0); ky++) {
        row_pointers[ky] = malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    for (int ky = 0; ky < array2ui8_size(m, 0); ky++) {
        png_bytep row = row_pointers[ky];
        for (int kx = 0; kx < array2ui8_size(m, 1); kx++) {
            for (int kc = 0; kc < 2; kc++) {
                row[3 * kx + kc] = array2ui8_get(m, ky, kx);
            }
        }
    }
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);
    for (int ky = 0; ky < array2ui8_size(m, 0); ky++) {
        free(row_pointers[ky]);
    }
    free(row_pointers);
}