#include "listi.h"

#include <stdlib.h>
#include <assert.h>

struct nodei_t {
    int value;
    nodei *previous;
    nodei *next;
};

struct listi_t {
    nodei *front;
    nodei *back;
};

listi *listi_new() {
    listi *lst = malloc(sizeof(listi));
    lst->front = NULL;
    lst->back = NULL;
    return lst;    
}

void listi_delete(listi *lst) {
    nodei *node = lst->front;
    while (node != NULL) {
        nodei *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

bool listi_empty(listi *lst) {
    return lst->front == NULL;
}

int listi_size(listi *lst) {
    int n = 0;
    nodei *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

void listi_push_front(listi *lst, int x) {
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

void listi_push_back(listi *lst, int x) {
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

int listi_front(listi *lst) {
    assert(!listi_empty(lst));
    return lst->front->value;
}

int listi_back(listi *lst) {
    assert(!listi_empty(lst));
    return lst->back->value;
}

int listi_pop_front(listi *lst) {
    assert(!listi_empty(lst));
    nodei* front = lst->front;
    int v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

int listi_pop_back(listi *lst) {
    assert(!listi_empty(lst));
    nodei* back = lst->back;
    int v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

nodei *listi_begin(listi *lst) {
    return lst->front;
}

nodei *listi_end(listi *lst) {
    return NULL;
}

nodei *listi_rbegin(listi *lst) {
    return lst->back;
}

nodei *listi_rend(listi *lst) {
    return NULL;
}

nodei *listi_next(nodei *no) {
	assert(no != NULL);
    return no->next;
}

nodei *listi_previous(nodei *no) {
    assert(no != NULL);
    return no->previous;
}

int listi_value(nodei *no) {
    assert(no != NULL);
    return no->value;
}

void listi_insert(listi* lst, nodei* no, int x) {
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

void listi_erase(listi *lst, nodei *no) {
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