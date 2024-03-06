#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "karatsuba.h"


void print_result(struct Poly res) {
    unsigned l = res.len - 1;
    while(res.p[l] == 0 && l >= 0)
        l--;

    for (int i = 0; i <= l; i++) {
        printf("%u ", res.p[i]);
    }
}

void scan_input(struct Poly* lhs, struct Poly* rhs, struct Poly* res) {
    int sc = scanf("%u %u", &lhs->len, &rhs->len);
    assert(sc == 2);

    lhs->start = rhs->start = 0;
    lhs->end = lhs->len;
    rhs->end = rhs->len;

    lhs->p = calloc(lhs->len, sizeof(unsigned));
    rhs->p = calloc(rhs->len, sizeof(unsigned));
    assert((lhs->p != NULL) && (rhs->p != NULL));

    for (int i = 0; i < lhs->len; i++) {
        sc = scanf("%u", &lhs->p[i]);
        assert(sc == 1);
    }

    for (int i = 0; i < rhs->len; i++) {
        sc = scanf("%u", &rhs->p[i]);
        assert(sc == 1);
    }

    //creating struct Poly res
    res->len = res->end = rhs->len + lhs->len - 1;
    res->start = 0;
    res->p = calloc(res->len, sizeof(unsigned));
    assert(res->p != NULL);
}