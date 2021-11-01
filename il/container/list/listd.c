#include "listd.h"

#include <stdlib.h>
#include <assert.h>

struct noded_t {
    double value;
    noded *previous;
    noded *next;
};

struct listd_t {
    noded *front;
    noded *back;
};

listd *listd_new() {
    listd *lst = malloc(sizeof(listd));
    lst->front = NULL;
    lst->back = NULL;
    return lst;    
}

void listd_delete(listd *lst) {
    noded *node = lst->front;
    while (node != NULL) {
        noded *next_node = node->next;
        free(node);
        node = next_node;
    }
    free(lst);
}

bool listd_empty(listd *lst) {
    return lst->front == NULL;
}

int listd_size(listd *lst) {
    int n = 0;
    noded *node = lst->front;
    while (node != NULL) {
        node = node->next;
        n++;
    }
    return n;
}

void listd_push_front(listd *lst, double x) {
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

void listd_push_back(listd *lst, double x) {
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

double listd_front(listd *lst) {
    assert(!listd_empty(lst));
    return lst->front->value;
}

double listd_back(listd *lst) {
    assert(!listd_empty(lst));
    return lst->back->value;
}

double listd_pop_front(listd *lst) {
    assert(!listd_empty(lst));
    noded* front = lst->front;
    double v = front->value;
    lst->front = front->next;
    if (lst->back == front) {
        lst->back = NULL;
    }
    return v;
}

double listd_pop_back(listd *lst) {
    assert(!listd_empty(lst));
    noded* back = lst->back;
    double v = back->value;
    lst->back = back->previous;
    if (lst->front == back) {
        lst->front = NULL;
    }
    return v;
}

noded *listd_begin(listd *lst) {
    return lst->front;
}

noded *listd_end(listd *lst) {
    return NULL;
}

noded *listd_rbegin(listd *lst) {
    return lst->back;
}

noded *listd_rend(listd *lst) {
    return NULL;
}

noded *listd_next(noded *no) {
	assert(no != NULL);
    return no->next;
}

noded *listd_previous(noded *no) {
    assert(no != NULL);
    return no->previous;
}

double listd_value(noded *no) {
    assert(no != NULL);
    return no->value;
}

void listd_insert(listd* lst, noded* no, double x) {
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

void listd_erase(listd *lst, noded *no) {
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
