#ifndef IL_ARRAYB_H
#define IL_ARRAYB_H

#include <stdbool.h>

typedef struct arrayb_t arrayb;

arrayb *arrayb_new();
void arrayb_delete(arrayb *v);

bool arrayb_empty(arrayb *v);
int arrayb_size(arrayb *v);
void arrayb_resize(arrayb *v, int n);
void arrayb_reserve(arrayb *v, int r);
bool arrayb_get(arrayb *v, int i);
void arrayb_set(arrayb *v, int i, bool x);
void arrayb_swap(arrayb *v, int i, int j);
void arrayb_push_back(arrayb *v, bool x);
bool arrayb_pop_back(arrayb *v);
bool *arrayb_data(arrayb *v);

#endif //IL_ARRAYB_H
