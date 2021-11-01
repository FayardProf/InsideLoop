#ifndef IL_ARRAY2D_H
#define IL_ARRAY2D_H

#include <stdbool.h>

typedef struct array2d_t array2d;

array2d *array2d_new();
void array2d_delete(array2d *m);

bool array2d_empty(array2d *m);
int array2d_size(array2d *m);
void array2d_resize(array2d *m, int n0, int n1);
void array2d_reserve(array2d *m, int r0, int r1);
double array2d_get(array2d *m, int i0, int i1);
void array2d_set(array2d *m, int i0, int i1, double x);
double *array2d_data(array2d *m);

#endif //IL_ARRAY2D_H