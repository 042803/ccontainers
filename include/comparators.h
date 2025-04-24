#ifndef COMPARATORS_H
#define COMPARATORS_H

typedef int (*comparator_fn)(const void*, const void*);

int cmp_ascending(const void* a, const void* b);
int cmp_descending(const void* a, const void* b);
int cmp_modulus(const void* a, const void* b);
int cmp_even_first(const void* a, const void* b);

#endif
