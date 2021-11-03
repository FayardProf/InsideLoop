#ifndef IL_SETD_H
#define IL_SETD_H

#include <stdbool.h>

typedef struct setd_t setd;

setd *setd_new();
void setd_delete(setd *s);

bool setd_empty(setd *s);
bool setd_contains(setd *s, double x);
void setd_add(setd *s, double x);
void setd_remove(setd *s, double x);
int setd_search(setd *s, double x);
bool setd_found(int i);
int setd_add_at(setd *s, int i, double x);
void setd_remove_at(setd *s, int i);
int setd_begin(setd *s);
int setd_end(setd *s);
int setd_next(setd *s, int i);
double setd_value(setd *s, int i);

#endif //IL_SETD_H
