#include <stdio.h>

#include "il.h"

int main() {
    int n = 32;

    seti *s = seti_new();
    for (int i = 0; i < n; i++) {
        seti_add(s, i);
    }

    for (int i = seti_begin(s); i != seti_end(s); i = seti_next(s, i)) {
        printf("%d\n", seti_value(s, i));
    }

    seti_delete(s);

    return 0;
}
