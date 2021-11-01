#include "il.h"

double listd_sum(listd *lst) {
    double sum = 0.0;
    for (noded *no = listd_begin(lst); no != listd_end(lst); no = listd_next(no)) {
        sum += listd_value(no);
    }
    return sum;
}

double arrayd_sum(arrayd *v) {
    double sum = 0.0;
    for (int i = 0; i < arrayd_size(v); i++) {
        sum += arrayd_get(v, i);
    }
    return sum;
}