#ifndef IL_ARRAY2UI8_H
#define IL_ARRAY2UI8_H

#include <stdint.h>
#include <stdbool.h>

typedef struct array2ui8_t array2ui8;

array2ui8 *array2ui8_new();
void array2ui8_delete(array2ui8 *m);

bool array2ui8_empty(array2ui8 *m);
int array2ui8_size(array2ui8 *m, int d);
int array2ui8_capacity(array2ui8 *m, int d);
void array2ui8_resize(array2ui8 *m, int n0, int n1);
void array2ui8_reserve(array2ui8 *m, int r0, int r1);
int8_t array2ui8_get(array2ui8 *m, int i0, int i1);
void array2ui8_set(array2ui8 *m, int i0, int i1, int8_t x);
int8_t *array2ui8_data(array2ui8 *m);

#endif //IL_ARRAY32UI8_H