#ifndef IL_SETI_H
#define IL_SETI_H

#include <stdbool.h>

typedef struct seti_t seti;

seti *seti_new();
void seti_delete(seti *s);

bool seti_empty(seti *s);
bool seti_contains(seti *s, int x);
void seti_add(seti *s, int x);
void seti_remove(seti *s, int x);
int seti_search(seti *s, int x);
bool seti_found(int i);
int seti_add_at(seti *s, int i, int x);
void seti_remove_at(seti *s, int i);
int seti_begin(seti *s);
int seti_end(seti *s);
int seti_next(seti *s, int i);
int seti_value(seti *s, int i);

#endif //IL_SETI_H
