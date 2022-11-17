#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "karatsuba.h"

int main()
{
    unsigned n1, m2, pom, kol, l;

    struct Poly lhs;            //первый множитель
    struct Poly rhs;            //второй множитель
    struct Poly res;            //результат произведения

    int sc = scanf("%u %u", &n1, &m2);
    assert(sc == 2);
    lhs.len = n1;
    lhs.start = 0;
    lhs.end = lhs.len;

    rhs.len = m2;
    rhs.start = 0;
    rhs.end = rhs.len;

    lhs.p = calloc(lhs.len, sizeof(unsigned));
    rhs.p = calloc(rhs.len, sizeof(unsigned));
    assert((lhs.p != NULL) && (rhs.p != NULL));

    for (int i = 0; i < n1; i++) {
        sc = scanf("%u", &pom);
        assert(sc == 1);
        lhs.p[i] = pom;
    }

    for (int i = 0; i < m2; i++) {
        sc = scanf("%u", &pom);
        assert(sc == 1);
        rhs.p[i] = pom;
    }

    res.len = rhs.len + lhs.len - 1;
    res.start = 0;
    res.end = res.len;
    res.p = calloc(res.len, sizeof(unsigned));
    assert(res.p != NULL);

    mpk(lhs, rhs, &res);        //умножение по алгоритму Карацубы

    kol = 0;                    //Далее до 149 строчки, проверяю с самого старшего коэффициента вниз на первый ненулевой коэффициент
    l = res.len - 1;
    while (kol == 0)
        if ((res.p[l]) == 0)
            l--;
        else
            kol = 1;


    for (int i = 0; i <= l; i++) {
        printf("%u ", res.p[i]);
    }

    free(lhs.p);
    free(rhs.p);
    free(res.p);
    return 0;
}


