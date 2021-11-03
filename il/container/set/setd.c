#include "setd.h"

#include <stdlib.h>
#include <assert.h>

#define IL_EMPTY 0
#define IL_TOMBSTONE 1
#define IL_OCCUPIED 2

typedef struct sbucketd_t sbucketd;

struct setd_t {
    sbucketd *bucket;
    int nb_elements;
    int nb_tombstones;
    int p;
};

struct sbucketd_t {
    uint8_t flag;
    double value;
};

setd *setd_new() {
    setd *s = malloc(sizeof(setd));
    s->bucket = NULL;
    s->nb_elements = 0;
    s->nb_tombstones = 0;
    s->p = -1;
    return s;
}

void setd_delete(setd *s) {
    if (s->bucket != NULL) {
        free(s->bucket);
    }
    free(s);
}

bool setd_empty(setd *s) {
    return s->nb_elements == 0;
}

int _setd_nb_buckets(int p) {
    return (p >= 0) ? (1 << p) : 0;
}

bool setd_contains(setd *s, double x) {
    return setd_search(s, x) >= 0;
}

void setd_add(setd *s, double x) {
    int i = setd_search(s, x);
    if (i < 0) {
        setd_add_at(s, i, x);
    }
}

// void setd_remove(setd *s, double x);

int setd_search(setd *s, double x) {
    if (s->p == -1) {
        return -1;
    }
    unsigned int mask = (1 << s->p) - 1;
    unsigned int i = hashd(x, s->p);
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

bool setd_found(int i) {
    return i >= 0;
}

void _setd_reserve(setd *s, int p);

int setd_add_at(setd *s, int i, double x) {
    i = -(1 + i);
    int m = _setd_nb_buckets(s->p);
    if (4 * (s->nb_elements + 1) > 3 * m) {
        _setd_reserve(s, (s->p == -1) ? 1 : s->p + 1);
        int j = setd_search(s, x);
        i = - (1 + j);
    }
    s->bucket[i].flag = IL_OCCUPIED;
    s->bucket[i].value = x;
    s->nb_elements++;
    return i;
}

void _setd_reserve(setd *s, int p) {
    sbucketd *old_bucket = s->bucket;
    int old_m = _setd_nb_buckets(s->p);
    int m = _setd_nb_buckets(p);
    s->bucket = malloc(m * sizeof(sbucketd));
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
                    int new_i = setd_search(s, old_bucket[i].value);
                    setd_add_at(s, new_i, old_bucket[i].value);
            }
        }
        free(old_bucket);
    }
}

// void setd_remove_at(setd *s, int i);

int setd_begin(setd *s) {
    return setd_next(s, -1);
}

int setd_end(setd *s) {
    return 1 << s->p;
}

int setd_next(setd *s, int i) {
    int m = 1 << s->p;
    i++;
    while (i < m && (s->bucket[i].flag == IL_EMPTY ||
                     s->bucket[i].flag == IL_TOMBSTONE)) {
        i++;
    }
    return i;
}

double setd_value(setd *s, int i) {
    return s->bucket[i].value;
}

