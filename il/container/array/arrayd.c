#include "arrayd.h"

#include <stdlib.h>
#include <assert.h>

struct arrayd_t {
    double *data;
    int size;
    int capacity;
};

arrayd *arrayd_new() {
    arrayd *v = malloc(sizeof(arrayd));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void arrayd_delete(arrayd *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

bool arrayd_empty(arrayd *v) {
    return v->size == 0;
}

int arrayd_size(arrayd *v) {
    return v->size;
}

void _arrayd_increase_capacity(arrayd* v, int r) {
    assert(v->capacity < r);
    double *new_data = malloc(r * sizeof(double));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

void arrayd_resize(arrayd* v, int n) {
    if (n > v->capacity) {
        _arrayd_increase_capacity(v, n);
    }
    v->size = n;
}

void arrayd_reserve(arrayd* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _arrayd_increase_capacity(v, r);
    }
}

double arrayd_get(arrayd *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

void arrayd_set(arrayd *v, int i, double x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

void arrayd_swap(arrayd *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    double x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

void arrayd_push_back(arrayd *v, double x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _arrayd_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

double arrayd_pop_back(arrayd *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

double *arrayd_data(arrayd *v) {
    return v->data;
}