#include "../include/comparators.h"

static inline int int_abs(int x) {
    return x < 0 ? -x : x;
}

int cmp_ascending(const void* a, const void* b) {
    const int ia = *(const int*) a; 
    const int ib = *(const int*) b;
    return (ia > ib) - (ia < ib);
}

int cmp_descending(const void* a, const void* b) {
    const int ia = *(const int*)a;
    const int ib = *(const int*)b;
    return (ib > ia) - (ib < ia);   
}

int cmp_modulus(const void* a, const void* b) {
    const int ia = int_abs(*(const int*)a);
    const int ib = int_abs(*(const int*)b);
    return (ia > ib) - (ia < ib);
}

int cmp_even_first(const void* a, const void* b) {
    const int ia = *(const int*)a;
    const int ib = *(const int*)b;

    if ((ia % 2 == 0) && (ib % 2 != 0)) return -1;
    if ((ia % 2 != 0) && (ib % 2 == 0)) return 1;
    return cmp_ascending(&ia, &ib); 
}
