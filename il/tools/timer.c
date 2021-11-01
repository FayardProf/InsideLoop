#include "timer.h"

#include <stdlib.h>
#include <time.h>
#include <assert.h>

struct timer_t {
    double time;
    clock_t start_time;
};

timer *timer_new() {
    timer *t = malloc(sizeof(timer));
		t->time = 0.0;
    return t;
}

void timer_delete(timer *t) {
    free(t);
}

void timer_start(timer *t) {
    t->start_time = clock();
}

void timer_stop(timer *t) {
    clock_t stop_time = clock();
		t->time += (double) (stop_time - t->start_time) / CLOCKS_PER_SEC; 
}

double timer_time(timer *t) {
    return t->time;
}

void timer_reset(timer *t) {
    t->time = 0.0;
}