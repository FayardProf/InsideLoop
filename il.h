#ifndef IL_H
#define IL_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

typedef struct timer_t timer;

struct timer_t {
    double time;
    clock_t start_time;
};

static inline timer *timer_new() {
    timer *t = malloc(sizeof(timer));
    t->time = 0.0;
    return t;
}

static inline void timer_delete(timer *t) {
    free(t);
}

static inline void timer_start(timer *t) {
    t->start_time = clock();
}

static inline void timer_stop(timer *t) {
    clock_t stop_time = clock();
    t->time += (double) (stop_time - t->start_time) / CLOCKS_PER_SEC; 
}

static inline double timer_time(timer *t) {
    return t->time;
}

static inline void timer_reset(timer *t) {
    t->time = 0.0;
}

typedef struct nodei_t nodei;
typedef struct listi_t listi;

struct nodei_t {
    int value;
    nodei *previous;
    nodei *next;
};

struct listi_t {
    nodei *front;
    nodei *back;
};

static inline listi *listi_new() {
    listi *lst = malloc(sizeof(listi));
    lst->front = NULL;
    lst->back = NULL;
    return lst;    
}

static inline void listi_delete(listi *lst) {
    nodei *node = lst->front;
    while (node != NULL) {
        nodei *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

static inline bool listi_empty(listi *lst) {
    return lst->front == NULL;
}

static inline int listi_size(listi *lst) {
    int n = 0;
    nodei *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

static inline void listi_push_front(listi *lst, int x) {
    nodei *node = malloc(sizeof(nodei));
    node->value = x;
    node->previous = NULL;
    node->next = lst->front;
    if (listi_empty(lst)) {
        lst->back = node;
    } else {
        lst->front->previous = node;
    }
    lst->front = node;
}

static inline void listi_push_back(listi *lst, int x) {
    nodei *node = malloc(sizeof(nodei));
    node->value = x;
    node->previous = lst->back;
    node->next = NULL;
    if (listi_empty(lst)) {
        lst->front = node;
    } else {
        lst->back->next = node;
    }
    lst->back = node;
}

static inline int listi_front(listi *lst) {
    assert(!listi_empty(lst));
    return lst->front->value;
}

static inline int listi_back(listi *lst) {
    assert(!listi_empty(lst));
    return lst->back->value;
}

static inline int listi_pop_front(listi *lst) {
    assert(!listi_empty(lst));
    nodei* front = lst->front;
    int v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

static inline int listi_pop_back(listi *lst) {
    assert(!listi_empty(lst));
    nodei* back = lst->back;
    int v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

static inline nodei *listi_begin(listi *lst) {
    return lst->front;
}

static inline nodei *listi_end(listi *lst) {
    return NULL;
}

static inline nodei *listi_rbegin(listi *lst) {
    return lst->back;
}

static inline nodei *listi_rend(listi *lst) {
    return NULL;
}

static inline nodei *listi_next(nodei *no) {
    assert(no != NULL);
    return no->next;
}

static inline nodei *listi_previous(nodei *no) {
    assert(no != NULL);
    return no->previous;
}

static inline int listi_value(nodei *no) {
    assert(no != NULL);
    return no->value;
}

static inline void listi_insert(listi* lst, nodei* no, int x) {
    nodei *new_no = malloc(sizeof(nodei));
    new_no->value = x;
    new_no->next = no;
    if (no != NULL) {
        new_no->previous = no->previous;
        if (no->previous != NULL) {
            no->previous->next = new_no;
        }
        no->previous = new_no;
    } else {
        new_no->previous = lst->back;
        if (lst->back != NULL) {
            lst->back->next = new_no; 
        }
        lst->back = new_no;
    }
    if (new_no->previous == NULL) {
        lst->front = new_no;
    }
}

static inline void listi_erase(listi *lst, nodei *no) {
    assert(no != NULL);
    nodei *previous_no = no->previous;
    nodei *next_no = no->next;
    free(no);
    if (previous_no != NULL) {
        previous_no->next = next_no;
    } else {
        lst->front = next_no;
    }
    if (next_no != NULL) {
        next_no->previous = previous_no;
    } else {
        lst->back = previous_no;
    }
}

typedef struct noded_t noded;
typedef struct listd_t listd;

struct noded_t {
    double value;
    noded *previous;
    noded *next;
};

struct listd_t {
    noded *front;
    noded *back;
};

static inline listd *listd_new() {
    listd *lst = malloc(sizeof(listd));
    lst->front = NULL;
    lst->back = NULL;
    return lst;    
}

static inline void listd_delete(listd *lst) {
    noded *node = lst->front;
    while (node != NULL) {
        noded *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

static inline bool listd_empty(listd *lst) {
    return lst->front == NULL;
}

static inline int listd_size(listd *lst) {
    int n = 0;
    noded *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

static inline void listd_push_front(listd *lst, double x) {
    noded *node = malloc(sizeof(noded));
    node->value = x;
    node->previous = NULL;
    node->next = lst->front;
    if (listd_empty(lst)) {
        lst->back = node;
    } else {
        lst->front->previous = node;
    }
    lst->front = node;
}

static inline void listd_push_back(listd *lst, double x) {
    noded *node = malloc(sizeof(noded));
    node->value = x;
    node->previous = lst->back;
    node->next = NULL;
    if (listd_empty(lst)) {
        lst->front = node;
    } else {
        lst->back->next = node;
    }
    lst->back = node;
}

static inline double listd_front(listd *lst) {
    assert(!listd_empty(lst));
    return lst->front->value;
}

static inline double listd_back(listd *lst) {
    assert(!listd_empty(lst));
    return lst->back->value;
}

static inline double listd_pop_front(listd *lst) {
    assert(!listd_empty(lst));
    noded* front = lst->front;
    double v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

static inline double listd_pop_back(listd *lst) {
    assert(!listd_empty(lst));
    noded* back = lst->back;
    double v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

static inline noded *listd_begin(listd *lst) {
    return lst->front;
}

static inline noded *listd_end(listd *lst) {
    return NULL;
}

static inline noded *listd_rbegin(listd *lst) {
    return lst->back;
}

static inline noded *listd_rend(listd *lst) {
    return NULL;
}

static inline noded *listd_next(noded *no) {
    assert(no != NULL);
    return no->next;
}

static inline noded *listd_previous(noded *no) {
    assert(no != NULL);
    return no->previous;
}

static inline double listd_value(noded *no) {
    assert(no != NULL);
    return no->value;
}

static inline void listd_insert(listd* lst, noded* no, double x) {
    noded *new_no = malloc(sizeof(noded));
    new_no->value = x;
    new_no->next = no;
    if (no != NULL) {
        new_no->previous = no->previous;
        if (no->previous != NULL) {
            no->previous->next = new_no;
        }
        no->previous = new_no;
    } else {
        new_no->previous = lst->back;
        if (lst->back != NULL) {
            lst->back->next = new_no; 
        }
        lst->back = new_no;
    }
    if (new_no->previous == NULL) {
        lst->front = new_no;
    }
}

static inline void listd_erase(listd *lst, noded *no) {
    assert(no != NULL);
    noded *previous_no = no->previous;
    noded *next_no = no->next;
    free(no);
    if (previous_no != NULL) {
        previous_no->next = next_no;
    } else {
        lst->front = next_no;
    }
    if (next_no != NULL) {
        next_no->previous = previous_no;
    } else {
        lst->back = previous_no;
    }
}

typedef struct arrayb_t arrayb;

struct arrayb_t {
    bool *data;
    int size;
    int capacity;
};

static inline arrayb *arrayb_new() {
    arrayb *v = malloc(sizeof(arrayb));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

static inline void arrayb_delete(arrayb *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

static inline bool arrayb_empty(arrayb *v) {
    return v->size == 0;
}

static inline int arrayb_size(arrayb *v) {
    return v->size;
}

static inline void _arrayb_increase_capacity(arrayb* v, int r) {
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

static inline void arrayb_resize(arrayb* v, int n) {
    if (n > v->capacity) {
        _arrayb_increase_capacity(v, n);
    }
    v->size = n;
}

static inline void arrayb_reserve(arrayb* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _arrayb_increase_capacity(v, r);
    }
}

static inline bool arrayb_get(arrayb *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

static inline void arrayb_set(arrayb *v, int i, bool x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

static inline void arrayb_swap(arrayb *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    bool x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

static inline void arrayb_push_back(arrayb *v, bool x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _arrayb_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

static inline bool arrayb_pop_back(arrayb *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

static inline bool *arrayb_data(arrayb *v) {
    return v->data;
}

typedef struct arrayi_t arrayi;

struct arrayi_t {
    int *data;
    int size;
    int capacity;
};

static inline arrayi *arrayi_new() {
    arrayi *v = malloc(sizeof(arrayi));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

static inline void arrayi_delete(arrayi *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

static inline bool arrayi_empty(arrayi *v) {
    return v->size == 0;
}

static inline int arrayi_size(arrayi *v) {
    return v->size;
}

static inline void _arrayi_increase_capacity(arrayi* v, int r) {
    assert(v->capacity < r);
    int *new_data = malloc(r * sizeof(int));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

static inline void arrayi_resize(arrayi* v, int n) {
    if (n > v->capacity) {
        _arrayi_increase_capacity(v, n);
    }
    v->size = n;
}

static inline void arrayi_reserve(arrayi* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _arrayi_increase_capacity(v, r);
    }
}

static inline int arrayi_get(arrayi *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

static inline void arrayi_set(arrayi *v, int i, int x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

static inline void arrayi_swap(arrayi *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    int x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

static inline void arrayi_push_back(arrayi *v, int x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _arrayi_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

static inline int arrayi_pop_back(arrayi *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

static inline int *arrayi_data(arrayi *v) {
    return v->data;
}


typedef struct arrayd_t arrayd;

struct arrayd_t {
    double *data;
    int size;
    int capacity;
};

static inline arrayd *arrayd_new() {
    arrayd *v = malloc(sizeof(arrayd));
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
    return v;
}

static inline void arrayd_delete(arrayd *v) {
    if (v->data != NULL) {
        free(v->data);
    }
    free(v);
}

static inline bool arrayd_empty(arrayd *v) {
    return v->size == 0;
}

static inline int arrayd_size(arrayd *v) {
    return v->size;
}

static inline void _arrayd_increase_capacity(arrayd* v, int r) {
    assert(v->capacity < r);
    double *new_data = malloc(r * sizeof(double));
    if (v->data != NULL) {
        for (int i = 0; i < v->size; i++) {
            new_data[i] = v->data[i];
        }
        free(v->data);
    }
    v->data = new_data;
    v->capacity = r;
}

static inline void arrayd_resize(arrayd* v, int n) {
    if (n > v->capacity) {
        _arrayd_increase_capacity(v, n);
    }
    v->size = n;
}

static inline void arrayd_reserve(arrayd* v, int r) {
    assert(r >= 0);

    if (r > v->capacity) {
        _arrayd_increase_capacity(v, r);
    }
}

static inline double arrayd_get(arrayd *v, int i) {
    assert(i >= 0 && i < v->size);
    return v->data[i];
}

static inline void arrayd_set(arrayd *v, int i, double x) {
    assert(i >= 0 && i < v->size);
    v->data[i] = x;
}

static inline void arrayd_swap(arrayd *v, int i, int j) {
    assert(i >= 0 && i < v->size);
    assert(j >= 0 && j < v->size);
    double x = v->data[i];
    v->data[i] = v->data[j];
    v->data[j] = x;
}

static inline void arrayd_push_back(arrayd *v, double x) {
    int n = v->size;
    int r = v->capacity;
    if (r == n) {
        int new_r = (n == 0) ? 1 : 2 * n;
        _arrayd_increase_capacity(v, new_r);
    }
    v->data[n] = x;
    v->size++;
}

static inline double arrayd_pop_back(arrayd *v) {
    assert(v->size > 0);
    v->size--;
    int i = v->size;
    return v->data[i];
}

static inline double *arrayd_data(arrayd *v) {
    return v->data;
}

typedef struct array2ui8_t array2ui8;

struct array2ui8_t {
    uint8_t *data;
    int size[2];
    int capacity[2];
};

static inline array2ui8 *array2ui8_new() {
    array2ui8 *m = malloc(sizeof(array2ui8));
    m->data = NULL;
    m->size[0] = 0;
    m->size[1] = 0;
    m->capacity[0] = 0;
    m->capacity[1] = 0;
    return m;
}

static inline void array2ui8_delete(array2ui8 *m) {
    if (m->data != NULL) {
        free(m->data);
    }
    free(m);
}

static inline int array2ui8_size(array2ui8 *m, int d) {
    assert(d == 0 || d == 1);
    return m->size[d];
}

static inline int array2ui8_capacity(array2ui8 *m, int d) {
    assert(d == 0 || d == 1);
    return m->capacity[d];  
}

static inline void array2ui8_resize(array2ui8 *m, int n0, int n1) {
    assert(n0 >= 0);
    assert(n1 >= 0);
    int n0_capacity = array2ui8_capacity(m, 0);
    int n1_capacity = array2ui8_capacity(m, 1);
    if (n0 > n0_capacity || n1 > n1_capacity) {
        int n0_old = array2ui8_size(m, 0);
        int n1_old = array2ui8_size(m, 1);
        uint8_t *new_data = malloc(n0 * n1 * sizeof(uint8_t));
        if (m->data != NULL) {
            for (int i0 = 0; i0 < n0_old; i0++) {
                for (int i1 = 0; i1 < n1_old; i1++) {
                    new_data[i0 * n1 + i1] = m->data[i0 * m->capacity[1] + i1];
                }
            }
        }
        m->capacity[0] = n0;
        m->capacity[1] = n1;
        m->data = new_data;
    }
    m->size[0] = n0;
    m->size[1] = n1;
}

static inline int8_t array2ui8_get(array2ui8 *m, int i0, int i1) {
    assert(i0 >= 0 && i0 < m->size[0]);
    assert(i1 >= 0 && i1 < m->size[1]);
    return m->data[i0 * m->capacity[1] + i1];
}

static inline void array2ui8_set(array2ui8 *m, int i0, int i1, int8_t x) {
    assert(i0 >= 0 && i0 < m->size[0]);
    assert(i1 >= 0 && i1 < m->size[1]);
    m->data[i0 * m->capacity[1] + i1] = x;
}

static inline uint8_t *array2ui8_data(array2ui8 *m) {
    return m->data;
}

typedef struct array3ui8_t array3ui8;

struct array3ui8_t {
    uint8_t *data;
    int size[3];
    int capacity[3];
};

static inline array3ui8 *array3ui8_new() {
    array3ui8 *m = malloc(sizeof(array3ui8));
    m->data = NULL;
    m->size[0] = 0;
    m->size[1] = 0;
    m->size[2] = 0;
    m->capacity[0] = 0;
    m->capacity[1] = 0;
    m->capacity[2] = 0;
    return m;
}

static inline void array3ui8_delete(array3ui8 *m) {
    if (m->data != NULL) {
        free(m->data);
    }
    free(m);
}

static inline int array3ui8_size(array3ui8 *m, int d) {
    assert(d == 0 || d == 1 || d == 2);
    return m->size[d];
}

static inline int array3ui8_capacity(array3ui8 *m, int d) {
    assert(d == 0 || d == 1 || d == 2);
    return m->capacity[d];  
}

static inline void array3ui8_resize(array3ui8 *m, int n0, int n1, int n2) {
    assert(n0 >= 0);
    assert(n1 >= 0);
    assert(n2 >= 0);
    int n0_capacity = array3ui8_capacity(m, 0);
    int n1_capacity = array3ui8_capacity(m, 1);
    int n2_capacity = array3ui8_capacity(m, 2);
    if (n0 > n0_capacity || n1 > n1_capacity || n2 > n2_capacity) {
        int n0_old = array3ui8_size(m, 0);
        int n1_old = array3ui8_size(m, 1);
        int n2_old = array3ui8_size(m, 2);
        uint8_t *new_data = malloc(n0 * n1 * n2 * sizeof(uint8_t));
        if (m->data != NULL) {
            for (int i0 = 0; i0 < n0_old; i0++) {
                for (int i1 = 0; i1 < n1_old; i1++) {
                    for (int i2 = 0; i2 < n2_old; i2++) {
                        new_data[(i0 * n1 + i1) * n2 + i2] = m->data[(i0 * m->capacity[1] + i1) * m->capacity[2] + i2];
                    }
                }
            }
        }
        m->capacity[0] = n0;
        m->capacity[1] = n1;
        m->capacity[2] = n2;
        m->data = new_data;
    }
    m->size[0] = n0;
    m->size[1] = n1;
    m->size[2] = n1;
}

static inline int8_t array3ui8_get(array3ui8 *m, int i0, int i1, int i2) {
    assert(i0 >= 0 && i0 < m->size[0]);
    assert(i1 >= 0 && i1 < m->size[1]);
    assert(i2 >= 0 && i2 < m->size[2]);
    return m->data[(i0 * m->capacity[1] + i1) * m->capacity[2] + i2];
}

static inline void array3ui8_set(array3ui8 *m, int i0, int i1, int i2, int8_t x) {
    assert(i0 >= 0 && i0 < m->size[0]);
    assert(i1 >= 0 && i1 < m->size[1]);
    assert(i2 >= 0 && i2 < m->size[2]);
    m->data[(i0 * m->capacity[1] + i1) * m->capacity[2] + i2] = x;
}

#define IL_EMPTY 0
#define IL_TOMBSTONE 1
#define IL_OCCUPIED 2

typedef struct setd_t setd;
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

static inline unsigned int hashd(double x, int p) {
    unsigned int mask = (1 << p) - 1;
    unsigned int i = (unsigned int) x;
    i &= mask;
    return i;
}

static inline setd *setd_new() {
    setd *s = malloc(sizeof(setd));
    s->bucket = NULL;
    s->nb_elements = 0;
    s->nb_tombstones = 0;
    s->p = -1;
    return s;
}

static inline void setd_delete(setd *s) {
    if (s->bucket != NULL) {
        free(s->bucket);
    }
    free(s);
}

static inline bool setd_empty(setd *s) {
    return s->nb_elements == 0;
}

static inline int _setd_nb_buckets(int p) {
    return (p >= 0) ? (1 << p) : 0;
}

// void setd_remove(setd *s, double x);

static inline int setd_search(setd *s, double x) {
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

static inline bool setd_found(int i) {
    return i >= 0;
}

static inline void _setd_reserve(setd *s, int p);

static inline int setd_add_at(setd *s, int i, double x) {
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

static inline void _setd_reserve(setd *s, int p) {
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

// static inline void setd_remove_at(setd *s, int i);

static inline bool setd_contains(setd *s, double x) {
    return setd_search(s, x) >= 0;
}

static inline void setd_add(setd *s, double x) {
    int i = setd_search(s, x);
    if (i < 0) {
        setd_add_at(s, i, x);
    }
}

static inline int setd_next(setd *s, int i) {
    int m = 1 << s->p;
    i++;
    while (i < m && (s->bucket[i].flag == IL_EMPTY ||
                     s->bucket[i].flag == IL_TOMBSTONE)) {
        i++;
    }
    return i;
}

static inline int setd_begin(setd *s) {
    return setd_next(s, -1);
}

static inline int setd_end(setd *s) {
    return 1 << s->p;
}

static inline double setd_value(setd *s, int i) {
    return s->bucket[i].value;
}

typedef struct sbucketi_t sbucketi;
typedef struct seti_t seti;

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

static inline unsigned int hashi(int x, int p) {
    unsigned int knuth = 2654435769;
    return (x * knuth) >> (32 - p);
}

static inline seti *seti_new() {
    seti *s = malloc(sizeof(seti));
    s->bucket = NULL;
    s->nb_elements = 0;
    s->nb_tombstones = 0;
    s->p = -1;
    return s;
}

static inline void seti_delete(seti *s) {
    if (s->bucket != NULL) {
        free(s->bucket);
    }
    free(s);
}

static inline bool seti_empty(seti *s) {
    return s->nb_elements == 0;
}

static inline int _seti_nb_buckets(int p) {
    return (p >= 0) ? (1 << p) : 0;
}

// void seti_remove(seti *s, int x);

static inline int seti_search(seti *s, int x) {
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

static inline bool seti_found(int i) {
    return i >= 0;
}

static inline void _seti_reserve(seti *s, int p);

static inline int seti_add_at(seti *s, int i, int x) {
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

static inline void _seti_reserve(seti *s, int p) {
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

static inline bool seti_contains(seti *s, int x) {
    return seti_search(s, x) >= 0;
}

static inline void seti_add(seti *s, int x) {
    int i = seti_search(s, x);
    if (i < 0) {
        seti_add_at(s, i, x);
    }
}
// void seti_remove_at(seti *s, int i);

static inline int seti_end(seti *s) {
    return 1 << s->p;
}

static inline int seti_next(seti *s, int i) {
    int m = 1 << s->p;
    i++;
    while (i < m && (s->bucket[i].flag == IL_EMPTY ||
                     s->bucket[i].flag == IL_TOMBSTONE)) {
        i++;
    }
    return i;
}

static inline int seti_begin(seti *s) {
    return seti_next(s, -1);
}

static inline int seti_value(seti *s, int i) {
    return s->bucket[i].value;
}

#endif //IL_H