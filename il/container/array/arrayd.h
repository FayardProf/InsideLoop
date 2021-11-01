#ifndef IL_ARRAYD_H
#define IL_ARRAYD_H

#include <stdbool.h>

typedef struct arrayd_t arrayd;

arrayd *arrayd_new();
void arrayd_delete(arrayd *v);

bool arrayd_empty(arrayd *v);
int arrayd_size(arrayd *v);
void arrayd_resize(arrayd *v, int n);
void arrayd_reserve(arrayd *v, int r);
double arrayd_get(arrayd *v, int i);
void arrayd_set(arrayd *v, int i, double x);
void arrayd_swap(arrayd *v, int i, int j);
void arrayd_push_back(arrayd *v, double x);
double arrayd_pop_back(arrayd *v);
double *arrayd_data(arrayd *v);

#endif //IL_ARRAYD_H
