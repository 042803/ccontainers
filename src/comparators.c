#include "../include/comparators.h"

static inline int int_abs(int x) {
    return x < 0 ? -x : x;
}

int cmp_ascending(const int* a, const int* b) {
    return (*a > *b) - (*a < *b);
}

int cmp_descending(const int* a, const int* b) {
    return (*b > *a) - (*b < *a);
}

int cmp_modulus(const int* a, const int* b) {
    return (int_abs(*a) > int_abs(*b)) - (int_abs(*a) < int_abs(*b));
}

int cmp_even_first(const int* a, const int* b) {
    if ((*a % 2 == 0) && (*b % 2 != 0)) return -1;
    if ((*a % 2 != 0) && (*b % 2 == 0)) return 1;
    return cmp_ascending(a, b);
}
