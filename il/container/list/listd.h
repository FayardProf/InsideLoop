#ifndef IL_LISTD_H
#define IL_LISTD_H

#include <stdbool.h>

typedef struct noded_t noded;
typedef struct listd_t listd;

listd *listd_new();
void listd_delete(listd *lst);

bool listd_empty(listd *lst);
int listd_size(listd *lst);
void listd_push_front(listd *lst, double x);
void listd_push_back(listd *lst, double x);
double listd_front(listd *lst);
double listd_back(listd *lst);
double listd_pop_front(listd *lst);
double listd_pop_back(listd *lst);
noded *listd_begin(listd *lst);
noded *listd_end(listd *lst);
noded *listd_rbegin(listd *lst);
noded *listd_rend(listd *lst);
noded *listd_next(noded *no);
noded *listd_previous(noded *no);
double listd_value(noded *no);
void listd_insert(listd *lst, noded *no, double x);
void listd_erase(listd *lst, noded *no);

#endif //IL_LISTD_H
