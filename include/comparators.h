#ifndef COMPARATORS_H
#define COMPARATORS_H

typedef int (*comparator_fn)(const void*, const void*);

int cmp_ascending(const int* a, const int* b);
int cmp_descending(const int* a, const int* b);
int cmp_modulus(const int* a, const int* b);
int cmp_even_first(const int* a, const int* b);

#endif
