#ifndef IL_ARRAYI_H
#define IL_ARRAYI_H

#include <stdbool.h>

typedef struct arrayi_t arrayi;

arrayi *arrayi_new();
void arrayi_delete(arrayi *v);

bool arrayi_empty(arrayi *v);
int arrayi_size(arrayi *v);
void arrayi_resize(arrayi* v, int n);
void arrayi_reserve(arrayi* v, int r);
int arrayi_get(arrayi *v, int i);
void arrayi_set(arrayi *v, int i, int x);
void arrayi_swap(arrayi *v, int i, int j);
void arrayi_push_back(arrayi *v, int x);
int arrayi_pop_back(arrayi *v);
int *arrayi_data(arrayi *v);

#endif //IL_ARRAYI_H
