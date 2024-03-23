#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/karatsuba.h"

void scan_input(struct Poly* lhs, struct Poly* rhs, struct Poly* res);
void print_result(struct Poly res);

int main()
{
    struct Poly lhs;            //first factor
    struct Poly rhs;            //second factor
    struct Poly res;            //product

    scan_input(&lhs, &rhs, &res);
    mpk(lhs, rhs, &res);        //Karatsuba multiplication algorithm
    print_result(res);

    free(lhs.p);
    free(rhs.p);
    free(res.p);
    return 0;
}


