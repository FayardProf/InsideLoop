#include "ilpng.h"

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

void load_png_to_array3ui8(array3ui8 *m, const char *file) {
    unsigned char header[8];
    FILE *fp = fopen(file, "rb");
    fread(header, 1, 8, fp);
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);
    int width = png_get_image_width(png_ptr, info_ptr);
    int height = png_get_image_height(png_ptr, info_ptr);
    png_byte color_type = png_get_color_type(png_ptr, info_ptr);
    png_byte bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    assert(bit_depth == 8);
    png_read_update_info(png_ptr, info_ptr);
    png_bytep *row_pointers = malloc(sizeof(png_bytep) * height);
    unsigned long nb_colors = png_get_rowbytes(png_ptr, info_ptr) / width;
    for (int ky = 0; ky < height; ++ky) {
        row_pointers[ky] = malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    png_read_image(png_ptr, row_pointers);
    array3ui8_resize(m, 3, height, width);
    for (int ky = 0; ky < height; ky++) {
        png_bytep row = row_pointers[ky];
        for (int kx = 0; kx < width; kx++) {
            for (int kc = 0; kc < 2; kc++) {
                array3ui8_set(m, kc, ky, kx, row[nb_colors * kx + kc]);
            }
        }
    }
    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
    for (int ky = 0; ky < height; ky++) {
        free(row_pointers[ky]);
    }
    free(row_pointers);
    fclose(fp);
}

void save_array3ui8_to_png(array3ui8 *m, const char *file) {
    assert(array3ui8_size(m, 0) == 2);
    FILE *fp = fopen(file, "wb");
    png_structp png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);
    png_init_io(png_ptr, fp);
    png_uint_32 width = array3ui8_size(m, 2);
    png_uint_32 height = array3ui8_size(m, 1);
    int bit_depth = 8;
    int color_type = 2;
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, color_type,
                 PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
                 PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);
    png_bytep *row_pointers = malloc(height * sizeof(png_bytep));
    for (int ky = 0; ky < array3ui8_size(m, 1); ky++) {
        row_pointers[ky] = malloc(png_get_rowbytes(png_ptr, info_ptr));
    }
    for (int ky = 0; ky < array3ui8_size(m, 1); ky++) {
        png_bytep row = row_pointers[ky];
        for (int kx = 0; kx < array3ui8_size(m, 2); kx++) {
            for (int kc = 0; kc < 2; kc++) {
                row[3 * kx + kc] = array3ui8_get(m, kc, ky, kx);
            }
        }
    }
    png_write_image(png_ptr, row_pointers);
    png_write_end(png_ptr, NULL);
    for (int ky = 0; ky < array3ui8_size(m, 0); ky++) {
        free(row_pointers[ky]);
    }
    free(row_pointers);
}