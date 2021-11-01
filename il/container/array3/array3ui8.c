#include "array3ui8.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

struct array3ui8_t {
    uint8_t *data;
    int size[3];
    int capacity[3];
};

array3ui8 *array3ui8_new() {
    array3ui8 *m = malloc(sizeof(array3ui8));
    m->data = NULL;
    m->size[0] = 0;
    m->size[1] = 0;
    m->size[2] = 0;
    m->capacity[0] = 0;
    m->capacity[1] = 0;
    m->capacity[2] = 0;
    return m;
}

void array3ui8_delete(array3ui8 *m) {
    if (m->data != NULL) {
        free(m->data);
    }
    free(m);
}

int array3ui8_size(array3ui8 *m, int d) {
    assert(d == 0 || d == 1 || d == 2);
    return m->size[d];
}

int array3ui8_capacity(array3ui8 *m, int d) {
    assert(d == 0 || d == 1 || d == 2);
    return m->capacity[d];  
}

void array3ui8_resize(array3ui8 *m, int n0, int n1, int n2) {
    assert(n0 >= 0);
    assert(n1 >= 0);
    assert(n2 >= 0);
    int n0_capacity = array3ui8_capacity(m, 0);
    int n1_capacity = array3ui8_capacity(m, 1);
    int n2_capacity = array3ui8_capacity(m, 2);
    if (n0 > n0_capacity || n1 > n1_capacity || n2 > n2_capacity) {
        int n0_old = array3ui8_size(m, 0);
        int n1_old = array3ui8_size(m, 1);
        int n2_old = array3ui8_size(m, 2);
        uint8_t *new_data = malloc(n0 * n1 * n2 * sizeof(uint8_t));
        if (m->data != NULL) {
            for (int i0 = 0; i0 < n0_old; i0++) {
                for (int i1 = 0; i1 < n1_old; i1++) {
                    for (int i2 = 0; i2 < n2_old; i2++) {
                        new_data[(i0 * n1 + i1) * n2 + i2] = m->data[(i0 * m->capacity[1] + i1) * m->capacity[2] + i2];
                    }
                }
            }
        }
        m->capacity[0] = n0;
        m->capacity[1] = n1;
        m->capacity[2] = n2;
        m->data = new_data;
    }
    m->size[0] = n0;
    m->size[1] = n1;
    m->size[2] = n1;
}

int8_t array3ui8_get(array3ui8 *m, int i0, int i1, int i2) {
    assert(i0 >= 0 && i0 < m->size[0]);
    assert(i1 >= 0 && i1 < m->size[1]);
    assert(i2 >= 0 && i2 < m->size[2]);
    return m->data[(i0 * m->capacity[1] + i1) * m->capacity[2] + i2];
}

void array3ui8_set(array3ui8 *m, int i0, int i1, int i2, int8_t x) {
    assert(i0 >= 0 && i0 < m->size[0]);
    assert(i1 >= 0 && i1 < m->size[1]);
    assert(i2 >= 0 && i2 < m->size[2]);
    m->data[(i0 * m->capacity[1] + i1) * m->capacity[2] + i2] = x;
}

