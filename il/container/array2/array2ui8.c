#include "array2ui8.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

struct array2ui8_t {
    uint8_t *data;
    int size[2];
    int capacity[2];
};

array2ui8 *array2ui8_new() {
    array2ui8 *m = malloc(sizeof(array2ui8));
    m->data = NULL;
    m->size[0] = 0;
	m->size[1] = 0;
	m->capacity[0] = 0;
    m->capacity[1] = 0;
    return m;
}

void array2ui8_delete(array2ui8 *m) {
    if (m->data != NULL) {
        free(m->data);
    }
    free(m);
}

int array2ui8_size(array2ui8 *m, int d) {
    assert(d == 0 || d == 1);
    return m->size[d];
}

int array2ui8_capacity(array2ui8 *m, int d) {
    assert(d == 0 || d == 1);
    return m->capacity[d];  
}

void array2ui8_resize(array2ui8 *m, int n0, int n1) {
    assert(n0 >= 0);
    assert(n1 >= 0);
    int n0_capacity = array2ui8_capacity(m, 0);
    int n1_capacity = array2ui8_capacity(m, 1);
    if (n0 > n0_capacity || n1 > n1_capacity) {
        int n0_old = array2ui8_size(m, 0);
        int n1_old = array2ui8_size(m, 1);
        uint8_t *new_data = malloc(n0 * n1 * sizeof(uint8_t));
        if (m->data != NULL) {
            for (int i0 = 0; i0 < n0_old; i0++) {
                for (int i1 = 0; i1 < n1_old; i1++) {
                    new_data[i0 * n1 + i1] = m->data[i0 * m->capacity[1] + i1];
                }
            }
        }
        m->capacity[0] = n0;
        m->capacity[1] = n1;
        m->data = new_data;
    }
    m->size[0] = n0;
    m->size[1] = n1;
}

int8_t array2ui8_get(array2ui8 *m, int i0, int i1) {
    return m->data[i0 * m->capacity[1] + i1];
}

void array2ui8_set(array2ui8 *m, int i0, int i1, int8_t x) {
    assert(i0 >= 0 && i0 < m->capacity[0]);
    assert(i1 >= 0 && i1 < m->capacity[1]);
    m->data[i0 * m->capacity[1] + i1] = x;
}

