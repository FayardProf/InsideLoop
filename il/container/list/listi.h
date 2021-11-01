#ifndef IL_LISTI_H
#define IL_LISTI_H

#include <stdbool.h>

typedef struct nodei_t nodei;
typedef struct listi_t listi;

listi *listi_new();
void listi_delete(listi *lst);

bool listi_empty(listi *lst);
int listi_size(listi *lst);
void listi_push_front(listi *lst, int x);
void listi_push_back(listi *lst, int x);
int listi_front(listi *lst);
int listi_back(listi *lst);
int listi_pop_front(listi *lst);
int listi_pop_back(listi *lst);
nodei *listi_begin(listi *lst);
nodei *listi_end(listi *lst);
nodei *listi_rbegin(listi *lst);
nodei *listi_rend(listi *lst);
nodei *listi_next(nodei *no);
nodei *listi_previous(nodei *no);
int listi_value(nodei *no);
void listi_insert(listi *lst, nodei *no, int x);
void listi_erase(listi *lst, nodei *no);

#endif //IL_LISTI_H
