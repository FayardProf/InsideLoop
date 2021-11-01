#include "arrayi.h"

#include <stdlib.h>
#include <assert.h>

struct arrayi_t {
    int *data;
    int size;
    int capacity;
};

arrayi *arrayi_new() {
    arrayi *v = malloc(sizeof(arrayi));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void arrayi_delete(arrayi *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

bool arrayi_empty(arrayi *v) {
    return v->size == 0;
}

int arrayi_size(arrayi *v) {
    return v->size;
}

void _arrayi_increase_capacity(arrayi* v, int r) {
    assert(v->capacity < r);
    int *new_data = malloc(r * sizeof(int));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

void arrayi_resize(arrayi* v, int n) {
    if (n > v->capacity) {
        _arrayi_increase_capacity(v, n);
    }
    v->size = n;
}

void arrayi_reserve(arrayi* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _arrayi_increase_capacity(v, r);
    }
}

int arrayi_get(arrayi *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

void arrayi_set(arrayi *v, int i, int x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

void arrayi_swap(arrayi *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    int x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

void arrayi_push_back(arrayi *v, int x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _arrayi_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

int arrayi_pop_back(arrayi *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

int *arrayi_data(arrayi *v) {
    return v->data;
}