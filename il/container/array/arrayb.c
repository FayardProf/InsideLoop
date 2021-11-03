#include "arrayb.h"

#include <stdlib.h>
#include <assert.h>

struct arrayb_t {
    bool *data;
    int size;
    int capacity;
};

arrayb *arrayb_new() {
    arrayb *v = malloc(sizeof(arrayb));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

void arrayb_delete(arrayb *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

bool arrayb_empty(arrayb *v) {
    return v->size == 0;
}

int arrayb_size(arrayb *v) {
    return v->size;
}

void _arrayb_increase_capacity(arrayb* v, int r) {
    assert(v->capacity < r);
    bool *new_data = malloc(r * sizeof(bool));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

void arrayb_resize(arrayb* v, int n) {
    if (n > v->capacity) {
        _arrayb_increase_capacity(v, n);
    }
    v->size = n;
}

void arrayb_reserve(arrayb* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _arrayb_increase_capacity(v, r);
    }
}

bool arrayb_get(arrayb *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

void arrayb_set(arrayb *v, int i, bool x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

void arrayb_swap(arrayb *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    bool x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

void arrayb_push_back(arrayb *v, bool x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _arrayb_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

bool arrayb_pop_back(arrayb *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

bool *arrayb_data(arrayb *v) {
    return v->data;
}