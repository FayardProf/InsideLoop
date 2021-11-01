#include "mpilib.h"

void doc_list() {
		int n = 10;

    listd *lst = listd_new();
    double x = 0.123456789123456789;
    for (int k = 0; k < n; k++) {
        noded *no = listd_begin(lst);
        while (no != listd_end(lst) && x > listd_value(no)) {
            no = listd_next(no);
        }
        listd_insert(lst, no, x);
        x = 4 * x * (1 - x);
    }

    printf("\n");
    for (noded *no = listd_begin(lst); no != listd_end(lst); no = listd_next(no)) {
        printf("%f\n", listd_value(no));
    }
    printf("\n");
    for (noded *no = listd_rbegin(lst); no != listd_rend(lst); no = listd_previous(no)) {
        printf("%f\n", listd_value(no));
    }
    listd_delete(lst);
}