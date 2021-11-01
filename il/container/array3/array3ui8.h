#ifndef IL_ARRAY3UI8_H
#define IL_ARRAY3UI8_H

#include <stdint.h>
#include <stdbool.h>

typedef struct array3ui8_t array3ui8;

array3ui8 *array3ui8_new();
void array3ui8_delete(array3ui8 *a);

bool array3ui8_empty(array3ui8 *a);
int array3ui8_size(array3ui8 *a, int d);
int array3ui8_capacity(array3ui8 *a, int d);
void array3ui8_resize(array3ui8 *a, int n0, int n1, int n2);
void array3ui8_reserve(array3ui8 *a, int r0, int r1, int r2);
int8_t array3ui8_get(array3ui8 *a, int i0, int i1, int i2);
void array3ui8_set(array3ui8 *a, int i0, int i1, int i2, int8_t x);
int8_t *array3ui8_data(array3ui8 *a);

#endif //IL_ARRAY3UI8_H