#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/karatsuba.h"

void mult(struct Poly lhs, struct Poly rhs, struct Poly *p_res)
{
    unsigned k = 0;
    for (int i = lhs.start; i < lhs.end; i++)
        for (int j = rhs.start; j < rhs.end; j++) {
            k = i + j - 2 * lhs.start;
            assert(k < p_res->end);
            p_res->p[k] = p_res->p[k] + rhs.p[i] * lhs.p[j];
        }
}

void sum(struct Poly s1, struct Poly *res)
{
    res->len = s1.len / 2;
    res->start = 0;
    res->end = s1.len / 2;

    for (int i = res->start; i < res->end; i++) {
        res->p[i] = s1.p[i + s1.start] + s1.p[i + s1.start + res->len];
    }
}

void mpk(struct Poly lhs, struct Poly rhs, struct Poly *p_res)
{
    struct Poly first, second, third;

    assert((lhs.len > 0) && (rhs.len > 0) && (p_res->len > 0));
    assert((lhs.p != NULL) && (rhs.p != NULL) && (p_res->p != NULL));
    assert(((lhs.end - lhs.start) == lhs.len));
    assert((rhs.end - rhs.start) == rhs.len);
    assert((p_res->end - p_res->start) == p_res->len);

    if ((lhs.len) <= 70) {
        mult(lhs, rhs, p_res);

    } else {
        first.len = lhs.len - 1;
        first.p = calloc(first.len, sizeof(unsigned));

        second.len = lhs.len - 1;
        second.start = 0;
        second.end = second.len;
        second.p = calloc(second.len, sizeof(unsigned));

        third.len = lhs.len - 1;
        third.p = calloc(third.len, sizeof(unsigned));

        assert((first.p != NULL) && (second.p != NULL) && (third.p != NULL));

        sum(lhs, &first);
        sum(rhs, &third);

        mpk(first, third, &second);

        for (int i = first.start; i < first.end; i++)
            first.p[i] = 0;

        for (int i = third.start; i < third.end; i++)
            third.p[i] = 0;


        first.len = lhs.len - 1;
        first.start = 0;
        first.end = first.len;

        third.len = lhs.len - 1;
        third.start = 0;
        third.end = third.len;

        lhs.start += lhs.len / 2;
        lhs.len = lhs.len / 2;

        rhs.start += rhs.len / 2;
        rhs.len = rhs.len / 2;
        mpk(lhs, rhs, &first);

        lhs.len *= 2;
        lhs.start -= lhs.len / 2;

        rhs.len *= 2;
        rhs.start -= rhs.len / 2;

        rhs.end -= rhs.len / 2;
        rhs.len = rhs.len / 2;

        lhs.end -= lhs.len / 2;
        lhs.len = lhs.len / 2;

        mpk(lhs, rhs, &third);

        rhs.len = rhs.len * 2;
        rhs.end += rhs.len / 2;

        lhs.len = lhs.len * 2;
        lhs.end += lhs.len / 2;
        for (int i = 0; i < third.end; i++) {
            p_res->p[i] += third.p[i];

            p_res->p[i + (lhs.len) / 2] +=
                (second.p[i] - third.p[i] - first.p[i]);

            p_res->p[i + (lhs.len)] += first.p[i];
        }

        free(first.p);
        free(second.p);
        free(third.p);
    }

}