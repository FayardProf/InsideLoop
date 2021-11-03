#include "seti.h"

#include <stdlib.h>
#include <assert.h>

#define IL_EMPTY 0
#define IL_TOMBSTONE 1
#define IL_OCCUPIED 2

typedef struct sbucketi_t sbucketi;

struct seti_t {
    sbucketi *bucket;
    int nb_elements;
    int nb_tombstones;
    int p;
};

struct sbucketi_t {
    uint8_t flag;
    int value;
};

unsigned int hashi(int x, int p) {
    unsigned int knuth = 2654435769;
    return (x * knuth) >> (32 - p);
}

seti *seti_new() {
    seti *s = malloc(sizeof(seti));
    s->bucket = NULL;
    s->nb_elements = 0;
    s->nb_tombstones = 0;
    s->p = -1;
    return s;
}

void seti_delete(seti *s) {
    if (s->bucket != NULL) {
        free(s->bucket);
    }
    free(s);
}

bool seti_empty(seti *s) {
    return s->nb_elements == 0;
}

int _seti_nb_buckets(int p) {
    return (p >= 0) ? (1 << p) : 0;
}

bool seti_contains(seti *s, int x) {
    return seti_search(s, x) >= 0;
}

void seti_add(seti *s, int x) {
    int i = seti_search(s, x);
    if (i < 0) {
        seti_add_at(s, i, x);
    }
}

// void seti_remove(seti *s, int x);

int seti_search(seti *s, int x) {
    if (s->p == -1) {
        return -1;
    }
    unsigned int mask = (1 << s->p) - 1;
    unsigned int i = hashi(x, s->p);
    int tombstone_i = -1;
    int delta_i = 1;
    while (true) {
        if (s->bucket[i].flag == IL_EMPTY) {
            return -(1 + (int) ((tombstone_i == -1) ? i : tombstone_i));
        } else if (s->bucket[i].flag == IL_TOMBSTONE) {
            tombstone_i = i;
        } else if (s->bucket[i].value == x) {
            return (int) i;
        }
        i += delta_i;
        i &= mask;
        delta_i++;
    }
}

bool seti_found(int i) {
    return i >= 0;
}

void _seti_reserve(seti *s, int p);

int seti_add_at(seti *s, int i, int x) {
    i = -(1 + i);
    int m = _seti_nb_buckets(s->p);
    if (4 * (s->nb_elements + 1) > 3 * m) {
        _seti_reserve(s, (s->p == -1) ? 1 : s->p + 1);
        int j = seti_search(s, x);
        i = - (1 + j);
    }
    s->bucket[i].flag = IL_OCCUPIED;
    s->bucket[i].value = x;
    s->nb_elements++;
    return i;
}

void _seti_reserve(seti *s, int p) {
    sbucketi *old_bucket = s->bucket;
    int old_m = _seti_nb_buckets(s->p);
    int m = _seti_nb_buckets(p);
    s->bucket = malloc(m * sizeof(sbucketi));
    for (int i = 0; i < m; i++) {
        s->bucket[i].flag = IL_EMPTY;
    }
    s->nb_elements = 0;
    s->nb_tombstones = 0;
    s->p = p;
    if (p >= 0) {
        for (int i = 0; i < old_m; i++) {
            if (old_bucket[i].flag != IL_EMPTY &&
                old_bucket[i].flag != IL_TOMBSTONE) {
                int new_i = seti_search(s, old_bucket[i].value);
                seti_add_at(s, new_i, old_bucket[i].value);
            }
        }
        free(old_bucket);
    }
}

// void seti_remove_at(seti *s, int i);

int seti_begin(seti *s) {
    return seti_next(s, -1);
}

int seti_end(seti *s) {
    return 1 << s->p;
}

int seti_next(seti *s, int i) {
    int m = 1 << s->p;
    i++;
    while (i < m && (s->bucket[i].flag == IL_EMPTY ||
                     s->bucket[i].flag == IL_TOMBSTONE)) {
        i++;
    }
    return i;
}

int seti_value(seti *s, int i) {
    return s->bucket[i].value;
}