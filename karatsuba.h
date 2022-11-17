#pragma once 

struct Poly {
    unsigned start;
    unsigned end;
    unsigned len;
    unsigned *p;
};

void mult(struct Poly lhs, struct Poly rhs, struct Poly *p_res);

void sum(struct Poly s1, struct Poly *res);


void mpk(struct Poly lhs, struct Poly rhs, struct Poly *p_res);